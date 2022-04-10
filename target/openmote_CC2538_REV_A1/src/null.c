// SPDX-FileCopyrightText: 2022 Marian Sauer
//
// SPDX-License-Identifier: BSD-2-Clause

#include "arch/cc.h"
#include <unistd.h>
#include <stdint.h>

#include "openmote_cc2538/leds.h"


int usleep(useconds_t a)
{
  volatile uint32_t cycle_burn = (1<<10) * a;
  while(cycle_burn--);
}

void
abort(void)
{
  leds_error_on();
  while(1);
}



#if 0

#define ENOMEM      12
uint32_t errno = 0;

void *
_sbrk (int  incr)
{
    extern char __heap_start;//set by linker
    extern char __heap_end;//set by linker

    static char *heap_end;      /* Previous end of heap or 0 if none */
    char        *prev_heap_end;

    if (0 == heap_end) {
        heap_end = &__heap_start;           /* Initialize first time round */
    }

    prev_heap_end  = heap_end;
    heap_end      += incr;
    //check
    if( heap_end < (&__heap_end)) {

    } else {
        errno = ENOMEM;
        return (char*)-1;
    }
    return (void *) prev_heap_end;

}
#endif

#if 0
int fflush (void *__stream)
{
  return 0;
}
#endif

#if 0
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

#endif
