// SPDX-FileCopyrightText: 2022 Marian Sauer
//
// SPDX-License-Identifier: BSD-2-Clause

#include "server/udp.h"
#include "server/tcp.h"

#include "lwip/init.h"
#include "lwip/ip.h"
#include "lwip/timeouts.h"
#include "lwip/sio.h"
#include "netif/slipif.h"

#include <unistd.h>

int
main(int argc, char **argv)
{
// goal: HDLC in Normal response mode (because RS485 is shared by secondaries)
// a) primary requests -> one of n secondary replies
// or
// b) primary request -> timeout (100 ms)

  ptrdiff_t num_slip1 = 3; // tnt3
  ip4_addr_t ipaddr_slip1;
  ip4_addr_t netmask_slip1;
  ip4_addr_t gw_slip1;
  struct netif slipif1;

  lwip_init();

  IP4_ADDR(&ipaddr_slip1,
           10,
           1,
           0,
           2);
  IP4_ADDR(&netmask_slip1,
           255,
           255,
           0,
           0);
  IP4_ADDR(&gw_slip1,
           10,
           1,
           0,
           1);

  struct netif *ret = netif_add(&slipif1,
                                &ipaddr_slip1,
                                &netmask_slip1,
                                &gw_slip1,
                                (void *)num_slip1,
                                slipif_init,
                                ip_input);
  LWIP_ASSERT("netif_add failed",
              ret == &slipif1);

  netif_set_default(&slipif1);

  netif_set_up(&slipif1);
  netif_set_link_up(&slipif1);


  #if defined(LWIP_UDP) && LWIP_UDP
    udp_server_setup();
  #endif


  #if defined(LWIP_TCP) && LWIP_TCP
    tcp_server_setup();
  #endif



  while (1)
  {
    sys_check_timeouts(); // required for tcp
    slipif_poll(&slipif1);
  }

}
