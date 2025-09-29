
/*
 * Reference Document
 * https://www.stcmicro.com/datasheet/STC89C51RC-en.pdf
*/

#ifndef _STC89_H_
#define _STC89_H_

#include <8051.h>

#ifdef REG8051_H
#undef REG8051_H
#endif

/*
 * Auxiliary Register
 *   Bit Mapping: - - - - - - EXTRAM ALEOFF
 *   Reset Value: 0000,0000
 */
__sfr __at (0x8E) AUXR;

/*
 * Auxiliary Register1
 *   Bit Mapping: - - - - GF2 - - DPS
 *   Reset Value: 0000,0000
 */
__sfr __at (0xA2) AUXR1;

/*
 * Slave Address
 *   Reset Value: 0000,0000
 */
__sfr __at (0xA9) SADDR;

/*
 * Interrupt Priority High
 *   Bit Mapping: PX3H PX2H PT2H PSH PT1H PX1H PT0H PX0H
 *   Reset Value: 0000,0000
 */
__sfr __at (0xB7) IPH;

/*
 * Slave Address Mask
 *   Reset Value: 0000,0000
 */
__sfr __at (0xB9) SADEN;

/*
 * Auxiliary Interrupt Control
 *   Bit Mapping: PX3 EX3 IE3 IT3 PX2 EX2 IE2 IT2
 *   Reset Value: 0000,0000
 */
__sfr __at (0xC0) XICON;

/*
 * Timer/Counter2 Control
 *   Bit Mapping: TF2 ECF2 RCLK TCLK EXEN2 TR2 CT/T2 CP/RL2
 *   Reset Value: 0000,0000
 */
__sfr __at (0xC8) T2CON;

/*
 * Timer/Counter2 Mode
 *   Bit Mapping: - - - - - - T2OE DCEN
 *   Reset Value: xxxx,xx00
 */
__sfr __at (0xC8) T2MOD;

/*
 * Timer/Counter2 Reload/Capture Low Byte
 *   Reset Value: 0000,0000
 */
__sfr __at (0xCA) RCAP2L;

/*
 * Timer/Counter2 Reload/Capture High Byte
 *   Reset Value: 0000,0000
 */
__sfr __at (0xCB) RCAP2H;

/*
 * Timer/Counter Low Byte
 *   Reset Value: 0000,0000
 */
__sfr __at (0xCC) TL2;

/*
 * Timer/Counter High Byte
 *   Reset Value: 0000,0000
 */
__sfr __at (0xCD) TH2;

/*
 * WatchDog Timer Control Register
 *   Bit Mapping: - - EN_WDT CLR_WDT IDLE_WDT PS2 PS1 PS0
 *   Reset Value: xx00,0000
 */
__sfr __at (0xE1) WDT_CONTR;

/*
 * Port 4
 *   Bit Mapping: P4.7 P4.6 P4.5 P4.4 P4.3 P4.2 P4.1 P4.0
 *   Reset Value: 1111,1111
 */
__sfr __at (0xE8) P4;

/*  BIT Register  */

/*  TCON2  */
__sbit __at (0xC8) CP_RL2 ;
__sbit __at (0xC9) C_T2   ;
__sbit __at (0xCA) TR2    ;
__sbit __at (0xCB) EXEN2  ;
__sbit __at (0xCC) TCLK   ;
__sbit __at (0xCD) RCLK   ;
__sbit __at (0xCE) EXF2   ;
__sbit __at (0xCF) TF2    ;

/* P4 */
__sbit __at (0xE8) P4_0;
__sbit __at (0xE9) P4_1;
__sbit __at (0xEA) P4_2;
__sbit __at (0xEB) P4_3;
__sbit __at (0xEC) P4_4;
__sbit __at (0xED) P4_5;
__sbit __at (0xEE) P4_6;
__sbit __at (0xEF) P4_7;

#endif