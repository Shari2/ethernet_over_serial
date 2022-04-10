// Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
// SPDX-FileCopyrightText: 2013 Texas Instruments Incorporated
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef __ECC_CURVES_H__
#define __ECC_CURVES_H__

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
// A structure which contains the necessary elements of the
// Elliptical curve cryptography's (ECC) prime curve.
//
//*****************************************************************************
typedef struct _curveInfo
{
  //
  // Name of the curve.
  //
  char*       name;

  //
  // Size of the curve in 32-bit word.
  //
  uint8_t     ui8Size;

  //
  // The prime that defines the field of the curve.
  //
  uint32_t*   pui32Prime;

  //
  // Order of the curve.
  //
  uint32_t*   pui32N;

  //
  // Co-efficient a of the equation.
  //
  uint32_t*   pui32A;

  //
  // co-efficient b of the equation.
  //
  uint32_t*   pui32B;

  //
  // x co-ordinate value of the generator point.
  //
  uint32_t*   pui32Gx;

  //
  // y co-ordinate value of the generator point.
  //
  uint32_t*   pui32Gy;
}
tECCCurveInfo;

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __ECC_CURVES_H__
