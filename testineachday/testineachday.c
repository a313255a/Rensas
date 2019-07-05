#include "iodefine.h"

void inittimer(void);
void system_clk(void);
void mpc_init(void);
void s12ad_init(void);
void port_init(void);
void sci1_init(void);

#define Num_of_Results         (133)
static unsigned short results[Num_of_Results]; 
unsigned int tx_index,Red=1,starttx=0;
int ad_index2=0;
int temp1,temp;
int ad_index = 0;
int x=1,cnt=1;
int count=0;
void main(void)
{	
	system_clk();
	inittimer();
	s12ad_init();
	mpc_init();
	port_init();
	sci1_init();
		while(1)
		{
			if (ad_index == 132)
			{
				ad_index2 = ad_index;
				ad_index = 0;
 				tx_index = 0;
				starttx=0;
				
				while (tx_index < Num_of_Results)
				{
					while (!SCI1.SSR.BIT.TEND);
			
					SCI1.TDR = results[tx_index];
					tx_index++;
				}
				
				S12AD.ADCSR.BIT.ADIE = 1;
			}
		}
}

#pragma interrupt (Excep_TMR0_CMIA0(vect=174))
void Excep_TMR0_CMIA0(void);
void Excep_TMR0_CMIA0(void)
{
    
	   S12AD.ADCSR.BIT.ADST = 1;           /* start A/D conversion */
	
}

#pragma interrupt (Excep_S12AD0_S12ADI0(vect=102))
void Excep_S12AD0_S12ADI0(void);
void Excep_S12AD0_S12ADI0(void)
{
	  switch(cnt)
  {
  case 1:
    if (Red == 1)
    {
      	results[0] = 0xFF;         // Red -> 0xFF = 255
    }
    else
    {
      	results[0] = 0xEF;         // IR  -> 0xEF = 239
    }                                   
    								//1
		results[1] = 0xAB;           // Sample Rate: 2^10 = 1024 hz, NumofLED: 2 , NumofRound: 2^3 = 8 Lack of space
		
		results[2] = 0x16;           //Ch2, Ch3, Ch5 ON
		
    	results[3] = 0x040 | ((S12AD.ADDR2)>>6); 
		                         //2
		results[4] = 0x080 | (0x03F & (S12AD.ADDR2));
		                       	//4 
		results[5] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[6] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[7] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[8] = 0x080 | (0x03F & S12AD.ADDR8);
		
		//ad_index=8;                         //8
    
    break;
    
  case 2:
    if (Red == 1)
    {
			Red=0;                          // Turn NIR
			PORTB.PODR.BIT.B6 = 1;		    //PB6output high led4 910nm on		
		    PORTB.PODR.BIT.B7 = 0; 			//PB7output high led2 640nm off                     // Turn IR
    }
    else
    {
  			Red=1;                          // Turn NIR
			PORTB.PODR.BIT.B6 = 0;		    //PB6output high led4 910nm off	
		    PORTB.PODR.BIT.B7 = 1;			//PB7output high led2 640nm on
    }
		results[9] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[10] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[11] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[12] = 0x080 | (0x03F & S12AD.ADDR8);
		
		//ad_index=12;
		                         //3    
    break;
    
  case 3:
		results[13] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[14] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[15] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[16] = 0x080 | (0x03F & S12AD.ADDR8);
		
		//ad_index=16;                         //3    
    
    break;

  case 4:
		results[17] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[18] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[19] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[20] = 0x080 | (0x03F & S12AD.ADDR8);
		
		//ad_index=20;                         //3    
    
    break;     
 
  case 5:
		results[21] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[20] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[23] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[24] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=24;                         //3    
    
    break; 

  case 6:
		results[25] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[26] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[27] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[28] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=28;                         //3    
    
    break; 

  case 7:
		results[29] = 0x040 | S12AD.ADDR10>>6; 
		                         //5
		results[30] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[31] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[32] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=32;                         //3    
    break; 

  case 8:
		results[33] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[34] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[35] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[36] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=36;                         //3    
    
    break; 

  case 9:
		results[37] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[38] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[39] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[40] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=40;                         //3    
    
    break; 

  case 10:
		results[41] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[42] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[43] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[44] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=44;                         //3    
    
    break; 

  case 11:
		results[45] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[46] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[47] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[48] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=48;                         //3    
    break; 

  case 12:
		results[49] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[50] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[51] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[52] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=52;                         //3    
    
    break; 

  case 13:
		results[53] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[54] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[55] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[56] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=56;                         //3    
    
    break; 

  case 14:
		results[57] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[58] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[59] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[60] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=60;                         //3    
    
    break; 
  
  case 15:
		results[61] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[62] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[63] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[64] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=64;                         //3    
    
    break; 

  case 16:
		results[65] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[66] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[67] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[68] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=68;                         //3    
    
    break; 

  case 17:
		results[69] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[70] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[71] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[72] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=72;                         //3    
    
    break; 

  case 18:
		results[73] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[74] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[75] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[76] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=76;                         //3    
    break; 
  
  case 19:
		results[77] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[78] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[79] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[80] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=80;                         //3    
    break; 

  case 20:
		results[81] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[82] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[83] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[84] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=84;                         //3    
		
    break;

  case 21:
		results[85] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[86] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[87] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[88] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=88;                         //3    
    
    break; 

  case 22:
		results[89] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[90] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[91] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[92] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=92;                         //3    
    
    break; 
  
  case 23:
		results[93] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[94] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[95] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[96] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=96;                         //3    
    
    break; 

  case 24:
		results[97] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[98] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[99] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[100] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=100;                         //3    
    
    break;

  case 25:
		results[101] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[102] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[103] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[104] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=104;                         //3    
    
    break; 

  case 26:
		results[105] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[106] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[107] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[108] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=108;                         //3    
    
    break; 
  
  case 27:
		results[109] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[110] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[111] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[112] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=112;                         //3    
    break; 

  case 28:
		results[113] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[114] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[115] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[116] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=116;                         //3    
    
    break;

  case 29:
		results[117] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[118] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[119] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[120] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=120;                         //3    
    
    break; 

  case 30:
		results[121] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[122] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[123] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[124] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=124;                         //3    
    
    break;

  case 31:
		results[125] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[126] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[127] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[128] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=128;                         //3    
    
    break;

  case 32:    
		results[129] = 0x040 | S12AD.ADDR10>>6; 
		                        //5
		results[130] = 0x080 | (0x03F & S12AD.ADDR10);
		
		results[131] = 0x040 | S12AD.ADDR8>>6; 
		                         //7			
		results[132] = 0x080 | (0x03F & S12AD.ADDR8);
		
		ad_index=132;                         //3                            		
			cnt=0;
			x=0;                         		
    break;
    
  }
 		cnt++;
		x++;
		//S12AD.ADCSR.BIT.ADIE = 0;		
        //starttx=2;
		count++;
		IR(SCI1,TXI1) = 0;
		IR(SCI1,RXI1) = 0;
	  //IEN(SCI1,RXI1)= 0;
	
	

	
	

}

