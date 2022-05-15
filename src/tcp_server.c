// SPDX-FileCopyrightText: 2022 Marian Sauer
//
// SPDX-License-Identifier: BSD-2-Clause

#include "server/tcp.h"

#if defined(LWIP_TCP) && LWIP_TCP
#include "lwip/tcp.h"

#include <string.h>

static struct tcp_pcb * server_instance(struct tcp_pcb * replaced)
{
  static struct tcp_pcb * instance = NULL;
  if(!instance)
  {
    instance = tcp_new();
  } else if(replaced) {
    /* The tcp_listen() function returns a new connection identifier, and the one passed as an argument to the function will be deallocated. */
    instance = replaced;
  }
  return instance;
}

struct tcp_session_data
{
  uint32_t a;
};

static uint8_t * reply = NULL;

err_t tcp_sent_callback(void *arg, struct tcp_pcb *tpcb,
                              u16_t len)
{
  mem_free(reply);
  reply = NULL;
  return ERR_OK;
}

err_t tcp_receive_callback(void *arg, struct tcp_pcb *tpcb,
                             struct pbuf *p, err_t err)
{
  static uint8_t msg[] = "dave is not here man";

  if (p)
  {
    pbuf_free(p);
    tcp_recved(tpcb, p->tot_len);

    if(!reply)
    {
      reply = mem_malloc(sizeof(msg));
      memcpy(reply, msg, sizeof(msg));
      tcp_write(tpcb, reply, sizeof(msg), 0);
    }

  } else {
    /* p = NULL indicated connection closed */
    mem_free(arg);
    tcp_close(tpcb);
  }


  if (err != ERR_OK) {
    /* connection closed by remote */
    tcp_close(tpcb);
  }
  return ERR_OK;
}

static err_t
tcp_accept_callback(void *arg, struct tcp_pcb *pcb, err_t err)
{

  struct tcp_session_data * ctx = (struct tcp_session_data*) mem_malloc(sizeof(struct tcp_session_data));
  tcp_arg(pcb, ctx);
  tcp_recv(pcb, tcp_receive_callback);
  tcp_sent(pcb, tcp_sent_callback);

  return ERR_OK;
}

void tcp_server_setup(void)
{
  struct tcp_pcb * server = server_instance(NULL);
  tcp_bind(server, &netif_default->ip_addr, USECASE_SERVER_PORT);
  struct tcp_pcb * listen_server = tcp_listen(server);
  server_instance(listen_server);
  tcp_accept(listen_server, tcp_accept_callback);
}

#else

// null impl

void tcp_server_setup(void)
{

}
#endif
