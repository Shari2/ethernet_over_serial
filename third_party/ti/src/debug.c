// Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
// SPDX-FileCopyrightText: 2012 Texas Instruments Incorporated
//
// SPDX-License-Identifier: BSD-3-Clause

//*****************************************************************************
//
//! \addtogroup debug_api
//! @{
//
//*****************************************************************************

#include "ti_bsp/debug.h"

//*****************************************************************************
//
//!
//! Function stub for allowing compile with ENABLE_ASSERT flag asserted.
//!
//
//*****************************************************************************
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
//! Close the Doxygen group.
//! @}
//
//*****************************************************************************
