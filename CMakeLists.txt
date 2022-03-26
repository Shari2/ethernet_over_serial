# SPDX-FileCopyrightText: 2022 Marian Sauer
#
# SPDX-License-Identifier: BSD-2-Clause

cmake_minimum_required(VERSION 3.16)
project(lwip_icmp_server)

add_compile_options(-fdata-sections -ffunction-sections)
add_link_options(-Wl,--gc-sections)

add_library(port STATIC "src/port/arch/sys_arch.c")
target_include_directories(port PUBLIC "inc/port")

set(LWIP_SRC "third_party/lwip/src")
set(LWIP_CORE "${LWIP_SRC}/core")

add_library(lwip STATIC "${LWIP_CORE}/init.c")

target_sources(lwip PRIVATE
  "${LWIP_CORE}/ipv4/icmp.c"
  "${LWIP_CORE}/ipv4/ip4.c"
  "${LWIP_CORE}/ipv4/ip4_addr.c"
)
  
target_sources(lwip PRIVATE
  "${LWIP_CORE}/netif.c"
  "${LWIP_CORE}/timeouts.c"
  "${LWIP_CORE}/stats.c"
  "${LWIP_CORE}/mem.c"
  "${LWIP_CORE}/memp.c"
  "${LWIP_CORE}/ip.c"
  "${LWIP_CORE}/pbuf.c"
  "${LWIP_CORE}/def.c"
  "${LWIP_CORE}/inet_chksum.c"
)



target_sources(lwip PRIVATE
  "${LWIP_SRC}/netif/slipif.c"
)

target_include_directories(lwip PUBLIC "${LWIP_SRC}/include")
target_link_libraries(lwip PUBLIC port)
add_library(lib::static::lwip ALIAS lwip)

add_executable(icmp_server "src/main.c")
target_link_libraries(icmp_server PRIVATE lib::static::lwip)
target_link_options(icmp_server PRIVATE -Xlinker -Map=icmp_server.map)

add_custom_command(TARGET icmp_server POST_BUILD COMMAND size -x -t $<TARGET_FILE:icmp_server>)