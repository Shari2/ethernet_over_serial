// SPDX-FileCopyrightText: 2022 Marian Sauer
//
// SPDX-License-Identifier: BSD-2-Clause

#include "ti_bsp/sys_ctrl.h"
#include "ti_bsp/uart.h"
#include "ti_bsp/gpio.h"
#include "ti_bsp/ioc.h"
#include "ti_bsp/hw/hw_memmap.h"
#include "ti_bsp/hw/hw_ioc.h"

#define UART0_PIN_UART_RXD            GPIO_PIN_0
#define UART0_PIN_UART_TXD            GPIO_PIN_1
#define UART0_GPIO_BASE               GPIO_A_BASE

uint32_t
uart0_instance(void)
{
  return UART0_BASE;
}

void
uart0_startup(void)
{
  SysCtrlIOClockSet(SYS_CTRL_SYSDIV_32MHZ);
  SysCtrlPeripheralEnable(SYS_CTRL_PERIPH_UART0);
  UARTDisable(uart0_instance());

  UARTIntDisable(uart0_instance(),
                 0x1FFF);

  UARTClockSourceSet(uart0_instance(),
                     UART_CLOCK_PIOSC);

  IOCPinConfigPeriphOutput(UART0_GPIO_BASE,
                           UART0_PIN_UART_TXD,
                           IOC_MUX_OUT_SEL_UART0_TXD);

  GPIOPinTypeUARTOutput(UART0_GPIO_BASE,
                        UART0_PIN_UART_TXD);

  IOCPinConfigPeriphInput(UART0_GPIO_BASE,
                          UART0_PIN_UART_RXD,
                          IOC_UARTRXD_UART0);

  GPIOPinTypeUARTInput(UART0_GPIO_BASE,
                       UART0_PIN_UART_RXD);

  UARTConfigSetExpClk(uart0_instance(),
                      SysCtrlClockGet(),
                      1000000,
                      (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                      UART_CONFIG_PAR_NONE));

  UARTEnable(uart0_instance());
}

int _write(int file, char *ptr, int len)
{
  for(int i = 0; i < len; i++)
  {
    //UARTCharPut(uart0_instance(), *(ptr + i));
  }
  return len;
}


