#include "lwip/init.h"
#include "lwip/ip.h"
#include "lwip/timeouts.h"
#include "lwip/sio.h"
#include "netif/slipif.h"

#include <stdint.h>
#include <stddef.h>

void
sio_send(u8_t c, sio_fd_t context)
{

}

sio_fd_t
sio_open(u8_t devnum)
{
  return 1;
}

uint32_t
sio_tryread(sio_fd_t fd, uint8_t *data, uint32_t len)
{
  *data = ' ';
  return 1;
}

int
main(int argc, char **argv)
{
  uint8_t num_slip1 = 0;
  ip4_addr_t ipaddr_slip1;
  ip4_addr_t netmask_slip1;
  ip4_addr_t gw_slip1;
  struct netif slipif1;

  lwip_init();

  IP4_ADDR(&ipaddr_slip1,
           172,
           30,
           115,
           84);
  IP4_ADDR(&netmask_slip1,
           255,
           255,
           255,
           0);
  IP4_ADDR(&gw_slip1,
           172,
           30,
           115,
           1);

  struct netif *ret = netif_add(&slipif1,
                                &ipaddr_slip1,
                                &netmask_slip1,
                                &gw_slip1,
                                &num_slip1,
                                slipif_init,
                                ip_input);
  LWIP_ASSERT("netif_add failed",
              ret == &slipif1);

  netif_set_default(&slipif1);

  netif_set_up(&slipif1);
  netif_set_link_up(&slipif1);

  while (1)
  {
    sys_check_timeouts();
    slipif_poll(&slipif1);
  }

}