#pragma interrupt (Excep_SCI1_TXI1(vect=220))
void Excep_SCI1_TXI1(void);
void Excep_SCI1_TXI1(void)
{ 

}

#pragma interrupt (Excep_SCI1_RXI1(vect=219))
void Excep_SCI1_RXI1(void);
void Excep_SCI1_RXI1(void)
{ 

}

/*******************************************************************************
* Outline      : initial TMR setting
* Header       : none
* Function Name: inittimer
* Description  : initial TMR setting.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void inittimer(void)
{
	MSTP(TMR0) = 0;
	MSTP(TMR1) = 0;
	
	TMR1.TCCR.BIT.CSS = 1;//CSS CKSp852
	

	TMR1.TCCR.BIT.CKS = 1;	//0=PLCK; 1=PCLK/2; 2=PCLK/8;  4=PCLK/64; 5=PCLK/1024; 6=PCLK/8192;
	
	TMR0.TCCR.BIT.CSS = 3;
	TMR0.TCR.BIT.CCLR = 1;
	
	//deciding frequency ®˙ºÀ¿W≤v
	//TMR0.TCORA = 0x19;
	//TMR1.TCORA = 0x0a;
    TMR0.TCORA = 0x17;
	TMR1.TCORA = 0xd7;
    //25MHz/1024/(0018)Hex = 1017Hz <<< interrupt frequency
	//40 Hz = 25M/1024/610(0262)
	//300Hz = 25M/1024/81(0051)			
	
	TMR0.TCR.BIT.CMIEA = 1;
	
	IEN(TMR0,CMIA0) = 1;//enable compare match interrupt
	IPR(TMR0,CMIA0) = 3;//priority level of interrupt
}

/*******************************************************************************
* Outline      : Ports initial setting
* Header       : none
* Function Name: port_init
* Description  : Configure ports initial setting.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void port_init(void)
{
	PORT1.PODR.BIT.B6 = 1;              /* P16/TXD1: High */
    PORT1.PODR.BIT.B5 = 1;              /* P15/RXD1: High */
	//PORT1.PODR.BYTE = 011000;
	
    PORT1.PDR.BIT.B5 = 0;               /* P15/RXD1: input */
    PORT1.PDR.BIT.B6 = 1;               /* P16/TXD1: output */
	//PORT1.PDR.BYTE = 011000;

    PORT1.PMR.BIT.B5 = 0;               /* P15/RXD1: general I/O pin */
    PORT1.PMR.BIT.B6 = 0;               /* P16/TXD1: general I/O pin */
	//PORT1.PMR.BYTE = 011000;
	
	
    PORTB.PDR.BIT.B5 = 1; 				//PB5:output
	PORTB.PDR.BIT.B6 = 1; 				//PB6:output
	PORTB.PDR.BIT.B7 = 1;				//PB7:output
	
	PORTB.PODR.BIT.B5 = 1;				//PB5output high led1 off
	PORTB.PODR.BIT.B6 = 1; 				//PB6output high led3 off
	PORTB.PODR.BIT.B7 = 1; 				//PB7output high led5 off
	
	

	//PORTB.PDR.BYTE = 111000;
	

	

 

}

