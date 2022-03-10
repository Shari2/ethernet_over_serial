cmake_minimum_required(VERSION 3.16)
project(lwip_icmp_server)

add_compile_options(-fdata-sections -ffunction-sections)
add_link_options(-Wl,--gc-sections)

add_library(port STATIC "port/arch/sys_arch.c")
target_include_directories(port PUBLIC "port")

set(LWIP_CORE "lwip/src/core")

add_library(lwip STATIC "${LWIP_CORE}/init.c")

target_sources(lwip PRIVATE
  "lwip/src/core/ipv4/icmp.c"
  "lwip/src/core/ipv4/ip4.c"
  "lwip/src/core/ipv4/ip4_addr.c"
)
  
target_sources(lwip PRIVATE
  "lwip/src/core/netif.c"
  "lwip/src/core/timeouts.c"
  "lwip/src/core/stats.c"
  "lwip/src/core/mem.c"
  "lwip/src/core/memp.c"
  "lwip/src/core/ip.c"
  "lwip/src/core/pbuf.c"
  "lwip/src/core/def.c"
  "lwip/src/core/inet_chksum.c"
)

target_sources(lwip PRIVATE
  "lwip/src/netif/slipif.c"
)

target_include_directories(lwip PUBLIC "lwip/src/include")
target_link_libraries(lwip PUBLIC port)
add_library(lib::static::lwip ALIAS lwip)

add_executable(icmp_server main.c)
target_link_libraries(icmp_server PRIVATE lib::static::lwip)
target_link_options(icmp_server PRIVATE -Xlinker -Map=icmp_server.map)

add_custom_command(TARGET icmp_server POST_BUILD COMMAND size -x -t $<TARGET_FILE:icmp_server>)