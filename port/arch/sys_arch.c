// SPDX-FileCopyrightText: 2022 Marian Sauer
//
// SPDX-License-Identifier: BSD-2-Clause

#include <time.h>
#include <stdint.h>

static void
get_monotonic_time(struct timespec *ts)
{
  clock_gettime(CLOCK_MONOTONIC,
                ts);
}

uint32_t
sys_now(void)
{
  struct timespec ts;

  get_monotonic_time(&ts);
  return (uint32_t) (ts.tv_sec * 1000L + ts.tv_nsec / 1000000L);
}