/*******************************************************************************
* Outline      : SCI1 initial setting
* Header       : none
* Function Name: sci1_init
* Description  : Configure SCI1 initial setting.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void sci1_init(void)
{
    SYSTEM.PRCR.WORD = 0xA502;          /* Enables writing to the registers */
    MSTP(SCI1) = 0;                     /* SCI1 module stop state is canceled */
    SYSTEM.PRCR.WORD = 0xA500;          /* Disables writing to the registers */
	
    /* ---- SCI interrupt request is disabled ---- */
    IEN(SCI1,ERI1) = 0;                 /* SCI1.ERI1 interrupt request is disabled */
    IEN(SCI1,RXI1) = 0;                 /* SCI1.RXI1 interrupt request is disabled */
    IEN(SCI1,TXI1) = 0;                 /* SCI1.TXI1 interrupt request is disabled */
    IEN(SCI1,TEI1) = 0;                 /* SCI1.TEI1 interrupt request is disabled */

    /* ---- Initialization of SCI ---- */
    SCI1.SCR.BYTE = 0x00;               /* Disable transmission and reception */
    while (0x00 != (SCI1.SCR.BYTE & 0xF0))
    {
        /* Confirm that bit is actually 0 */
    }

    MPC.PWPR.BIT.B0WI   = 0;            /* Writing to the PFSWE bit is enabled */
    MPC.PWPR.BIT.PFSWE  = 1;            /* Writing to the PFS register is enabled */
    MPC.P15PFS.BIT.PSEL = 0x0A;         /* RXD1 */
    MPC.P16PFS.BIT.PSEL = 0x0A;         /* TXD1 */
    MPC.PWPR.BIT.PFSWE  = 0;            /* Writing to the PFS register is disabled */
    MPC.PWPR.BIT.B0WI   = 1;            /* Writing to the PFSWE bit is disabled */
    PORT1.PMR.BIT.B5    = 1;            /* P15/RXD1: Use pin as I/O port for peripheral function */

    SCI1.SCR.BIT.CKE = 0;               /* Select an On-chip baud rate generator to the clock source */
    SCI1.SMR.BYTE    = 0x00;            /* Clock source: PCLKB */
                                        /* Communications mode: Asynchronous mode */
    SCI1.SCMR.BYTE   = 0xF2;            /* Smart card interface mode: serial communications interface mode */
                                        /* Data invert: Not inverted */
                                        /* Data transfer direction: LSB-first */
    SCI1.SEMR.BYTE = 0x00;              /* Base Clock Select: Selects 16 base clock cycles for 1-bit period */
                                        /* Noise cancellation function for the RXDn input signal: Disabled */
    SCI1.BRR         = 6;              /* 19.34 = (25MHz/(64*2^(-1)*38400bps))-1 */

    /* ---- Initialization of SCI interrupt ---- */
    IPR(SCI1,    ) = 1;                 /* SCI interrupt priority level is 1 */
    IR(SCI1,RXI1)  = 0;                 /* SCI1.RXI1 interrupt request is cleared (Edge interrupt) */
    IR(SCI1,TXI1)  = 0;                 /* SCI1.TXI1 interrupt request is cleared (Edge interrupt) */

	/* ==== Start to transmit and receive ==== */
	SCI1.SCR.BYTE |= 0xF4;              /* Enable TE, TIE, TEIE, RE, RIE */
    PORT1.PMR.BIT.B6 = 1;               /* P16/TXD1: Use pin as I/O port for peripheral function */
	PORT1.PMR.BIT.B5 = 1;               /* P15/RXD1: Use pin as I/O port for peripheral function */
    IEN(SCI1,ERI1) = 1;                 /* Enable ERI interrupt request */
    IEN(SCI1,RXI1) = 1;                 /* Enable RXI interrupt request */
    IEN(SCI1,TXI1) = 1;                 /* Enable TXI interrupt request */
}

