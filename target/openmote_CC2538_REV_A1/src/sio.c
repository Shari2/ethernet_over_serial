// SPDX-FileCopyrightText: 2022 Marian Sauer
//
// SPDX-License-Identifier: BSD-2-Clause

#include "arch/cc.h"
#include "ti_bsp/uart.h"
#include <stdint.h>


extern uint32_t uart0_instance(void);

void
sio_send(uint8_t c, sio_fd_t fd)
{
  UARTCharPut(fd, c);
}

sio_fd_t
sio_open(uint8_t devnum)
{
  switch(devnum)
  {
    case 3:
      return uart0_instance();
    default:
      return 0;
  }
}

uint32_t
sio_tryread(sio_fd_t fd, uint8_t *data, uint32_t len)
{
  int32_t c = UARTCharGetNonBlocking(fd);

  if(c < 0)
  {
    *data = 0;
    return 0;
  } else {
    *data = c;
    itm_port0_putc(c);
    return 1;
  }
}
