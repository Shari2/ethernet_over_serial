# SPDX-FileCopyrightText: 2022 Marian Sauer
#
# SPDX-License-Identifier: BSD-2-Clause

# maybe required libnewlib-arm-none-eabi

set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")


set(GCC_CORTEX_M3_COMMON_FLAGS "-ffunction-sections -fdata-sections")
set(GCC_CORTEX_M3_32BIT_FLAGS "-mcpu=cortex-m3 -mthumb -Xlinker --gc-sections -nostartfiles -nostdlib")



set(CMAKE_CXX_FLAGS_INIT "${GCC_CORTEX_M3_COMMON_FLAGS} ${GCC_CORTEX_M3_32BIT_FLAGS}")
set(CMAKE_C_FLAGS_INIT "${GCC_CORTEX_M3_COMMON_FLAGS} ${GCC_CORTEX_M3_32BIT_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-Xlinker -T \"${CMAKE_SOURCE_DIR}/third_party/openWSN/cc2538sf23.lds\"")


# project specific variable
set(PORT_OPENMOTE_CC2538 1)