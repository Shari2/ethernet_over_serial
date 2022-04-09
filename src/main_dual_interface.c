// SPDX-FileCopyrightText: 2022 Marian Sauer
//
// SPDX-License-Identifier: BSD-2-Clause

#include "lwip/init.h"
#include "lwip/ip.h"
#include "lwip/timeouts.h"
#include "lwip/sio.h"
#include "netif/slipif.h"

#include <stdint.h>
#include <stddef.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

void
sio_send(u8_t c, sio_fd_t fd)
{
  int ret = write(fd,
                  &c,
                  sizeof(c));
#if 0
  if (ret)
  {
    printf("-> %u 0x%02x\n",
           (uint32_t) time(NULL),
           c);
  }
#endif
}

sio_fd_t
sio_open(u8_t devnum)
{
  char dev_name[] = "/dev/tnt255";
  snprintf(dev_name, sizeof(dev_name), "/dev/tnt%u", devnum);
  int fd = open(dev_name,
                O_NONBLOCK | O_RDWR);

  return (fd > 0) ? fd : 0;
}

uint32_t
sio_tryread(sio_fd_t fd, uint8_t *data, uint32_t len)
{
  int ret = read(fd,
                 data,
                 len);
#if 0
  return (ret > 0) ? printf("<- %u 0x%02x\n",
                            (uint32_t) time(NULL),
                            *data), ret :
                     0;
#else
  return (ret > 0) ? ret : 0;
#endif
}

int
main(int argc, char **argv)
{
  struct netif slipif1;
  struct netif slipif2;

  lwip_init();

  struct netif *ret;

  {
    ptrdiff_t num_slip1 = 1; // tnt1
    ip4_addr_t ipaddr_slip1;
    ip4_addr_t netmask_slip1;
    ip4_addr_t gw_slip1;
    IP4_ADDR(&ipaddr_slip1,
             10,
             0,
             0,
             1);
    IP4_ADDR(&netmask_slip1,
             255,
             254,
             0,
             0);
    IP4_ADDR(&gw_slip1,
             0,
             0,
             0,
             0);

    ret = netif_add(&slipif1,
                    &ipaddr_slip1,
                    &netmask_slip1,
                    &gw_slip1,
                    (void *)num_slip1,
                    slipif_init,
                    ip_input);
  }

  LWIP_ASSERT("netif_add failed",
              ret == &slipif1);

  netif_set_default(&slipif1);

  netif_set_up(&slipif1);
  netif_set_link_up(&slipif1);


  {
    ptrdiff_t num_slip2 = 2; // tnt2
    ip4_addr_t ipaddr_slip2;
    ip4_addr_t netmask_slip2;
    ip4_addr_t gw_slip2;
    IP4_ADDR(&ipaddr_slip2,
             10,
             1,
             0,
             1);
    IP4_ADDR(&netmask_slip2,
             255,
             255,
             0,
             0);
    IP4_ADDR(&gw_slip2,
             0,
             0,
             0,
             0);

    ret = netif_add(&slipif2,
                    &ipaddr_slip2,
                    &netmask_slip2,
                    &gw_slip2,
                    (void *)num_slip2,
                    slipif_init,
                    ip_input);
  }

  LWIP_ASSERT("netif_add failed",
              ret == &slipif2);

  netif_set_up(&slipif2);
  netif_set_link_up(&slipif2);

  while (1)
  {
    //sys_check_timeouts();
    slipif_poll(&slipif1);
    slipif_poll(&slipif2);
    usleep(100);
  }

}
