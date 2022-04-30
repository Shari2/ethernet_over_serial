// SPDX-FileCopyrightText: 2022 Marian Sauer
//
// SPDX-License-Identifier: BSD-2-Clause

#include "arch/cc.h"
#include <stdint.h>

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#include <termios.h>

void
sio_send(uint8_t c, sio_fd_t fd)
{
  int ret = write(fd,
                  &c,
                  sizeof(c));

  if(ret < 0)
  {
    perror("sio_send");
  }
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
sio_open(uint8_t devnum)
{
  char dev_name[] = "/dev/ttyUSB255";
  snprintf(dev_name, sizeof(dev_name), "/dev/ttyUSB%u", devnum);
  int fd = open(dev_name,
                O_NONBLOCK | O_RDWR);

  {
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
      perror("Error from tcgetattr: ");
      return -1;
    }

    cfmakeraw(&tty);

    cfsetospeed(&tty, B1000000);
    cfsetispeed(&tty, B1000000);



    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
      perror("Error from tcsetattr: ");
      return -1;
    }

    tcflush(fd, TCIOFLUSH);
  }


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
