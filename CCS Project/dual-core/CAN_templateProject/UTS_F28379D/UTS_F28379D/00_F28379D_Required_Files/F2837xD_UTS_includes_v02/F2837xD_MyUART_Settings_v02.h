//#include "F28x_Project.h"
//#include "HardwareSerial.h"

void serialInit();
void scib_xmit();
void serialWrite(char * msg);
int serialAvailable();
int serialRead();
void TX_Uint16(Uint16);
void update_serial();
void RxTx_Serial_Data();


// Test 1,SCIA  DLB, 8-bit word, baud rate 0x000F, default, 1 STOP bit, no parity
void serialInit()
{

	EALLOW;
	//Configure GPIO84 as SCITXDA (Output pin)
	//Configure GPIO85 as SCIRXDA (Input pin)
	GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0; // Enable pullup on GPIO18
	GpioCtrlRegs.GPAGMUX2.bit.GPIO18 = 2;
	GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;

	//GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0; // Enable pullup on GPIO19
	//GpioCtrlRegs.GPAGMUX2.bit.GPIO19 = 2;   //2=SCIRXDB
	//GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1;
	// Configure GPIO85 (SCIRXDA) as async pin
	//GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3;

	GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0; // Enable pullup on GPIO28
	GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // asynch input
	GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 2; // GPIO28 = SCIRXDA
	GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0; // Enable pullup on GPIO29
	GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 2; // GPIO29 = SCITXDA


	EDIS;

	//-----------------------------------------------------------------------------------------------------
    //GpioCtrlRegs.GPAGMUX2.bit.GPIO18 = 0;       // 0|0=GPIO  0|1=SPICLKA      0|2=SCITXDB      0|3=CANRXA
    //GpioCtrlRegs.GPAMUX2.bit.GPIO18  = 0;       // 1|0=GPIO  1|1=EPWM10A      1|2=rsvd         1|3=SD1_D2
                                                // 2|0=GPIO  2|1=rsvd         2|2=rsvd         2|3=rsvd
                                                // 3|0=GPIO  3|1=rsvd         3|2=rsvd         3|3=UPP-D2
    //-----------------------------------------------------------------------------------------------------
    //GpioCtrlRegs.GPAGMUX2.bit.GPIO19 = 0;       // 0|0=GPIO  0|1=SPISTEAn     0|2=SCIRXDB      0|3=CANTXA
    //GpioCtrlRegs.GPAMUX2.bit.GPIO19  = 0;       // 1|0=GPIO  1|1=EPWM10B      1|2=rsvd         1|3=SD1_C2
                                                // 2|0=GPIO  2|1=rsvd         2|2=rsvd         2|3=rsvd
                                                // 3|0=GPIO  3|1=rsvd         3|2=rsvd         3|3=UPP-D1


/*
	GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0; // Enable pullup on GPIO17
	GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0; // GPIO17 = I/O
	GpioCtrlRegs.GPADIR.bit.GPIO17 = 1; // GPIO17 = output
*/

	ScibRegs.SCIFFTX.all=0xE040;
	ScibRegs.SCIFFRX.all=0x2044;
	ScibRegs.SCIFFCT.all=0x0;


	EALLOW;
	CpuSysRegs.PCLKCR7.bit.SCI_B = 1;
	ClkCfgRegs.LOSPCP.bit.LSPCLKDIV = 1;
	EDIS;
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function

 	ScibRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
                                   // No parity,8 char bits,
                                   // async mode, idle-line protocol
	ScibRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
	ScibRegs.SCICTL2.all =0x0003;
	ScibRegs.SCICTL2.bit.TXINTENA =1;
	ScibRegs.SCICTL2.bit.RXBKINTENA =1;

    //
    // SCIA at 9600 baud
    // @LSPCLK = 50 MHz (200 MHz SYSCLK) HBAUD = 0x02 and LBAUD = 0x8B.
    // @LSPCLK = 30 MHz (120 MHz SYSCLK) HBAUD = 0x01 and LBAUD = 0x86.
    //

	// Baud Rate 19200
	//ScibRegs.SCIHBAUD.all    = 0x002; // (unsigned int)((CPU_FREQ/(ClkCfgRegs.LOSPCP.bit.LSPCLKDIV * 2))/(baud*8)-1)>>8 ;
    //ScibRegs.SCILBAUD.all    = 0x8B; // (unsigned int)((CPU_FREQ/(ClkCfgRegs.LOSPCP.bit.LSPCLKDIV * 2))/(baud*8)-1)&0x00FF;

    //ScibRegs.SCIHBAUD.all    = 0x01; // (unsigned int)((CPU_FREQ/(ClkCfgRegs.LOSPCP.bit.LSPCLKDIV * 2))/(baud*8)-1)>>8 ;
    //ScibRegs.SCILBAUD.all    = 0x86; // (unsigned int)((CPU_FREQ/(ClkCfgRegs.LOSPCP.bit.LSPCLKDIV * 2))/(baud*8)-1)&0x00FF;
    ScibRegs.SCILBAUD.all    = 53 ;


    // Baud Rate 230400
    ScibRegs.SCIHBAUD.all    = 0x00;
    ScibRegs.SCILBAUD.all    = 53 ;

	ScibRegs.SCICTL1.all =0x0023;  // Relinquish SCI from Reset


	// scib_fifo_init - Initialize the SCI FIFO
	ScibRegs.SCIFFTX.all = 0xE040;
	ScibRegs.SCIFFRX.all = 0x2044;
	ScibRegs.SCIFFCT.all = 0x0;

}

