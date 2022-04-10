# SPDX-FileCopyrightText: 2022 Marian Sauer
#
# SPDX-License-Identifier: BSD-2-Clause

add_library(port STATIC
  "src/port/arch/sys_arch.c"
   "src/port/arch/sio.c"
)
target_include_directories(port PUBLIC "inc/port")
add_library(lib::static::port ALIAS port)