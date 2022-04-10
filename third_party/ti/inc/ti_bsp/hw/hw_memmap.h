// Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
// SPDX-FileCopyrightText: 2013 Texas Instruments Incorporated
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef __HW_MEMMAP_H__
#define __HW_MEMMAP_H__

//*****************************************************************************
//
// The following are defines for the base address of the memories and
// peripherals on the top_s interface.
//
//*****************************************************************************
#define ROM_BASE                0x00000000  // ROM 
#define FLASH_BASE              0x00200000  // Flash 
#define SRAM_BASE               0x20000000  // SRAM 
#define SRAM_LL_BASE            0x20004000  // SRAM_LL 
#define SSI0_BASE               0x40008000  // SSI 
#define SSI1_BASE               0x40009000  // SSI 
#define UART0_BASE              0x4000C000  // UART 
#define UART1_BASE              0x4000D000  // UART 
#define I2C_M0_BASE             0x40020000  // I2CM 
#define I2C_S0_BASE             0x40020800  // I2CS 
#define GPTIMER0_BASE           0x40030000  // GPTIMER 
#define GPTIMER1_BASE           0x40031000  // GPTIMER 
#define GPTIMER2_BASE           0x40032000  // GPTIMER 
#define GPTIMER3_BASE           0x40033000  // GPTIMER 
#define RFCORE_RAM_BASE         0x40088000  // SRAM_RFCORE 
#define FRMF_SRCM_RAM_BASE      0x40088400  // SRAM_FRMF_SRCM 
#define RFCORE_FFSM_BASE        0x40088500  // RFCORE_FFSM 
#define RFCORE_XREG_BASE        0x40088600  // RFCORE_XREG 
#define RFCORE_SFR_BASE         0x40088800  // RFCORE_SFR 
#define USB_BASE                0x40089000  // USB 
#define AES_BASE                0x4008B000  // AES 
#define SYS_CTRL_BASE           0x400D2000  // SYS_CTRL 
#define FLASH_CTRL_BASE         0x400D3000  // FLASH_CTRL 
#define IOC_BASE                0x400D4000  // IOC 
#define SMWDTHROSC_BASE         0x400D5000  // SMWDTHROSC 
#define ANA_REGS_BASE           0x400D6000  // ANA_REGS 
#define SOC_ADC_BASE            0x400D7000  // SOC_ADC 
#define GPIO_A_BASE             0x400D9000  // GPIO 
#define GPIO_B_BASE             0x400DA000  // GPIO 
#define GPIO_C_BASE             0x400DB000  // GPIO 
#define GPIO_D_BASE             0x400DC000  // GPIO 
#define uDMA_BASE               0x400FF000  // UDMA 
#define ST_TESTCTRL_BASE        0x40110000  // STTEST 
#define PKA_BASE                0x44004000  // PKA 
#define PKA_RAM_BASE            0x44006000  // SRAM_PKA 
#define CC_TESTCTRL_BASE        0x44010000  // CCTEST 

#endif // __HW_MEMMAP_H__

