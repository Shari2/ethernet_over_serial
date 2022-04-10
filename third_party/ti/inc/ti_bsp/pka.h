// Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
// SPDX-FileCopyrightText: 2013 Texas Instruments Incorporated
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef __PKA_H__
#define __PKA_H__

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
#include "ecc_curveinfo.h"

//*****************************************************************************
//
// Function return values
//
//*****************************************************************************
#define PKA_STATUS_SUCCESS             0 // Success
#define PKA_STATUS_FAILURE             1 // Failure
#define PKA_STATUS_INVALID_PARAM       2 // Invalid parameter
#define PKA_STATUS_BUF_UNDERFLOW       3 // Buffer underflow
#define PKA_STATUS_RESULT_0            4 // Result is all zeros
#define PKA_STATUS_A_GR_B              5 // Big number compare return status if
                                         // the first big num is greater than
                                         // the second.
#define PKA_STATUS_A_LT_B              6 // Big number compare return status if
                                         // the first big num is less than the
                                         // second.
#define PKA_STATUS_OPERATION_INPRG     7 // PKA operation is in progress.
#define PKA_STATUS_OPERATION_NOT_INPRG 8 // No PKA operation is in progress.

//*****************************************************************************
//
// A structure containing the pointers to the values of x and y co-ordinates of
// the Elliptical Curve point.
//
//*****************************************************************************
typedef struct _ECPt
{
  //
  // Pointer to value of the x co-ordinate of the ec point.
  //
  uint32_t* pui32X;

  //
  // Pointer to value of the y co-ordinate of the ec point.
  //
  uint32_t* pui32Y;
}
tECPt;

//*****************************************************************************
//
// PKA function return type.
//
//*****************************************************************************
typedef uint8_t tPKAStatus;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
extern void PKAEnableInt(void);
extern void PKADisableInt(void);
extern void PKAClearInt(void);
extern void PKARegInt(void(*pfnHandler)(void));
extern void PKAUnRegInt(void);
extern tPKAStatus PKAGetOpsStatus(void);
extern tPKAStatus PKABigNumModStart(uint32_t* pui32BNum, uint8_t ui8BNSize,
                                    uint32_t* pui32Modulus, uint8_t ui8ModSize,
                                    uint32_t* pui32ResultVector);
extern tPKAStatus PKABigNumModGetResult(uint32_t* pui32ResultBuf,
                                        uint8_t ui8Size,
                                        uint32_t ui32ResVectorLoc);
extern tPKAStatus PKABigNumCmpStart(uint32_t* pui32BNum1, uint32_t* pui32BNum2,
                                    uint8_t ui8Size);
extern tPKAStatus PKABigNumCmpGetResult(void);
extern tPKAStatus PKABigNumInvModStart(uint32_t* pui32BNum, uint8_t ui8BNSize,
                                       uint32_t* pui32Modulus, uint8_t ui8Size,
                                       uint32_t* pui32ResultVector);
extern tPKAStatus PKABigNumInvModGetResult(uint32_t* pui32ResultBuf,
                                           uint8_t ui8Size,
                                           uint32_t ui32ResVectorLoc);
extern tPKAStatus PKABigNumMultiplyStart(uint32_t* pui32Xplicand,
                                         uint8_t ui8XplicandSize,
                                         uint32_t* pui32Xplier,
                                         uint8_t ui8XplierSize,
                                         uint32_t* pui32ResultVector);
extern tPKAStatus PKABigNumMultGetResult(uint32_t* pui32ResultBuf,
                                         uint32_t* pui32Len,
                                         uint32_t ui32ResVectorLoc);
extern tPKAStatus PKABigNumAddStart(uint32_t* pui32BN1, uint8_t ui8BN1Size,
                                    uint32_t* pui32BN2, uint8_t ui8BN2Size,
                                    uint32_t* pui32ResultVector);
extern tPKAStatus PKABigNumAddGetResult(uint32_t* pui32ResultBuf,
                                        uint32_t* pui32Len,
                                        uint32_t ui32resVectorLoc);
extern tPKAStatus PKAECCMultiplyStart(uint32_t* pui32Scalar,
                                      tECPt* ptEcPt,
                                      tECCCurveInfo* ptCurve,
                                      uint32_t* pui32ResultVector);
extern tPKAStatus PKAECCMultiplyGetResult(tECPt* ptOutEcPt,
                                          uint32_t ui32ResVectorLoc);
extern tPKAStatus PKAECCMultGenPtStart(uint32_t* pui32Scalar,
                                       tECCCurveInfo* ptCurve,
                                       uint32_t* pui32ResultVector);
extern tPKAStatus PKAECCMultGenPtGetResult(tECPt* ptOutEcPt,
                                           uint32_t pui32ResVectorLoc);
extern tPKAStatus PKAECCAddStart(tECPt* ptEcPt1, tECPt* ptEcPt2,
                                 tECCCurveInfo* ptCurve,
                                 uint32_t* pui32ResultVector);
extern tPKAStatus PKAECCAddGetResult(tECPt* ptOutEcPt, uint32_t ui32ResultLoc);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __PKA_H__