// Transmit a character from the SCI
void scib_xmit(int a)
{
    while (ScibRegs.SCIFFTX.bit.TXFFST != 0) {}
    ScibRegs.SCITXBUF.all =a;
}

void serialWrite(char * msg)
{
    int i;
    i = 0;
    while(msg[i] != '\0')
    {
        scib_xmit(msg[i]);
        i++;
    }
}

int serialAvailable()
{
	return ScibRegs.SCIFFRX.bit.RXFFST;
}

int serialRead()
{
	return ScibRegs.SCIRXBUF.all;
}

void TX_Uint16(Uint16 data16){
    Uint16 LSB;
    Uint16 MSB;

    LSB=data16;
    MSB=(data16>>8);

    scib_xmit(LSB);
    scib_xmit(MSB);



}

void update_serial(){
    if (update_uart_speed==1){
        ScibRegs.SCILBAUD.all    = baut_int ;
        ScibRegs.SCICTL1.all =0x0023;  // Relinquish SCI from Reset
    }

}

void RxTx_Serial_Data(){
    //serialWrite("100 \r\n\0");
        //data_in=0;
    Uint16 j=0;
    Uint16 data_in_length;
    Uint16 data_in;
    Uint16 data_in_array[10];
    Uint16 data_out_array[10];
    Uint16 cont_in;
    Uint16 data_out = 250;



        if(serialAvailable()){

            data_in_length=0;
            data_in= serialRead();
            data_in_array[0]= data_in;
            if (data_in== 255){
                while(data_in_length==0){
                    if(serialAvailable()){
                        data_in_length = serialRead();
                        if (data_in_length>10)
                            data_in_length=10;
                        data_in_array[1]= data_in_length;
                    }
                }
                cont_in=2;
                while(cont_in<data_in_length ){
                    if(serialAvailable()){
                        data_in_array[cont_in]=serialRead();
                        cont_in++;
                }

                }
                External_instruction=data_in_array[2];


                // 1: Rx integer
                if (External_instruction==1){
                    //form integer
                    Uint16 LSB;
                    Uint16 MSB;

                    LSB=data_in_array[4];
                    MSB=data_in_array[5];
                    External_int[data_in_array[3]]=(MSB << 8) | LSB;
                }


                // 2: Rx float
                if (External_instruction==2){
                    //Uint16 byte_in[4];
    /*
                    for(j=0; j<4; j++){
                        byte_in[j]=data_in_array[j+4];
                        External_int[j]=byte_in[j];
                    }
                    //test_IN1=byte_in[0] | (byte_in[1] << 8);
                    //test_IN2=byte_in[2] | (byte_in[3] << 8);
                     * */

                    myfloat.uint16[0]=data_in_array[4] | (data_in_array[5] << 8);
                    myfloat.uint16[1]=data_in_array[6] | (data_in_array[7] << 8);

                    External_float[data_in_array[3]]=myfloat.number;
                }

                // 11: Tx integer
                if (External_instruction==11){
                    //send integer
                    Uint16 LSB;
                    Uint16 MSB;
                    //data_out =abs(External_int[data_in_array[3]]);
                    data_out =External_int[data_in_array[3]];
                    LSB = data_out;
                    MSB = data_out>>8;
                    data_out_array[0]=100;
                    data_out_array[1]=5;    //length
                    data_out_array[2]=1;    //1:integer
                    data_out_array[3]=LSB;
                    data_out_array[4]=MSB;
                    for(j=0; j<data_out_array[1]; j++){
                        scib_xmit(data_out_array[j]);
                        //DelayUs(1);
                    }
                }

                // 12: Tx float
                if (External_instruction==12){
                    //send integer
                    //Uint16 LSB;
                    //Uint16 MSB;
                    //data_out =abs(External_int[data_in_array[3]]);
                    myfloat.number = External_float[data_in_array[3]];
                    //LSB = data_out;
                    //MSB = data_out>>8;
                    data_out_array[0]=100;
                    data_out_array[1]=7;    //length
                    data_out_array[2]=2;    //2:floating
                    data_out_array[3]=myfloat.uint16[0];
                    data_out_array[4]=myfloat.uint16[0]>>8;
                    data_out_array[5]=myfloat.uint16[1];
                    data_out_array[6]=myfloat.uint16[1]>>8;
                    for(j=0; j<data_out_array[1]; j++){
                        scib_xmit(data_out_array[j]);
                        //DelayUs(1);
                    }
                }




            }
        }
}