/*******************************************************************************
* Outline      : Multi-function Pin Controller initial setting
* Header       : none
* Function Name: mpc_init
* Description  : Configure the assignment of the input pins of the peripheral function to use.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void mpc_init(void)
{
    /* ==== P40/AN000 setting ==== */
	PORT4.PDR.BIT.B2 = 1;
	PORT4.PMR.BIT.B2 = 1;              /* P42: input */              /* P42: general I/O port */
    PORT4.PDR.BIT.B0 = 0;               /* P40: input */
    PORT4.PMR.BIT.B0 = 0;               /* P40: general I/O port */
	PORT4.PDR.BIT.B6 = 0;               /* P46: input */
    PORT4.PMR.BIT.B6 = 0;               /* P46: general I/O port */
	PORTE.PDR.BIT.B2 = 0;               /* PE2: input */
    PORTE.PMR.BIT.B2 = 0;               /* PE2: general I/O port */


    MPC.PWPR.BIT.B0WI   = 0;            /* Writing to the PFSWE bit is enabled */
    MPC.PWPR.BIT.PFSWE  = 1;            /* Writing to the PFS register is enabled */
    MPC.P40PFS.BIT.ASEL = 1;            /* P40: Used as an analog pin (AN000) */
	MPC.P42PFS.BIT.ASEL = 1;            /* P42: Used as an analog pin (AN002) */
	MPC.P46PFS.BIT.ASEL = 1;            /* P46: Used as an analog pin (AN006) */
	MPC.PE2PFS.BIT.ASEL = 1;			/* PE2: Used as an analog pin (AN010) */
    MPC.PWPR.BIT.PFSWE  = 0;            /* Writing to the PFS register is disabled */
    MPC.PWPR.BIT.B0WI   = 1;            /* Writing to the PFSWE bit is disabled */
}

