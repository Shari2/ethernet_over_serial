// Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
// SPDX-FileCopyrightText: 2012 Texas Instruments Incorporated
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef __SHA256_H__
#define __SHA256_H__

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

//*****************************************************************************
//
//  General constants
//
//*****************************************************************************
#define SHA256_BLOCK_SIZE         64
#define SHA256_OUTPUT_LEN         32
#define HASH_SHA256_MAX_BLOCK_LEN 64

// SHA256 structures
typedef struct {
    uint64_t length;   
    uint32_t  state[8]; 
    uint32_t  curlen;    
    uint8_t  buf[64];  
    uint8_t  new_digest;
    uint8_t  final_digest;
} tSHA256State;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
// SHA256 functions
extern uint8_t SHA256Init(tSHA256State *psMd);
extern uint8_t SHA256Process(tSHA256State *psMd,
                             uint8_t *ui8In,
                             uint32_t ui32InLen);
extern uint8_t SHA256Done(tSHA256State *psMd, uint8_t *ui8Out);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // __SHA256_H__
