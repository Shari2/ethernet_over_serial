// Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
// SPDX-FileCopyrightText: 2012 Texas Instruments Incorporated
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef __FLASH_H__
#define __FLASH_H__

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
// Values that can be passed to FlashCacheModeSet()
// and returned by FlashCacheModeGet()
//
//*****************************************************************************
#define  FLASH_CTRL_CACHE_MODE_DISABLE          0x0
#define  FLASH_CTRL_CACHE_MODE_ENABLE           0x4
#define  FLASH_CTRL_CACHE_MODE_PREFETCH_ENABLE  0x8
#define  FLASH_CTRL_CACHE_MODE_REALTIME         0xc

//*****************************************************************************
//
// Define for the erase size of the FLASH block that is erased by an erase
// operation.
//
//****************************************************************************
#define FLASH_ERASE_SIZE  0x800

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
extern int32_t FlashMainPageErase(uint32_t ui32Address);
extern int32_t FlashUpperPageErase(void);
extern int32_t FlashMainPageProgram(uint32_t *pui32Data,
                                    uint32_t ui32Address,
                                    uint32_t ui32Count);
extern int32_t FlashUpperPageProgram(uint32_t *pui32Data,
                                     uint32_t ui32Address,
                                     uint32_t ui32Count);

extern uint32_t FlashGet(uint32_t ui32Addr);
extern uint32_t FlashCacheModeGet(void);
extern void FlashCacheModeSet(uint32_t ui32CacheMode);
extern uint32_t FlashSizeGet(void);
extern uint32_t FlashSramSizeGet(void);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __FLASH_H__
