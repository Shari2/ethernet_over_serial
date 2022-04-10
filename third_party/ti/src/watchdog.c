// Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
// SPDX-FileCopyrightText: 2012 Texas Instruments Incorporated
//
// SPDX-License-Identifier: BSD-3-Clause

//*****************************************************************************
//
//! \addtogroup watchdog_api
//! @{
//
//*****************************************************************************

#include "ti_bsp/hw/hw_ints.h"
#include "ti_bsp/hw/hw_memmap.h"
#include "ti_bsp/hw/hw_smwdthrosc.h"
#include "ti_bsp/debug.h"
#include "ti_bsp/interrupt.h"
#include "ti_bsp/watchdog.h"

//*****************************************************************************
//
//! Enables the watchdog timer
//!
//! \param ui32Interval is the timer interval setting.
//!
//! This function sets the timer interval and enables the watchdog timer.
//! A timeout causes a chip reset.
//!
//! The \e ui32Interval argument must be only one of the following values:
//! \b WATCHDOG_INTERVAL_32768, \b WATCHDOG_INTERVAL_8192,
//! \b WATCHDOG_INTERVAL_512,   \b WATCHDOG_INTERVAL_64.
//!
//! \sa WatchdogDisable()
//!
//! \return None
//
//*****************************************************************************
void
WatchdogEnable(uint32_t ui32Interval)
{
    uint32_t ui32Regval;
    //
    // Check the arguments.
    //
    ASSERT(ui32Interval == WATCHDOG_INTERVAL_32768 ||
           ui32Interval == WATCHDOG_INTERVAL_8192  ||
           ui32Interval == WATCHDOG_INTERVAL_512   ||
           ui32Interval == WATCHDOG_INTERVAL_64);

    // Disable Timer to set interval
    HWREG(SMWDTHROSC_WDCTL) &= ~SMWDTHROSC_WDCTL_EN;
    ui32Regval = HWREG(SMWDTHROSC_WDCTL);
    ui32Regval &= ~SMWDTHROSC_WDCTL_INT_M;
    ui32Regval |= ui32Interval;
    HWREG(SMWDTHROSC_WDCTL) = ui32Regval;

    //
    // Enable the watchdog timer module.
    //
    ui32Regval = HWREG(SMWDTHROSC_WDCTL);
    ui32Regval &= ~0x4;
    ui32Regval |= SMWDTHROSC_WDCTL_EN;
    HWREG(SMWDTHROSC_WDCTL) = ui32Regval;
}

//*****************************************************************************
//
//! Clear watch dog timer
//!
//! This function clears the watch dog timer.
//! Timer must be enabled for the clear operation to take effect.
//!
//! \return None
//
//*****************************************************************************
void
WatchdogClear(void)
{
    uint32_t ui32Reg1;
    uint32_t ui32Reg2;

    //
    // Write 0xA followed by 0x5 to CLR field
    // (0x5 also clears in timer mode)
    //
    ui32Reg1 = HWREG(SMWDTHROSC_WDCTL);
    ui32Reg1 &= ~SMWDTHROSC_WDCTL_CLR_M;
    ui32Reg2 = ui32Reg1 | (0x5 << SMWDTHROSC_WDCTL_CLR_S);
    ui32Reg1 |= 0xa << SMWDTHROSC_WDCTL_CLR_S;

    //
    // The following two writes must happen within 0.5 cycle of WDT clock!
    // for clear to actually happen.
    // Note:  might need to "safe guard" this zone by disabling interrupts.
    //
    HWREG(SMWDTHROSC_WDCTL) = ui32Reg1;
    HWREG(SMWDTHROSC_WDCTL) = ui32Reg2;
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
