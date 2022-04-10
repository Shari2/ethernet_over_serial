// Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
// SPDX-FileCopyrightText: 2012 Texas Instruments Incorporated
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef __CCM_H__
#define __CCM_H__

#include "ti_bsp/hw/hw_types.h"

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
    
extern uint8_t CCMAuthEncryptStart (bool bEncrypt,
                                    uint8_t ui8Mval, 
                                    uint8_t *pui8N, 
                                    uint8_t *pui8M, 
                                    uint16_t ui16LenM, 
                                    uint8_t *pui8A, 
                                    uint16_t ui16LenA, 
                                    uint8_t ui8KeyLocation, 
                                    uint8_t *pui8Cstate, 
                                    uint8_t ui8CCMLVal, 
                                    uint8_t ui8IntEnable);
extern uint8_t CCMAuthEncryptCheckResult(void);
extern uint8_t CCMAuthEncryptGetResult(uint8_t ui8Mval,  
                                       uint16_t ui16LenM, 
                                       uint8_t *pui8Cstate);
extern uint8_t CCMInvAuthDecryptStart (bool bDecrypt,
                                       uint8_t ui8Mval, 
                                       uint8_t *pui8N, 
                                       uint8_t *pui8C, 
                                       uint16_t ui16LenC, 
                                       uint8_t *pui8A, 
                                       uint16_t ui16LenA,
                                       uint8_t ui8KeyLocation, 
                                       uint8_t *pui8Cstate, 
                                       uint8_t ui8CCMLVal, 
                                       uint8_t ui8IntEnable);
extern uint8_t CCMInvAuthDecryptCheckResult(void);
extern uint8_t CCMInvAuthDecryptGetResult(uint8_t ui8Mval, 
                                          uint8_t *pui8C, 
                                          uint16_t ui16LenC, 
                                          uint8_t *pui8Cstate);
    
//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // __CCM_H__
