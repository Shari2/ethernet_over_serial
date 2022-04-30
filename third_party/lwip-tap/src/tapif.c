// Copyright (c) 2001-2003 Swedish Institute of Computer Science.
// Copyright (c) 2012-2013 Takayuki Usui
//
// SPDX-License-Identifier: BSD-3-Clause
//
// Author: Adam Dunkels <adam@sics.se>

#include "lwip_tap/tapif.h"

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <net/route.h>
#include <errno.h>
#include <assert.h>


#include "lwip/debug.h"

#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/ip.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/sys.h"


#if defined(LWIP_DEBUG) && defined(LWIP_TCPDUMP)
#include "netif/tcpdump.h"
#endif /* LWIP_DEBUG && LWIP_TCPDUMP */


#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#define DEVTAP "/dev/net/tun"

#define IFNAME0 't'
#define IFNAME1 'p'

#ifndef TAPIF_DEBUG
#define TAPIF_DEBUG LWIP_DBG_OFF
#endif

/*-----------------------------------------------------------------------------------*/
static err_t
low_level_probe(struct netif *netif,const char *name)
{
  int len;
  int s;
  struct ifreq ifr;

  len = strlen(name);
  if (len > (IFNAMSIZ-1)) {
    perror("tapif_init: name is too long");
    return ERR_IF;
  }

  s = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
  if (s == -1) {
    perror("tapif_init: socket");
    return ERR_IF;
  }

  memset(&ifr, 0, sizeof(ifr));
  strncpy(ifr.ifr_name, name, len);


  if (ioctl(s, SIOCGIFMTU, &ifr) == -1) {
    perror("tapif_init: ioctl SIOCGIFMTU");
    goto err;
  }

  ifr.ifr_flags |= IFF_UP;
  ioctl(s, SIOCSIFFLAGS, &ifr);

  // add route instead of ip to the link or kernel will respond to icmp instead of application
  struct rtentry route;
  memset( &route, 0, sizeof( route ) );

  struct sockaddr_in *addr = (struct sockaddr_in *)&route.rt_gateway;
  addr->sin_family = AF_INET;
  addr->sin_addr.s_addr = netif->gw.addr;

  addr = (struct sockaddr_in*) &route.rt_dst;
  addr->sin_family = AF_INET;
  addr->sin_addr.s_addr = netif->ip_addr.addr & netif->netmask.addr;

  addr = (struct sockaddr_in*) &route.rt_genmask;
  addr->sin_family = AF_INET;
  addr->sin_addr.s_addr = netif->netmask.addr;

  route.rt_flags = RTF_UP;
  route.rt_metric = 0;
  route.rt_dev = ifr.ifr_name;

  if(ioctl( s, SIOCADDRT, &route ))
  {
    perror("SIOCADDRT");
    goto err;
  }


  netif->mtu = ifr.ifr_mtu;
  close(s);
  return ERR_OK;
 err:
  close(s);
  return ERR_IF;
}

static void
low_level_init(struct netif *netif,const char *name)
{
  struct tapif *tapif;
  struct ifreq ifr;
  tapif = (struct tapif *)netif->state;

  /* Do whatever else is needed to initialize interface. */

  tapif->fd = open(DEVTAP, O_RDWR);
  LWIP_DEBUGF(TAPIF_DEBUG, ("tapif_init: fd %d\n", tapif->fd));
  if(tapif->fd == -1) {
    perror("tapif_init: try running \"modprobe tun\" or rebuilding your kernel with CONFIG_TUN; cannot open "DEVTAP);
    exit(1);
  }

  memset(&ifr, 0, sizeof(ifr));
  if (name != NULL)
  {
    strncpy(ifr.ifr_name,name,strlen(name));
  }

  ifr.ifr_flags = IFF_TUN|IFF_NO_PI;

  if (ioctl(tapif->fd, TUNSETIFF, (void *) &ifr) < 0) {
    perror("tapif_init: "DEVTAP" ioctl TUNSETIFF");
    exit(1);
  }

  if(fcntl(tapif->fd, F_SETFL, O_NONBLOCK) < 0)
  {
    perror("Nonblocking");
    exit(1);
  }


  if (low_level_probe(netif,name != NULL ? name : ifr.ifr_name) != ERR_OK)
    exit(1);
}
/*-----------------------------------------------------------------------------------*/
/*
 * low_level_output():
 *
 * Should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 */
/*-----------------------------------------------------------------------------------*/
static err_t
low_level_output(struct netif *netif, struct pbuf *p)
{
  struct pbuf *q;
  char buf[1514];
  char *bufptr;
  struct tapif *tapif;

  tapif = (struct tapif *)netif->state;
  /* initiate transfer(); */

  bufptr = &buf[0];

  for(q = p; q != NULL; q = q->next) {
    /* Send the data from the pbuf to the interface, one pbuf at a
       time. The size of the data in each pbuf is kept in the ->len
       variable. */
    /* send data from(q->payload, q->len); */
    memcpy(bufptr, q->payload, q->len);
    bufptr += q->len;
  }

  /* signal that packet should be sent(); */
  if(write(tapif->fd, buf, p->tot_len) == -1) {
    perror("tapif: write");
  }
  return ERR_OK;
}

static err_t
tapif_output_v4(struct netif *netif, struct pbuf *p, const ip4_addr_t *ipaddr)
{
  LWIP_UNUSED_ARG(ipaddr);
  return low_level_output(netif, p);
}

/*-----------------------------------------------------------------------------------*/
/*
 * tapif_init():
 *
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 */
/*-----------------------------------------------------------------------------------*/
err_t
tapif_init(struct netif *netif)
{
  struct tapif *tapif;
  char *name = NULL;
  err_t err;

  if (netif->state == NULL) {
    tapif = (struct tapif *)mem_malloc(sizeof(struct tapif));
    if (!tapif) {
      return ERR_MEM;
    }
    netif->state = tapif;
  } else {
    tapif = (struct tapif *)netif->state;
    name = tapif->name;
    if (name != NULL) {
      err = low_level_probe(netif,name);
      if (err != ERR_OK)
        return err;
    }
  }
  netif->name[0] = IFNAME0;
  netif->name[1] = IFNAME1;
  netif->output = tapif_output_v4;
  netif->linkoutput = low_level_output;
  netif->mtu = 1500;

  netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_IGMP;

  low_level_init(netif,name);

  return ERR_OK;
}

void
tapif_poll(struct netif *netif)
{
  u8_t c;
  struct tapif *priv;

  LWIP_ASSERT("netif != NULL", (netif != NULL));
  LWIP_ASSERT("netif->state != NULL", (netif->state != NULL));

  priv = (struct tapif *)netif->state;

  if (priv->p == NULL)
  {
    priv->p = pbuf_alloc(PBUF_IP, netif->mtu, PBUF_POOL);
  }

  int ret = read(priv->fd, priv->p->payload, netif->mtu);
  if(ret < 0)
  {
    switch(errno)
    {
      case EAGAIN:
        break;
      default:
        assert(0);
        break;
    }
  } else {
    if (netif->input(priv->p, netif) != ERR_OK) {
      pbuf_free(priv->p);
    }
    priv->p = NULL;
  }
}
/*-----------------------------------------------------------------------------------*/
