/******************************************************************************
* DISCLAIMER
*
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized.
*
* This software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.
*
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES 
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, 
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY 
* DISCLAIMED.
*
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES 
* FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS 
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
*
* Renesas reserves the right, without notice, to make changes to this 
* software and to discontinue the availability of this software.  
* By using this software, you agree to the additional terms and 
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
******************************************************************************/
/* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.  */
/******************************************************************************
* System Name  : RX210 initialization example
* File Name    : clock_init.c
* Abstract     : Program example of RX210 initialization
* Version      : Ver 1.00
* Device       : R5F52108ADFP(RX210 Group)
* Tool-Chain   : High-performance Embedded Workshop (Version 4.09.00.007)
*              : C/C++ Compiler Package for RX family (V.1.02 Release 00)
* H/W Platform : Renesas Starter Kit for RX210
* Description  : Initialize the clock.
*******************************************************************************
* History      : Mar.21,2012 Ver. 1.00 First Release
******************************************************************************/

/******************************************************************************
Includes <System Includes> , "Project Includes"
******************************************************************************/
#include "iodefine.h"
#include <machine.h>
#include "clock_init.h"

/******************************************************************************
* Outline                  : Clock initialization
* Include                  : clock_init.h
* Declaration              : void clock_init(void)
* Description              : Initialize the clock.
* Argument                 : none
* Return Value             : none
******************************************************************************/
void clock_init(void)
{
    volatile unsigned char * cp = (unsigned char *)0x00080200;
    /* ---- Disable write protection ---- */
    SYSTEM.PRCR.WORD = 0xA507;              /* Enable writing to registers */
                                            /* related to the clock generation circuit. */
                                            /* Enable writing to registers */
                                            /* related to the low power consumption function. */
                                            /* Enable writing to address 0008 0200h. */
    /* ---- Write to address 0008 0200h ---- */
    *cp = 0x00;

    /* ---- Exit the module stop state ---- */
    MSTP(CMT0) = 0;                         /* CMT0 and CMT1 exit the module stop state. */
    /* ---- Stop CMT0 counting ---- */
    CMT.CMSTR0.BIT.STR0 = 0;                /* CMT0 count is stopped. */
    /* ---- Set the CMT0 count source ---- */
    CMT0.CMCR.WORD = 0x0081;                /* PCLK/32 */
    /* ---- Enable the CMT0 compare match interrupt ---- */
    CMT0.CMCR.BIT.CMIE = 1;                 /* Compare match interrupt (CMI0) is enabled. */

    /* ---- Turn off the HOCO power supply ---- */
    SYSTEM.HOCOPCR.BYTE = 0x01;             /* HOCO power supply is turned off. */

    /* ---- Stop the sub-clock ---- */
    SYSTEM.SOSCCR.BYTE = 0x01;              /* Sub-clock oscillator is stopped. */
    while(SYSTEM.SOSCCR.BYTE != 0x01){      /* Confirm that the written value can be read correctly. */
    }
    RTC.RCR3.BYTE = 0x0C;                   /* Sub-clock oscillator is stopped. */
    while(RTC.RCR3.BYTE != 0x0C){           /* Confirm that the written value can be read correctly. */
    }

    /* ---- Set the main clock oscillator drive capability ---- */
    SYSTEM.MOFCR.BYTE = 0x30;               /* 16 MHz to 20 MHz non-lead type ceramic resonator */
                                            /* 16 MHz to 20 MHz */
                                            /* Resonator */
                                            
    /* ---- Set wait time until the main clock oscillator stabilizes ---- */
    SYSTEM.MOSCWTCR.BYTE = 0x0D;            /* Wait time is 131072 cycles (approx. 6.55 ms). */
    /* ---- Operate the main clock oscillator ---- */
    SYSTEM.MOSCCR.BYTE = 0x00;              /* Main clock oscillator is operating. */
    while(SYSTEM.MOSCCR.BYTE != 0x00){      /* Confirm that the written value can be read correctly. */
    }

    /* ---- Set the PLL division ratio and multiplication factor ---- */
    SYSTEM.PLLCR.WORD = 0x0901;             /* PLL input division ratio is divide-by-2. */
                                            /* Frequency multiplication factor is multiply-by-10. */
    /* ---- Set wait time until the PLL clock oscillator stabilizes ---- */
    SYSTEM.PLLWTCR.BYTE = 0x0C;             /* Wait time is 524288 cycles (approx. 5.24 ms) */
    /* ---- Operate the PLL clock oscillator ---- */
    SYSTEM.PLLCR2.BYTE = 0x00;              /* PLL is operating. */
    /* ---- Wait processing for the clock oscillation stabilization ---- */
    cmt0_wait( 10500L/FOR_CMT0_TIME+1 );    /* Wait until the main clock and PLL clock */
                                            /* oscillation stabilize (10.5 ms). */

    /* ---- Set the operating power control mode ---- */
    SYSTEM.OPCCR.BYTE = 0x00;               /* High-speed operating mode */
    /* ---- Transition to the operation power control mode completed? ---- */
    while(SYSTEM.OPCCR.BIT.OPCMTSF == 1){
    }

    /* ---- Set the internal clock division ratio ---- */
    SYSTEM.SCKCR.LONG = 0x21821211;         /* FlashIF clock (FCLK), divide-by-4 */
                                            /* System clock (ICLK), divide-by-2 */
                                            /* BCLK pin output is disabled. (Fixed high) */
                                            /* External bus clock (BCLK), divide-by-4 */
                                            /* Peripheral module clock B (PCLKB), divide-by-4 */
                                            /* Peripheral module clock D (PCLKD), divide-by-2 */
    
    while(SYSTEM.SCKCR.LONG != 0x21821211){ /* Confirm that the written value can be read correctly. */
    }
    /* ---- Set the BCLK pin output ---- */
    SYSTEM.BCKCR.BYTE = 0x01;               /* BCLK divided by 2 */

    /* ---- Set the internal clock source ---- */
    SYSTEM.SCKCR3.WORD = 0x0400;            /* PLL circuit is selected. */
    while(SYSTEM.SCKCR3.WORD != 0x0400){    /* Confirm that the written value can be read correctly. */
    }
    
    /* ---- Initialize CMT0 ---- */
    CMT.CMSTR0.BIT.STR0 = 0;
    CMT0.CMCR.WORD = 0x0000;
    CMT0.CMCNT = 0x0000;
    CMT0.CMCOR = 0x0000;
    IR(CMT0,CMI0) = 0;
    /* ---- Enter the module stop state ---- */
    MSTP(CMT0) = 1;                         /* CMT0 and CMT1 are in the module stop state. */
    
    /* ---- Enable write protection ---- */
    SYSTEM.PRCR.WORD = 0xA500;              /* Disable writing to registers */
                                            /* related to the clock generation circuit. */
                                            /* Disable writing to registers */
                                            /* related to the low power consumption function. */
                                            /* Disable writing to address 0008 0200h. */

}
/******************************************************************************
* Outline                  : Wait processing for oscillation stabilization with CMT0
* Include                  : none
* Declaration              : void cmt0_wait(unsigned short cnt)
* Description              : Wait to stabilize the oscillation with CMT0.
* Argument                 : cnt : Wait for the time specified by an argument multiplied 
*                          :       by FOR_CMT0_TIME (us).
* Return Value             : none
******************************************************************************/
void cmt0_wait(unsigned short cnt)
{
    /* ---- Stop CMT0 counting ---- */
    CMT.CMSTR0.BIT.STR0 = 0;                /* CMT0 count is stopped. */
    /* ---- Clear the CMT0 count ---- */
    CMT0.CMCNT = 0x0000;
    /* ---- Wait time set is other than 0000h? ---- */
    if(cnt != 0x0000){
    /* ---- Decrement the wait time ---- */
        cnt = cnt - 1;
    }
    /* ---- Set the CMT0 wait time ---- */
    CMT0.CMCOR = cnt;
    /* ---- Clear the CMT0 interrupt request ---- */
    while(IR(CMT0,CMI0) == 1){
        IR(CMT0,CMI0) = 0;                  /* CMT0.CMI0 interrupt request is cleared. */
    }
    /* ---- Start CMT0 counting ---- */
    CMT.CMSTR0.BIT.STR0 = 1;                /* CMT0 count is started. */
    /* ---- CMI0 interrupt request generated? ---- */
    while(IR(CMT0,CMI0) == 0){
    }
    /* ---- Stop CMT0 counting ---- */
    CMT.CMSTR0.BIT.STR0 = 0;                /* CMT0 count is stopped. */
}

/* End of File */
