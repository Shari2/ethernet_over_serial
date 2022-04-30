# SPDX-FileCopyrightText: 2022 Marian Sauer
#
# SPDX-License-Identifier: BSD-2-Clause

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")


set(GCC_X86_COMMON_FLAGS "-ffunction-sections -fdata-sections")
set(GCC_X86_32BIT_FLAGS "-m32 -Xlinker --gc-sections")

set(CMAKE_CXX_FLAGS_INIT "${GCC_X86_COMMON_FLAGS} ${GCC_X86_32BIT_FLAGS}")
set(CMAKE_C_FLAGS_INIT "${GCC_X86_COMMON_FLAGS} ${GCC_X86_32BIT_FLAGS}")
