// Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
// SPDX-FileCopyrightText: 2012 Texas Instruments Incorporated
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

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
// The following are values that can be passed to the WatchdogEnable()
//
//*****************************************************************************
#define WATCHDOG_INTERVAL_32768 0x00000000 // Timer select: Twdt x 32768
#define WATCHDOG_INTERVAL_8192  0x00000001 // Timer select: Twdt x 8192
#define WATCHDOG_INTERVAL_512   0x00000002 // Timer select: Twdt x 512
#define WATCHDOG_INTERVAL_64    0x00000003 // Timer select: Twdt x 64

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
extern void WatchdogEnable(uint32_t ui32Interval);
extern void WatchdogClear(void);


//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __WATCHDOG_H__
