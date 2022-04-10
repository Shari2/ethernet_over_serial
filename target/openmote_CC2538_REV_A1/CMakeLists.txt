# SPDX-FileCopyrightText: 2022 Marian Sauer
#
# SPDX-License-Identifier: BSD-2-Clause

add_library(port STATIC
  "src/port/arch/sys_arch.c"
  "src/startup_gcc.c"
  "src/null.c"
  "src/uart0_startup.c"
  "src/sio.c"
)
target_include_directories(port PUBLIC "inc/port")
add_library(lib::static::port ALIAS port)

target_link_libraries(port PUBLIC lib::static::openmote_cc2538 lib::static::ti_bsp)