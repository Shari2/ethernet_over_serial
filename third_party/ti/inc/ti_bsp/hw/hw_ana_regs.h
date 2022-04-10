// Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
// SPDX-FileCopyrightText: 2013 Texas Instruments Incorporated
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef __HW_ANA_REGS_H__
#define __HW_ANA_REGS_H__

//*****************************************************************************
//
// The following are defines for the ANA_REGS register offsets.
//
//*****************************************************************************
#define ANA_REGS_O_IVCTRL       0x00000004  // Analog control register 


//*****************************************************************************
//
// The following are defines for the bit fields in the 
// ANA_REGS_O_IVCTRL register.
//
//*****************************************************************************
#define ANA_REGS_IVCTRL_DAC_CURR_CTRL_M \
                                0x00000030  // Controls bias current to DAC 
                                            // 00: 100% IVREF, 0% IREF bias 01: 
                                            // 60% IVREF, 40% IREF bias 10: 40% 
                                            // IVREF, 60% IREF bias 11: 0% 
                                            // IVREF, 100% IREF bias 

#define ANA_REGS_IVCTRL_DAC_CURR_CTRL_S 4
#define ANA_REGS_IVCTRL_LODIV_BIAS_CTRL \
                                0x00000008  // Controls bias current to LODIV 
                                            // 1: PTAT bias 0: IVREF bias 

#define ANA_REGS_IVCTRL_LODIV_BIAS_CTRL_M \
                                0x00000008
#define ANA_REGS_IVCTRL_LODIV_BIAS_CTRL_S 3
#define ANA_REGS_IVCTRL_TXMIX_DC_CTRL \
                                0x00000004  // Controls DC bias in TXMIX 

#define ANA_REGS_IVCTRL_TXMIX_DC_CTRL_M \
                                0x00000004
#define ANA_REGS_IVCTRL_TXMIX_DC_CTRL_S 2
#define ANA_REGS_IVCTRL_PA_BIAS_CTRL_M \
                                0x00000003  // Controls bias current to PA 00: 
                                            // IREF bias 01: IREF and IVREF 
                                            // bias (CC2530 mode) 10: PTAT bias 
                                            // 11: Increased PTAT slope bias 

#define ANA_REGS_IVCTRL_PA_BIAS_CTRL_S 0


#endif // __HW_ANA_REGS_H__

