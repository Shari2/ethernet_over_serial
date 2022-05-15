# SPDX-FileCopyrightText: 2022 Marian Sauer
#
# SPDX-License-Identifier: BSD-2-Clause

add_library(lwip_tap_static STATIC "src/tapif.c")
target_include_directories(lwip_tap_static PUBLIC "inc")
# linking just for the includes, should not matter if lwip_udp or lwip_tcp is linked
target_link_libraries(lwip_tap_static PRIVATE lib::static::lwip_udp)

add_library(lib::static::lwip_tap ALIAS lwip_tap_static)
