add_library(port STATIC "src/port/arch/sys_arch.c")
target_include_directories(port PUBLIC "inc/port")
add_library(lib::static::port ALIAS port)