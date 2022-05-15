# SPDX-FileCopyrightText: 2022 Marian Sauer
#
# SPDX-License-Identifier: BSD-2-Clause

cmake_minimum_required(VERSION 3.16)
project(lwip_icmp_server)



if(PORT_OPENMOTE_CC2538)
  add_subdirectory(third_party/openWSN)
  add_subdirectory(third_party/ti)
  add_subdirectory(target/openmote_CC2538_REV_A1)
else()
  add_subdirectory(target/pc)
  add_subdirectory(third_party/lwip-tap)
endif()


# lwipopts.h is shared by all ports
target_include_directories(port PUBLIC "inc/port")


set(LWIP_SRC "third_party/lwip/src")
set(LWIP_CORE "${LWIP_SRC}/core")

set(LWIP_COMMON_SOURCES 
  "${LWIP_CORE}/init.c"
  "${LWIP_CORE}/ipv4/icmp.c"
  "${LWIP_CORE}/ipv4/ip4.c"
  "${LWIP_CORE}/ipv4/ip4_addr.c"
  "${LWIP_CORE}/netif.c"
  "${LWIP_CORE}/timeouts.c"
  "${LWIP_CORE}/stats.c"
  "${LWIP_CORE}/mem.c"
  "${LWIP_CORE}/memp.c"
  "${LWIP_CORE}/ip.c"
  "${LWIP_CORE}/pbuf.c"
  "${LWIP_CORE}/def.c"
  "${LWIP_CORE}/inet_chksum.c"
  "${LWIP_SRC}/netif/slipif.c"
)

add_library(lwip_udp STATIC
  ${LWIP_COMMON_SOURCES}
  "${LWIP_CORE}/udp.c"
)

add_library(lwip_tcp STATIC
  ${LWIP_COMMON_SOURCES}
  "${LWIP_CORE}/tcp.c"
  "${LWIP_CORE}/tcp_in.c"
  "${LWIP_CORE}/tcp_out.c"
)

target_include_directories(lwip_udp PUBLIC "${LWIP_SRC}/include")
target_link_libraries(lwip_udp PUBLIC port)
target_compile_options(lwip_udp PUBLIC -DLWIP_UDP=1 -DLWIP_TCP=0)
add_library(lib::static::lwip_udp ALIAS lwip_udp)

target_include_directories(lwip_tcp PUBLIC "${LWIP_SRC}/include")
target_link_libraries(lwip_tcp PUBLIC port)
target_compile_options(lwip_tcp PUBLIC -DLWIP_UDP=0 -DLWIP_TCP=1)
add_library(lib::static::lwip_tcp ALIAS lwip_tcp)


add_executable(icmp_server "src/main.c" "src/udp_server.c")
target_include_directories(icmp_server PUBLIC "inc/usecase/")
target_link_libraries(icmp_server PRIVATE lib::static::lwip_udp)
target_link_options(icmp_server PRIVATE -Xlinker -Map=icmp_server.map)

add_custom_command(TARGET icmp_server POST_BUILD COMMAND size -t $<TARGET_FILE:icmp_server>)
if(PORT_OPENMOTE_CC2538)
  add_custom_command(TARGET icmp_server POST_BUILD COMMAND arm-none-eabi-objcopy -O ihex $<TARGET_FILE:icmp_server> $<TARGET_FILE_BASE_NAME:icmp_server>.ihex )

  add_custom_target(
  flash_cc2538_with_icmp_server
  COMMAND ./third_party/openWSN/cc2538-bsl.py -e --bootloader-invert-lines -w -b 115200 -p /dev/ttyUSB0 "$<TARGET_FILE_DIR:icmp_server>/$<TARGET_FILE_BASE_NAME:icmp_server>.ihex"
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  )
endif()

# tun/tap only avilable on pc
if(NOT PORT_OPENMOTE_CC2538)
  add_executable(icmp_server_dual_interface "src/main_dual_interface.c")
  target_link_libraries(icmp_server_dual_interface PRIVATE lib::static::lwip_tap lib::static::lwip_udp)
  target_link_options(icmp_server_dual_interface PRIVATE -Xlinker -Map=icmp_server_dual_interface.map)

  add_custom_command(TARGET icmp_server_dual_interface POST_BUILD COMMAND size -t $<TARGET_FILE:icmp_server_dual_interface>)
endif()


add_executable(tcp_server "src/main.c" "src/tcp_server.c")
target_include_directories(tcp_server PUBLIC "inc/usecase/")
target_link_libraries(tcp_server PRIVATE lib::static::lwip_tcp)
target_link_options(tcp_server PRIVATE -Xlinker -Map=tcp_server.map)
add_custom_command(TARGET tcp_server POST_BUILD COMMAND size -t $<TARGET_FILE:tcp_server>)