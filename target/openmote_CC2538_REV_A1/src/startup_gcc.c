// SPDX-FileCopyrightText: 2022 Marian Sauer
//
// SPDX-License-Identifier: BSD-2-Clause
//
// Based on openwsn startup_gcc.c

#include "ti_bsp/hw/hw_nvic.h"
#include "ti_bsp/sys_ctrl.h"
#include "openmote_cc2538/leds.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define FLASH_START_ADDR                0x00200000
#define BOOTLOADER_BACKDOOR_ENABLE      0xF6FFFFFF // ENABLED: PORT A, PIN 6, LOW
#define SYS_CTRL_EMUOVR                 0x400D20B4

extern int main(int argc, char** argv);

void ResetISR(void);
void NmiSR(void);
void FaultISR(void);
void IntDefaultHandler(void);


//*****************************************************************************
//
// Customer Configuration Area in Lock Page
// Holds Application entry point (bytes 2012 - 2015) and
// Image Valid (bytes 2008 - 2011) and
// Bootloader backdoor (byte 2007) and
// Reserved (byte 2006 - 2004)
//
//*****************************************************************************
typedef struct
{
    uint32_t ui32BootldrCfg;
    uint32_t ui32ImageValid;
    uint32_t ui32ImageVectorAddr;
}
lockPageCCA_t;

__attribute__ ((section(".flashcca"), used))
const lockPageCCA_t __cca =
{
  BOOTLOADER_BACKDOOR_ENABLE,  // Bootloader backdoor enabled
  0,                           // Image valid bytes
  FLASH_START_ADDR             // Vector table located at flash start address
};

