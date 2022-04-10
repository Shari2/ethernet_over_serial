# SPDX-FileCopyrightText: 2022 Marian Sauer
#
# SPDX-License-Identifier: BSD-2-Clause

add_library(ti_bsp_static STATIC
  "src/adc.c"
  "src/aes.c"
  "src/ccm.c"
  "src/cpu.c"
  "src/debug.c"
  "src/flash.c"
  "src/gpio.c"
  "src/gptimer.c"
  "src/i2c.c"
  "src/interrupt.c"
  "src/ioc.c"
  "src/pka.c"
  "src/sleepmode.c"
  "src/ssi.c"
  "src/sys_ctrl.c"
  "src/systick.c"
  "src/uart.c"
  "src/udma.c"
  "src/watchdog.c"
)

add_library(lib::static::ti_bsp ALIAS ti_bsp_static)

target_include_directories(ti_bsp_static PUBLIC "inc")