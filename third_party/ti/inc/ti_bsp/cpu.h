// Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
// SPDX-FileCopyrightText: 2012 Texas Instruments Incorporated
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef __CPU_H__
#define __CPU_H__

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
// Prototypes.
//
//*****************************************************************************
extern uint32_t CPUcpsid(void);
extern uint32_t CPUcpsie(void);
extern uint32_t CPUprimask(void);
extern void CPUwfi(void);
extern void CPUwfe(void);
extern void CPUsev(void);
extern uint32_t CPUbasepriGet(void);
extern void CPUbasepriSet(uint32_t ui32NewBasepri);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __CPU_H__