/*******************************************************************************
* Outline      : 12-Bit A/D Converter initial setting
* Header       : none
* Function Name: s12ad_init
* Description  : Configure S12AD initial setting.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void s12ad_init(void)
{
	SYSTEM.PRCR.WORD = 0xA502;			/* protect off */
	MSTP(S12AD) = 0;
	SYSTEM.PRCR.WORD = 0xA500;			/* protect on */
	
    S12AD.ADCSR.WORD     = 0x0000;      /* Single scan mode */
    S12AD.ADANSA.WORD    = 0x0544;      /* AN000 is subjected to scan conversion */  //ADC¬‡¥´¨∞AN002
    S12AD.ADADS.WORD     = 0x0000;      /* A/D-converted value addition mode is not selected */
    S12AD.ADCER.WORD     = 0x0000;      /* Right-alignment, Disables self-diagnosis and automatic clearing */
    //S12AD.ADSTRGR.WORD   = 0x0100;      /* Trigger to start A/D: TRG0AN (TRGA compare match from MTU0) */
    S12AD.ADEXICR.WORD   = 0x0000;      /* A/D conversion of temperature sensor output is not performed */
                                        /* A/D conversion of internal reference voltage is not performed */
    S12AD.ADSSTR0        = 20;          /* Sampling Time: 20us = 20 * 1us (ADCLK=1MHz) */
    S12AD.ADSHCR.WORD    = 0x0114;      /* Use the AN000 channel-dedicated sample-and-hold circuits */
    S12AD.ADDISCR.BYTE   = 0x00;        /* Disconnection detection assist function is disabled */

    /* ==== Disable Interrupt ==== */
    //IEN(S12AD,S12ADI0)   = 0;           /* Disable S12AD.S12ADI0 interrupt */
    //S12AD.ADCSR.BIT.ADIE = 0;           /* Disable S12ADI0 interrupt generation upon scan completion */
    IEN(S12AD,S12ADI0)   = 1;           /* Enable S12AD.S12ADI0 interrupt */
	IPR(S12AD,S12ADI0)   = 1;
	S12AD.ADCSR.BIT.ADIE = 1;           /* Enable S12ADI0 interrupt generation upon scan completion */
	//while (0 != S12AD.ADCSR.BIT.ADIE)
    //{
    //    /* Confirm that the written value can be read correctly. */
    //}
    IR(S12AD,S12ADI0)    = 0;           /* Clear S12AD interrupt request */
	
    /* ==== Stop A/D conversion ==== */
    //S12AD.ADCSR.BIT.TRGE = 0;           /* Disable A/D conversion to be started by the synchronous trigger */
    //S12AD.ADCSR.BIT.ADST = 0;           /* Stop A/D conversion */

    /* ==== Enables trigger to start A/D conversion ==== */
    S12AD.ADCSR.BIT.TRGE = 1;           /* Enable A/D conversion to be started by the synchronous trigger */
}

/******************************************************************************
* Function Name: system_clk
* Description  : clock initialization
* Arguments    : none
* Return Value : none
******************************************************************************/
void system_clk(void)
{
	unsigned int i;
	
	SYSTEM.PRCR.WORD = 0x0A503;			/* Protect Register Off */
	SYSTEM.SYSCR0.WORD=0x5A01;			/* External BUS disabled */
  	MPC.PWPR.BYTE = 0x00; MPC.PWPR.BYTE = 0x40;  /* allow writing to MPC PFS */
 	RTC.RCR3.BYTE = 0x0C;               /* sub clock oscillator drive ability => standard */
	
  { /* PLL @50Mhz from 20Mhz xtal */
  
    SYSTEM.OPCCR.BIT.OPCM = 0x0; /* high speed mode */
	
    while(SYSTEM.OPCCR.BIT.OPCMTSF == 1)
      ;
      
  	SYSTEM.MOSCCR.BYTE = 0x00;			/* EXTAL ON :(Bit0=0ÅF)main clock oscillates */
  	
	for(i = 0;i< 1250;i++)
      ;				/* Wait 10mS */
      
  	SYSTEM.PLLCR.WORD=0x0901;			/* PLL circuit (x10/2)=>20.0MHzx10/2=100Mhz */
  	SYSTEM.PLLWTCR.BYTE	=0x08;			/* Set waiting time (0x08:32768cycle) */
  	SYSTEM.PLLCR2.BIT.PLLEN=0;			/* turn on PLL */
    
  	for(i = 0;i< 1250;i++)
	;				/* Wait 10mS */
   
  	SYSTEM.SCKCR.LONG = 0x21821211;
	/*                    || | | |    °ıPLL  °ıdivision ratio */
	/*                 FCLK| | | |    100Mhz/ 4 = 25Mhz */
	/*                  ICLK | | |    100Mhz/ 2 = 50Mhz */
	/*                    BCLK | |    100Mhz/ 4 = 25Mhz */
	/*                     PCLKB |    100Mhz/ 4 = 25Mhz */
	/*                       PCLKD    100Mhz/ 2 = 50Mhz */

  	SYSTEM.SCKCR3.WORD = 0x0400;		/* Select PLL circuit */
	SYSTEM.SYSCR0.WORD=0x5A03;			/*enable external bus to view BCLK Output on BCLK Pin P53*/
  }
}
/* End of Program */