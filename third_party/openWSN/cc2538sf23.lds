/*
  SPDX-FileCopyrightText: 2013 Regents of the University of California
  SPDX-License-Identifier: BSD-3-Clause
  
  Source: https://github.com/openwsn-berkeley/openwsn-fw/blob/develop/bsp/boards/openmote-cc2538/cc2538sf23.lds
*/

/**
 * Author: Xavier Vilajosana (xvilajosana@eecs.berkeley.edu)
 *         Pere Tuset (peretuset@openmote.com)
 * Date:   July 2013
 * Description: CC2538-specific linker script configuration file.
 */
 
/**
 * Indicate to the linker the entry point.
 */
ENTRY(ResetISR)

/**
 * RAM is 16 KB retention and 16 KB no retention
 * NON-RETENTION RAM starts at 0x20000000 with length 0x00004000 
 * RETENTION RAM starts at  0x20004000 with length 0x00004000
 */
MEMORY
{
    FLASH (rx)     : ORIGIN = 0x00200000, LENGTH = 0x0003FFD4
    FLASH_CCA (RX) : ORIGIN = 0x0023FFD4, LENGTH = 12
    SRAM (RWX)     : ORIGIN = 0x20004000, LENGTH = 0x00004000 
}

/* use rom functions
PROVIDE(memset = 0x00000048 + 24);
PROVIDE(memcpy = 0x00000048 + 28);
*/

SECTIONS
{
  
	/* Set stack top to end of RAM */
	__StackTop = ORIGIN(SRAM) + LENGTH(SRAM);
    .text :
    {
        _text = .;          
  		LONG(__StackTop);
        KEEP(*(.vectors))
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > FLASH=0

    .data :
    AT (ADDR (.text) + SIZEOF (.text))
    {
        _data = .;
        *(vtable)
        *(.data*)
        _edata = .;
    } > SRAM

    .ARM.exidx :
    {
        *(.ARM.exidx*)
    } > FLASH

    .bss :
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > SRAM

    .flashcca :
    {
        KEEP(*(.flashcca))
    } > FLASH_CCA
}
