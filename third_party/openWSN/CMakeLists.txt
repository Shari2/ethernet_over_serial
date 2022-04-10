# SPDX-FileCopyrightText: 2022 Marian Sauer
#
# SPDX-License-Identifier: BSD-2-Clause

add_library(openmote_cc2538_static STATIC
  "src/leds.c"
)

target_include_directories(openmote_cc2538_static PUBLIC "inc")
target_link_libraries(openmote_cc2538_static PUBLIC lib::static::ti_bsp)

add_library(lib::static::openmote_cc2538 ALIAS openmote_cc2538_static)

