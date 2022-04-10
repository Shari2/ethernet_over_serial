// Copyright (c) 2001-2003 Swedish Institute of Computer Science.
// Copyright (c) 2012-2013 Takayuki Usui
//
// SPDX-License-Identifier: BSD-3-Clause
//
// Author: Adam Dunkels <adam@sics.se>

#ifndef __TAPIF_H__
#define __TAPIF_H__

#include "lwip/netif.h"

struct tapif {
  /* Add whatever per-interface state that is needed here. */
  int fd;
  char *name;
  ip_addr_t ip_addr;
  ip_addr_t netmask;
  ip_addr_t gw;
  struct pbuf * p;
};

err_t tapif_init(struct netif *netif);

void tapif_poll(struct netif *netif);

#endif /* __TAPIF_H__ */
