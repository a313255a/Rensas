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
* File Name    : clock_init.h
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
Typedef definitions
******************************************************************************/
#define FOR_CMT0_TIME     223 /*  1 count time for LOCO is about 223us (143.75kHz@LOCO max.) */

/******************************************************************************
Private global variables and functions
******************************************************************************/

void clock_init(void);
void cmt0_wait(unsigned short );

/* End of File */
