// SPDX-FileCopyrightText: 2022 Marian Sauer
//
// SPDX-License-Identifier: BSD-2-Clause

#include "lwip/init.h"
#include "lwip/ip.h"
#include "lwip/timeouts.h"
#include "lwip/sio.h"
#include "netif/slipif.h"
#include "lwip_tap/tapif.h"

#include <string.h>

int
main(int argc, char **argv)
{
  struct netif tapif1;
  struct netif slipif2;

  lwip_init();

  struct netif *ret;

  {
    ip4_addr_t ipaddr_tap1;
    ip4_addr_t netmask_tap1;
    ip4_addr_t gw_tap1;
    IP4_ADDR(&ipaddr_tap1,
             10,
             0,
             0,
             1);
    IP4_ADDR(&netmask_tap1,
             255,
             254,
             0,
             0);
    IP4_ADDR(&gw_tap1,
             0,
             0,
             0,
             0);

    ret = netif_add(&tapif1,
                    &ipaddr_tap1,
                    &netmask_tap1,
                    &gw_tap1,
                    NULL,
                    tapif_init,
                    ip_input);
  }

  LWIP_ASSERT("netif_add failed",
              ret == &tapif1);

  netif_set_default(&tapif1);

  netif_set_up(&tapif1);
  netif_set_link_up(&tapif1);

#if 1
  {
    ptrdiff_t num_slip2 = 0; // USB0
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
#endif

  while (1)
  {
    //sys_check_timeouts();
    tapif_poll(&tapif1);
    slipif_poll(&slipif2);
    usleep(100);
  }

}
