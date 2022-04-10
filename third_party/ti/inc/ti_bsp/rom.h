// Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
// SPDX-FileCopyrightText: 2012 Texas Instruments Incorporated
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef __ROM_H__
#define __ROM_H__

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

//
// Start address of the ROM hard API access table (located after the ROM FW rev field)
//
#define ROM_API_TABLE_ADDR 0x00000048

//
// ROM utility function interface types
//
typedef uint32_t       (* volatile FPTR_CRC32_T)       (uint8_t* /*pData*/, uint32_t /*byteCount*/);
typedef uint32_t       (* volatile FPTR_GETFLSIZE_T)   (void);
typedef uint32_t       (* volatile FPTR_GETCHIPID_T)   (void);
typedef int32_t        (* volatile FPTR_PAGEERASE_T)   (uint32_t /*FlashAddr*/, uint32_t /*Size*/);
typedef int32_t        (* volatile FPTR_PROGFLASH_T)   (uint32_t* /*pRamData*/, uint32_t /*FlashAdr*/, uint32_t /*ByteCount*/);
typedef void           (* volatile FPTR_RESETDEV_T)    (void);
typedef void*          (* volatile FPTR_MEMSET_T)      (void* /*s*/, int32_t /*c*/, uint32_t /*n*/);
typedef void*          (* volatile FPTR_MEMCPY_T)      (void* /*s1*/, const void* /*s2*/, uint32_t /*n*/);
typedef int32_t        (* volatile FPTR_MEMCMP_T)      (const void* /*s1*/, const void* /*s2*/, uint32_t /*n*/);
typedef void*          (* volatile FPTR_MEMMOVE_T)     (void* /*s1*/, const void* /*s2*/, uint32_t /*n*/);

//
// ROM Hard-API access table type
//
typedef struct
    {
        FPTR_CRC32_T        Crc32;
        FPTR_GETFLSIZE_T    GetFlashSize;
        FPTR_GETCHIPID_T    GetChipId;
        FPTR_PAGEERASE_T    PageErase;
        FPTR_PROGFLASH_T    ProgramFlash;
        FPTR_RESETDEV_T     ResetDevice;
        FPTR_MEMSET_T       memset;
        FPTR_MEMCPY_T       memcpy;
        FPTR_MEMCMP_T       memcmp;
        FPTR_MEMMOVE_T      memmove;
    } ROM_API_T;

//
// Pointer to the ROM API table
//
#define P_ROM_API              ((ROM_API_T*) ROM_API_TABLE_ADDR)

#define ROM_Crc32(a,b)          P_ROM_API->Crc32(a,b)
#define ROM_GetFlashSize()      P_ROM_API->GetFlashSize()
#define ROM_GetChipId()         P_ROM_API->GetChipId()
#define ROM_PageErase(a,b)      P_ROM_API->PageErase(a,b)
#define ROM_ProgramFlash(a,b,c) P_ROM_API->ProgramFlash(a,b,c)
#define ROM_ResetDevice()       P_ROM_API->ResetDevice()
#define ROM_Memset(a,b,c)       P_ROM_API->memset(a,b,c)
#define ROM_Memcpy(a,b,c)       P_ROM_API->memcpy(a,b,c)
#define ROM_Memcmp(a,b,c)       P_ROM_API->memcmp(a,b,c)
#define ROM_Memmove(a,b,c)      P_ROM_API->memmove(a,b,c)

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __ROM_H__
