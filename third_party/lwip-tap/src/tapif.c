// Copyright (c) 2001-2003 Swedish Institute of Computer Science.
// Copyright (c) 2012-2013 Takayuki Usui
//
// SPDX-License-Identifier: BSD-3-Clause
//
// Author: Adam Dunkels <adam@sics.se>

#include "tapif.h"

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/socket.h>


#include "lwip/debug.h"

#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/ip.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/sys.h"

#include "netif/etharp.h"

#if defined(LWIP_DEBUG) && defined(LWIP_TCPDUMP)
#include "netif/tcpdump.h"
#endif /* LWIP_DEBUG && LWIP_TCPDUMP */

#define IFCONFIG_BIN "/sbin/ifconfig "

#if defined(linux)
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#define DEVTAP "/dev/net/tun"
#define IFCONFIG_ARGS "%s inet %d.%d.%d.%d netmask %d.%d.%d.%d"
#elif defined(openbsd)
#define DEVTAP "/dev/tun0"
#define IFCONFIG_ARGS "tun0 inet %d.%d.%d.%d link0"
#else /* others */
#define DEVTAP "/dev/tap0"
#define IFCONFIG_ARGS "tap0 inet %d.%d.%d.%d"
#endif

#define IFNAME0 't'
#define IFNAME1 'p'

#ifndef TAPIF_DEBUG
#define TAPIF_DEBUG LWIP_DBG_OFF
#endif

/* Forward declarations. */
static void  tapif_input(struct netif *netif);

static void tapif_thread(void *data);

/*-----------------------------------------------------------------------------------*/
#ifdef linux
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
  s = socket(AF_INET,SOCK_DGRAM,0);
  if (s == -1) {
    perror("tapif_init: socket");
    return ERR_IF;
  }
  memset(&ifr,0,sizeof(ifr));
  strncpy(ifr.ifr_name,name,len);
  if (ioctl(s,SIOCGIFHWADDR,&ifr) == -1) {
    perror("tapif_init: ioctl SIOCGIFHWADDR");
    goto err;
  }
  u8_t* hwaddr = (u8_t*)&ifr.ifr_hwaddr.sa_data;
  netif->hwaddr[0] = hwaddr[0];
  netif->hwaddr[1] = hwaddr[1];
  netif->hwaddr[2] = hwaddr[2];
  netif->hwaddr[3] = hwaddr[3];
  netif->hwaddr[4] = hwaddr[4];
  netif->hwaddr[5] = hwaddr[5] ^ 1;
  netif->hwaddr_len = 6;
  if (ioctl(s,SIOCGIFMTU,&ifr) == -1) {
    perror("tapif_init: ioctl SIOCGIFMTU");
    goto err;
  }
  netif->mtu = ifr.ifr_mtu;
  close(s);
  return ERR_OK;
 err:
  close(s);
  return ERR_IF;
}
#else
static err_t
low_level_probe(struct netif *netif,const char *name)
{
  return ERR_IF;
}
#endif