__attribute__ ((section(".vectors"), used))
void (* const gVectors[])(void) =
{
  ResetISR,                               // Reset handler
  NmiSR,                                  // The NMI handler
  FaultISR,                               // The hard fault handler
  IntDefaultHandler,                      // 4 The MPU fault handler
  IntDefaultHandler,                      // 5 The bus fault handler
  IntDefaultHandler,                      // 6 The usage fault handler
  0,                                      // 7 Reserved
  0,                                      // 8 Reserved
  0,                                      // 9 Reserved
  0,                                      // 10 Reserved
  IntDefaultHandler,                      // 11 SVCall handler
  IntDefaultHandler,                      // 12 Debug monitor handler
  0,                                      // 13 Reserved
  IntDefaultHandler,                      // 14 The PendSV handler
  IntDefaultHandler,                      // 15 The SysTick handler
  IntDefaultHandler,                      // 16 GPIO Port A
  IntDefaultHandler,                      // 17 GPIO Port B
  IntDefaultHandler,                      // 18 GPIO Port C
  IntDefaultHandler,                      // 19 GPIO Port D
  0,                                      // 20 none
  IntDefaultHandler,                      // 21 UART0 Rx and Tx
  IntDefaultHandler,                      // 22 UART1 Rx and Tx
  IntDefaultHandler,                      // 23 SSI0 Rx and Tx
  IntDefaultHandler,                      // 24 I2C Master and Slave
  0,                                      // 25 Reserved
  0,                                      // 26 Reserved
  0,                                      // 27 Reserved
  0,                                      // 28 Reserved
  0,                                      // 29 Reserved
  IntDefaultHandler,                      // 30 ADC Sequence 0
  0,                                      // 31 Reserved
  0,                                      // 32 Reserved
  0,                                      // 33 Reserved
  IntDefaultHandler,                      // 34 Watchdog timer, timer 0
  IntDefaultHandler,                      // 35 Timer 0 subtimer A
  IntDefaultHandler,                      // 36 Timer 0 subtimer B
  IntDefaultHandler,                      // 37 Timer 1 subtimer A
  IntDefaultHandler,                      // 38 Timer 1 subtimer B
  IntDefaultHandler,                      // 39 Timer 2 subtimer A
  IntDefaultHandler,                      // 40 Timer 2 subtimer B
  IntDefaultHandler,                      // 41 Analog Comparator 0
  IntDefaultHandler,                      // 42 RFCore Rx/Tx
  IntDefaultHandler,                      // 43 RFCore Error
  IntDefaultHandler,                      // 44 IcePick
  IntDefaultHandler,                      // 45 FLASH Control
  IntDefaultHandler,                      // 46 AES
  IntDefaultHandler,                      // 47 PKA
  IntDefaultHandler,                      // 48 Sleep Timer
  IntDefaultHandler,                      // 49 MacTimer
  IntDefaultHandler,                      // 50 SSI1 Rx and Tx
  IntDefaultHandler,                      // 51 Timer 3 subtimer A
  IntDefaultHandler,                      // 52 Timer 3 subtimer B
  0,                                      // 53 Reserved
  0,                                      // 54 Reserved
  0,                                      // 55 Reserved
  0,                                      // 56 Reserved
  0,                                      // 57 Reserved
  0,                                      // 58 Reserved
  0,                                      // 59 Reserved
  IntDefaultHandler,                      // 60 USB 2538
  0,                                      // 61 Reserved
  IntDefaultHandler,                      // 62 uDMA
  IntDefaultHandler,                      // 63 uDMA Error
#ifndef CC2538_USE_ALTERNATE_INTERRUPT_MAP
  0,                                      // 64 64-155 are not in use
  0,                                      // 65
  0,                                      // 66
  0,                                      // 67
  0,                                      // 68
  0,                                      // 69
  0,                                      // 70
  0,                                      // 71
  0,                                      // 72
  0,                                      // 73
  0,                                      // 74
  0,                                      // 75
  0,                                      // 76
  0,                                      // 77
  0,                                      // 78
  0,                                      // 79
  0,                                      // 80
  0,                                      // 81
  0,                                      // 82
  0,                                      // 83
  0,                                      // 84
  0,                                      // 85
  0,                                      // 86
  0,                                      // 87
  0,                                      // 88
  0,                                      // 89
  0,                                      // 90
  0,                                      // 91
  0,                                      // 92
  0,                                      // 93
  0,                                      // 94
  0,                                      // 95
  0,                                      // 96
  0,                                      // 97
  0,                                      // 98
  0,                                      // 99
  0,                                      // 100
  0,                                      // 101
  0,                                      // 102
  0,                                      // 103
  0,                                      // 104
  0,                                      // 105
  0,                                      // 106
  0,                                      // 107
  0,                                      // 108
  0,                                      // 109
  0,                                      // 110
  0,                                      // 111
  0,                                      // 112
  0,                                      // 113
  0,                                      // 114
  0,                                      // 115
  0,                                      // 116
  0,                                      // 117
  0,                                      // 118
  0,                                      // 119
  0,                                      // 120
  0,                                      // 121
  0,                                      // 122
  0,                                      // 123
  0,                                      // 124
  0,                                      // 125
  0,                                      // 126
  0,                                      // 127
  0,                                      // 128
  0,                                      // 129
  0,                                      // 130
  0,                                      // 131
  0,                                      // 132
  0,                                      // 133
  0,                                      // 134
  0,                                      // 135
  0,                                      // 136
  0,                                      // 137
  0,                                      // 138
  0,                                      // 139
  0,                                      // 140
  0,                                      // 141
  0,                                      // 142
  0,                                      // 143
  0,                                      // 144
  0,                                      // 145
  0,                                      // 146
  0,                                      // 147
  0,                                      // 148
  0,                                      // 149
  0,                                      // 150
  0,                                      // 151
  0,                                      // 152
  0,                                      // 153
  0,                                      // 154
  0,                                      // 155
  IntDefaultHandler,                      // 156 USB
  IntDefaultHandler,                      // 157 RFCORE RX/TX
  IntDefaultHandler,                      // 158 RFCORE Error
  IntDefaultHandler,                      // 159 AES
  IntDefaultHandler,                      // 160 PKA
  IntDefaultHandler,                      // 161 SMTimer
  IntDefaultHandler,                      // 162 MACTimer
#endif
};

