// Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
// SPDX-FileCopyrightText: 2012 Texas Instruments Incorporated
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef __I2C_H__
#define __I2C_H__

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
// Defines for the API.
//
//*****************************************************************************

//*****************************************************************************
//
// Interrupt defines.
//
//*****************************************************************************
#define I2C_INT_MASTER          0x00000001
#define I2C_INT_SLAVE           0x00000002

//*****************************************************************************
//
// I2C Master commands.
//
//*****************************************************************************
#define I2C_MASTER_CMD_SINGLE_SEND                                            \
                                0x00000007
#define I2C_MASTER_CMD_SINGLE_RECEIVE                                         \
                                0x00000007
#define I2C_MASTER_CMD_BURST_SEND_START                                       \
                                0x00000003
#define I2C_MASTER_CMD_BURST_SEND_CONT                                        \
                                0x00000001
#define I2C_MASTER_CMD_BURST_SEND_FINISH                                      \
                                0x00000005
#define I2C_MASTER_CMD_BURST_SEND_ERROR_STOP                                  \
                                0x00000004
#define I2C_MASTER_CMD_BURST_RECEIVE_START                                    \
                                0x0000000b
#define I2C_MASTER_CMD_BURST_RECEIVE_CONT                                     \
                                0x00000009
#define I2C_MASTER_CMD_BURST_RECEIVE_FINISH                                   \
                                0x00000005
#define I2C_MASTER_CMD_BURST_RECEIVE_ERROR_STOP                               \
                                0x00000004

//*****************************************************************************
//
// I2C Master error status.
//
//*****************************************************************************
#define I2C_MASTER_ERR_NONE     0
#define I2C_MASTER_ERR_ADDR_ACK 0x00000004
#define I2C_MASTER_ERR_DATA_ACK 0x00000008
#define I2C_MASTER_ERR_ARB_LOST 0x00000010

//*****************************************************************************
//
// I2C Slave action requests
//
//*****************************************************************************
#define I2C_SLAVE_ACT_NONE      0
#define I2C_SLAVE_ACT_RREQ      0x00000001  // Master has sent data
#define I2C_SLAVE_ACT_TREQ      0x00000002  // Master has requested data
#define I2C_SLAVE_ACT_RREQ_FBR  0x00000005  // Master has sent first byte

//*****************************************************************************
//
// Miscellaneous I2C driver definitions.
//
//*****************************************************************************
#define I2C_MASTER_MAX_RETRIES  1000        // Number of retries


//*****************************************************************************
//
// I2C Slave interrupts.
//
//*****************************************************************************
#define I2C_SLAVE_INT_STOP      0x00000004  // Stop Condition Interrupt.
#define I2C_SLAVE_INT_START     0x00000002  // Start Condition Interrupt.
#define I2C_SLAVE_INT_DATA      0x00000001  // Data Interrupt.


//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
extern void I2CIntRegister(void (*pfnHandler)(void));
extern void I2CIntUnregister(void);
extern bool I2CMasterBusBusy(void);
extern bool I2CMasterBusy(void);
extern void I2CMasterControl(uint32_t ui32Cmd);
extern uint32_t I2CMasterDataGet(void);
extern void I2CMasterDataPut(uint8_t ui8Data);
extern void I2CMasterDisable(void);
extern void I2CMasterEnable(void);
extern uint32_t I2CMasterErr(void);
extern void I2CMasterInitExpClk(uint32_t ui32I2CClk, bool bFast);
extern void I2CMasterIntClear(void);
extern void I2CMasterIntDisable(void);
extern void I2CMasterIntEnable(void);
extern bool I2CMasterIntStatus(bool bMasked);
extern void I2CMasterSlaveAddrSet(uint8_t ui8SlaveAddr,
                                  bool bReceive);
extern uint32_t I2CSlaveDataGet(void);
extern void I2CSlaveDataPut(uint8_t ui8Data);
extern void I2CSlaveDisable(void);
extern void I2CSlaveEnable(void);
extern void I2CSlaveInit(uint8_t ui8SlaveAddr);
extern void I2CSlaveIntClear(void);
extern void I2CSlaveIntDisable(void);
extern void I2CSlaveIntEnable(void);
extern void I2CSlaveIntClearEx(uint32_t ui32IntFlags);
extern void I2CSlaveIntDisableEx(uint32_t ui32IntFlags);
extern void I2CSlaveIntEnableEx(uint32_t ui32IntFlags);
extern bool I2CSlaveIntStatus(bool bMasked);
extern uint32_t I2CSlaveIntStatusEx(bool bMasked);
extern uint32_t I2CSlaveStatus(void);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __I2C_H__
