# SPDX-FileCopyrightText: 2022 Marian Sauer
#
# SPDX-License-Identifier: BSD-2-Clause

add_library(lwip_tap_static STATIC "src/tapif.c")
target_include_directories(lwip_tap_static PUBLIC "inc")
target_link_libraries(lwip_tap_static PUBLIC lib::static::lwip)

add_library(lib::static::lwip_tap ALIAS lwip_tap_static)