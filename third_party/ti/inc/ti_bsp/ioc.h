// Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
// SPDX-FileCopyrightText: 2012 Texas Instruments Incorporated
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef __IOC_H__
#define __IOC_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{  
#endif

#include "ti_bsp/hw/hw_types.h"

//*****************************************************************************
//
// The following values define the bit field for the ui8Pins and ui8Pin arguments
// to all of the APIs.
//
//*****************************************************************************
#define IOC_PIN_0              0x00000001  // IO pin 0
#define IOC_PIN_1              0x00000002  // IO pin 1
#define IOC_PIN_2              0x00000004  // IO pin 2
#define IOC_PIN_3              0x00000008  // IO pin 3
#define IOC_PIN_4              0x00000010  // IO pin 4
#define IOC_PIN_5              0x00000020  // IO pin 5
#define IOC_PIN_6              0x00000040  // IO pin 6
#define IOC_PIN_7              0x00000080  // IO pin 7

//*****************************************************************************
//
// Defined values for the ui32OutputSignal parameter of the 
// IOCPinConfigPeriphOutput() function.  These are the valid values for the 
// signal select registers.
// (The registers are in the addr range: IOC_PA0 - IOC_PD7).
//
//*****************************************************************************
#define IOC_MUX_OUT_SEL_UART0_TXD       0x00000000  // iuarttxd_uart0
#define IOC_MUX_OUT_SEL_UART1_RTS       0x00000001  // iuartrts_uart1
#define IOC_MUX_OUT_SEL_UART1_TXD       0x00000002  // iuarttxd_uart1
#define IOC_MUX_OUT_SEL_SSI0_TXD        0x00000003  // issitxd_ssi0
#define IOC_MUX_OUT_SEL_SSI0_CLKOUT     0x00000004  // issiclkout_ssi0
#define IOC_MUX_OUT_SEL_SSI0_FSSOUT     0x00000005  // issifssout_ssi0
#define IOC_MUX_OUT_SEL_SSI0_STXSER_EN  0x00000006  // istxser_en_ssi0
#define IOC_MUX_OUT_SEL_SSI1_TXD        0x00000007  // issitxd_ssi1
#define IOC_MUX_OUT_SEL_SSI1_CLKOUT     0x00000008  // issiclkout_ssi1
#define IOC_MUX_OUT_SEL_SSI1_FSSOUT     0x00000009  // issifssout_ssi1
#define IOC_MUX_OUT_SEL_SSI1_STXSER_EN  0x0000000A  // istxser_en_ssi1
#define IOC_MUX_OUT_SEL_I2C_CMSSDA      0x0000000B  // ii2cmssda
#define IOC_MUX_OUT_SEL_I2C_CMSSCL      0x0000000C  // ii2cmsscl
#define IOC_MUX_OUT_SEL_GPT0_ICP1       0x0000000D  // gpt0icp1
#define IOC_MUX_OUT_SEL_GPT0_ICP2       0x0000000E  // gpt0icp2
#define IOC_MUX_OUT_SEL_GPT1_ICP1       0x0000000F  // gpt1icp1
#define IOC_MUX_OUT_SEL_GPT1_ICP2       0x00000010  // gpt1icp2
#define IOC_MUX_OUT_SEL_GPT2_ICP1       0x00000011  // gpt2icp1
#define IOC_MUX_OUT_SEL_GPT2_ICP2       0x00000012  // gpt2icp2
#define IOC_MUX_OUT_SEL_GPT3_ICP1       0x00000013  // gpt3icp1
#define IOC_MUX_OUT_SEL_GPT3_ICP2       0x00000014  // gpt3icp2

//*****************************************************************************
//
// Defined bits in the value for the pin drive type returned by the
// IOCPadConfigGet() function and used in the ui32PinDrive parameter for the
// IOCPadConfigSet() function.
//
//*****************************************************************************
#define IOC_OVERRIDE_DIS  0x00000000    // PAD Config Override Disabled
#define IOC_OVERRIDE_ANA  0x00000001    // PAD Config Override Analog Enable
#define IOC_OVERRIDE_PDE  0x00000002    // PAD Config Override Pull Down Enable
#define IOC_OVERRIDE_PUE  0x00000004    // PAD Config Override Pull Up Enable
#define IOC_OVERRIDE_OE   0x00000008    // PAD Config Override Output Enable

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
extern void IOCPinConfigPeriphOutput(uint32_t ui32Port,
                                     uint8_t ui8Pins,
                                     uint32_t ui32OutputSignal);
extern void IOCPinConfigPeriphInput(uint32_t ui32Port,
                                    uint8_t ui8Pin,
                                    uint32_t ui32PinSelectReg);
extern void IOCPadConfigSet(uint32_t ui32Port, uint8_t ui8Pins,
                            uint32_t ui32PinDrive);
extern uint32_t IOCPadConfigGet(uint32_t ui32Port,
                                     uint8_t ui8Pin);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}  
#endif

#endif // __IOC_H__
