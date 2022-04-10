// SPDX-FileCopyrightText: 2022 Marian Sauer
//
// SPDX-License-Identifier: BSD-2-Clause

#include "arch/cc.h"
#include <unistd.h>
#include <stdint.h>


int usleep(useconds_t a)
{
}


int printf (const char *__restrict __format, ...)
{
  return 0;
}

int fflush (void *__stream)
{
  return 0;
}

void abort (void)
{
  while(1);
}

void *memset(void *__s, int __c, size_t __n)
{
  for(uint8_t* ptr = __s; ptr != (ptr +__n); ptr++)
  {
    *ptr = __c;
  }

  return __s;
}

void *memcpy(void *__restrict __dest, const void *__restrict __src,
             size_t __n)
{
  for(const uint8_t* ptr = __src; ptr != ((uint8_t*)__src) + __n; ptr++)
  {
    *(uint8_t*)__dest = *ptr;
  }

  return __dest;
}

