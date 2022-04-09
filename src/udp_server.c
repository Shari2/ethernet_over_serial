#include "server/udp.h"
#include "lwip/udp.h"

#if defined(LWIP_UDP) && LWIP_UDP

static struct udp_pcb * server_instance()
{
  static struct udp_pcb * instance = NULL;
  if(!instance)
  {
    instance = udp_new();
  }
  return instance;
}

static void
udp_recv_callback(void *arg, struct udp_pcb *pcb, struct pbuf *p,
                  const ip_addr_t *addr, u16_t port)
{

  udp_sendto(pcb, p, addr, port);

  if(p)
  {
    pbuf_free(p);
  }
}

void udp_server_setup(void)
{
  struct udp_pcb * server = server_instance();
  udp_bind(server, &netif_default->ip_addr, USECASE_SERVER_PORT);
  udp_recv(server, udp_recv_callback, NULL);
}

#else

// null impl

void udp_server_setup(void)
{

}
#endif