static void
low_level_init(struct netif *netif,const char *name)
{
  struct tapif *tapif;
  char buf[sizeof(IFCONFIG_ARGS) + sizeof(IFCONFIG_BIN) + 50];
#ifdef linux
  struct ifreq ifr;
#endif

  tapif = (struct tapif *)netif->state;

  /* Obtain MAC address from network interface. */

  /* (We just fake an address...) */
  tapif->ethaddr->addr[0] = 0x1;
  tapif->ethaddr->addr[1] = 0x2;
  tapif->ethaddr->addr[2] = 0x3;
  tapif->ethaddr->addr[3] = 0x4;
  tapif->ethaddr->addr[4] = 0x5;
  tapif->ethaddr->addr[5] = 0x6;

  /* Do whatever else is needed to initialize interface. */

  tapif->fd = open(DEVTAP, O_RDWR);
  LWIP_DEBUGF(TAPIF_DEBUG, ("tapif_init: fd %d\n", tapif->fd));
  if(tapif->fd == -1) {
#ifdef linux
    perror("tapif_init: try running \"modprobe tun\" or rebuilding your kernel with CONFIG_TUN; cannot open "DEVTAP);
#else
    perror("tapif_init: cannot open "DEVTAP);
#endif
    exit(1);
  }

#ifdef linux
  memset(&ifr, 0, sizeof(ifr));
  if (name != NULL)
    strncpy(ifr.ifr_name,name,strlen(name));
  ifr.ifr_flags = IFF_TAP|IFF_NO_PI;
  if (ioctl(tapif->fd, TUNSETIFF, (void *) &ifr) < 0) {
    perror("tapif_init: "DEVTAP" ioctl TUNSETIFF");
    exit(1);
  }
  if (low_level_probe(netif,name != NULL ? name : ifr.ifr_name) != ERR_OK)
    exit(1);
  if (name == NULL) {
    sprintf(buf, IFCONFIG_BIN IFCONFIG_ARGS,
            ifr.ifr_name,
            ip4_addr1(&(netif->gw)),
            ip4_addr2(&(netif->gw)),
            ip4_addr3(&(netif->gw)),
            ip4_addr4(&(netif->gw)),
            ip4_addr1(&(netif->netmask)),
            ip4_addr2(&(netif->netmask)),
            ip4_addr3(&(netif->netmask)),
            ip4_addr4(&(netif->netmask)));

    LWIP_DEBUGF(TAPIF_DEBUG, ("tapif_init: system(\"%s\");\n", buf));
    system(buf);
  }
#else
  sprintf(buf, IFCONFIG_BIN IFCONFIG_ARGS,
          ip4_addr1(&(netif->gw)),
          ip4_addr2(&(netif->gw)),
          ip4_addr3(&(netif->gw)),
          ip4_addr4(&(netif->gw)));

  LWIP_DEBUGF(TAPIF_DEBUG, ("tapif_init: system(\"%s\");\n", buf));
  system(buf);
#endif
  sys_thread_new("tapif_thread", tapif_thread, netif, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);

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
#if 0
    if(((double)rand()/(double)RAND_MAX) < 0.2) {
    printf("drop output\n");
    return ERR_OK;
    }
#endif
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
/*-----------------------------------------------------------------------------------*/
/*
 * low_level_input():
 *
 * Should allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 */
/*-----------------------------------------------------------------------------------*/
static struct pbuf *
low_level_input(struct tapif *tapif)
{
  struct pbuf *p, *q;
  u16_t len;
  char buf[1514];
  char *bufptr;

  /* Obtain the size of the packet and put it into the "len"
     variable. */
  len = read(tapif->fd, buf, sizeof(buf));
#if 0
    if(((double)rand()/(double)RAND_MAX) < 0.2) {
    printf("drop\n");
    return NULL;
    }
#endif

  /* We allocate a pbuf chain of pbufs from the pool. */
  p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);

  if(p != NULL) {
    /* We iterate over the pbuf chain until we have read the entire
       packet into the pbuf. */
    bufptr = &buf[0];
    for(q = p; q != NULL; q = q->next) {
      /* Read enough bytes to fill this pbuf in the chain. The
         available data in the pbuf is given by the q->len
         variable. */
      /* read data into(q->payload, q->len); */
      memcpy(q->payload, bufptr, q->len);
      bufptr += q->len;
    }
    /* acknowledge that packet has been read(); */
  } else {
    /* drop packet(); */
  }

  return p;
}
/*-----------------------------------------------------------------------------------*/
static void
tapif_thread(void *arg)
{
  struct netif *netif;
  struct tapif *tapif;
  fd_set fdset;
  int ret;

  netif = (struct netif *)arg;
  tapif = (struct tapif *)netif->state;

  while(1) {
    FD_ZERO(&fdset);
    FD_SET(tapif->fd, &fdset);

    /* Wait for a packet to arrive. */
    ret = select(tapif->fd + 1, &fdset, NULL, NULL, NULL);

    if(ret == 1) {
      /* Handle incoming packet. */
      tapif_input(netif);
    } else if(ret == -1) {
      perror("tapif_thread: select");
    }
  }
}
/*-----------------------------------------------------------------------------------*/
/*
 * tapif_input():
 *
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface.
 *
 */
/*-----------------------------------------------------------------------------------*/
static void
tapif_input(struct netif *netif)
{
  struct tapif *tapif;
  struct eth_hdr *ethhdr;
  struct pbuf *p;


  tapif = (struct tapif *)netif->state;

  p = low_level_input(tapif);

  if(p == NULL) {
    LWIP_DEBUGF(TAPIF_DEBUG, ("tapif_input: low_level_input returned NULL\n"));
    return;
  }
  ethhdr = (struct eth_hdr *)p->payload;

  switch(htons(ethhdr->type)) {
  /* IP or ARP packet? */
  case ETHTYPE_IP:
  case ETHTYPE_ARP:
#if PPPOE_SUPPORT
  /* PPPoE packet? */
  case ETHTYPE_PPPOEDISC:
  case ETHTYPE_PPPOE:
#endif /* PPPOE_SUPPORT */
    /* full packet send to tcpip_thread to process */
    if (netif->input(p, netif) != ERR_OK) {
      LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
       pbuf_free(p);
       p = NULL;
    }
    break;
  default:
    pbuf_free(p);
    break;
  }
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
  netif->output = etharp_output;
  netif->linkoutput = low_level_output;
  netif->mtu = 1500;
  /* hardware address length */
  netif->hwaddr_len = 6;

  tapif->ethaddr = (struct eth_addr *)&(netif->hwaddr[0]);

  netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_IGMP;

  low_level_init(netif,name);

  return ERR_OK;
}
/*-----------------------------------------------------------------------------------*/