//*****************************************************************************
//
// The following are constructs created by the linker, indicating where the
// the "data" and "bss" segments reside in memory.  The initializers for the
// for the "data" segment resides immediately following the "text" segment.
//
//*****************************************************************************
extern uint32_t _etext;
extern uint32_t _data;
extern uint32_t _edata;
extern uint32_t _bss;
extern uint32_t _ebss;

void
NmiSR (void)
{
    ResetISR();
    while(1)
    {
    }
}


void
FaultISR (void)
{
    while(1)
    {
    }
}


void
IntDefaultHandler (void)
{
    while(1)
    {
    }
}

extern void uart0_startup(void);

void
ResetISR(void)
{
  uint32_t *pui32Src, *pui32Dest;

  //
  // Workaround for PM debug issue
  //
  HWREG(SYS_CTRL_EMUOVR) = 0xFF;

  /* Workaround for J-Link debug issue */
  HWREG(NVIC_VTABLE) = (uint32_t) gVectors;

  //
  // Copy the data segment initializers from flash to SRAM.
  //
  pui32Src = &_etext;
  for (pui32Dest = &_data; pui32Dest < &_edata;)
  {
    *pui32Dest++ = *pui32Src++;
  }

  // Zero fill the bss segment.
  memset(&_bss,
         0,
         &_ebss - &_bss);

// register
#define DEMCR (0xE000EDFC)
#define ITM_TER (0xE0000E00)
#define ITM_TCR (0xE0000E80)
#define ITM_PORT0 (0xE0000000)
#define ITM_PORT1 (0xE0000004)
#define ITM_LOCK_ACCESS (0xE0000FB0)

#define TPIU_ACPR (0xE0040010)
#define TPIU_SPPR (0xE00400F0)
#define TPIU_FFCR (0xE0040304)
#define TPIU_FFCR_FOnMan (1 << 6) // Manual flush

// flags
#define DEMCR_TRCENA 0x01000000
#define ITM_TCR_ITMENA 0x00000001
#define ITM_UNCLOCK_KEY 0xC5ACCE55

  // use 32 MHz external osc
  SysCtrlClockSet(true,
                  false,
                  SYS_CTRL_SYSDIV_32MHZ);

  // undocumented
  HWREG(0x44010010) = 0x1;
  // PB5 OUT
  HWREG(0x400DA400) |= 0x20;

  // DEMCR
  HWREG(DEMCR) |= DEMCR_TRCENA;

  // async output prescaler - 1
  HWREG(TPIU_ACPR) = 31;

  // Unlock
  HWREG(ITM_LOCK_ACCESS) = ITM_UNCLOCK_KEY;

  // Enable ITM
  HWREG(ITM_TCR) = ITM_TCR_ITMENA;
  // stimulus port 0 and 1 enable
  HWREG(ITM_TER) = 0x3;

  // NRZ format = 2, Manchester = 1 (reset value)
  HWREG(TPIU_SPPR) = 0x00000002;

  while (0 == HWREG(ITM_PORT1))
    ;
  *(volatile uint32_t*) (ITM_PORT1) = 0xdeadc0de;

  char buff[] = "Hello, World!!!\n";

  /*
   * Each of the 32 stimulus ports has its own address.
   * A write to one of these locations causes data to be written
   *  into the FIFO if the corresponding bit in the Trace Enable
   *  Register is set.
   *  Reading from any of the stimulus ports returns the
   *  FIFO status in bit [0]:
   *  0 = full
   *  1 = not full
   */
#if 1
  {
    char *iter = buff;
    while (*iter)
    {
      while (0 == HWREG(ITM_PORT0))
        ;
      *(volatile char*) (ITM_PORT0) = *iter;
      iter++;
    };
  }
#endif

  while (0 == HWREG(ITM_PORT1))
    ;
  *(volatile uint32_t*) (ITM_PORT1) = 0xdeadbeef;

  leds_init();

  uart0_startup();

  main(0,
       NULL);

  //
  // End here if return from main()
  //
  while (1)
  {
    uint32_t cycle_burn = 1 << 18;
    while (cycle_burn--)
      ;
    leds_debug_toggle();

  }
}
