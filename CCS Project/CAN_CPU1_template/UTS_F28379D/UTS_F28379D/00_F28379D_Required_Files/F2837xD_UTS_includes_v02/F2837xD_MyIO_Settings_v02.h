

// Reserved for ePWMS
// ePWM1    GPIO0, GPIO1
// ePWM2    GPIO2, GPIO3
// ePWM3    GPIO4, GPIO5
// ePWM4    GPIO6, GPIO7
// ePWM5    GPIO8, GPIO9
// ePWM6    GPIO10, GPIO11
// ePWM7    GPIO12, GPIO13
// ePWM8    GPIO14, GPIO15
// ePWM9    GPIO161, GPIO162
// ePWM10   GPIO163, GPIO164
// ePWM11   GPIO165, GPIO166
// ePWM12   GPIO167, GPIO168

extern void IO_Init(void);
void digitalWrite(Uint16, Uint16);
void GPIO_Mode(Uint16 gp_pin,Uint16 state);


#define IO_16_ON()        GpioDataRegs.GPASET.bit.GPIO16 = 1 // Turn on the IO
#define IO_16_OFF()        GpioDataRegs.GPACLEAR.bit.GPIO16 = 1 // Turn off the IO
#define IO_16_data()     GpioDataRegs.GPADAT.bit.GPIO16 // Read the data from GPIO
#define IO_16_Toggle()    GpioDataRegs.GPATOGGLE.bit.GPIO16 = 1 // Toggles the state of the GPIO

#define IO_17_ON()        GpioDataRegs.GPASET.bit.GPIO17 = 1 // Turn on the IO
#define IO_17_OFF()        GpioDataRegs.GPACLEAR.bit.GPIO17 = 1 // Turn off the IO
#define IO_17_data()     GpioDataRegs.GPADAT.bit.GPIO17 // Read the data from GPIO
#define IO_17_Toggle()    GpioDataRegs.GPATOGGLE.bit.GPIO17 = 1 // Toggles the state of the GPIO
/*
#define IO_18_ON()        GpioDataRegs.GPASET.bit.GPIO18 = 1 // Turn on the IO
#define IO_18_OFF()        GpioDataRegs.GPACLEAR.bit.GPIO18 = 1 // Turn off the IO
#define IO_18_data()     GpioDataRegs.GPADAT.bit.GPIO18 // Read the data from GPIO
#define IO_18_Toggle()    GpioDataRegs.GPATOGGLE.bit.GPIO18 = 1 // Toggles the state of the GPIO

#define IO_19_ON()        GpioDataRegs.GPASET.bit.GPIO19 = 1 // Turn on the IO
#define IO_19_OFF()        GpioDataRegs.GPACLEAR.bit.GPIO19 = 1 // Turn off the IO
#define IO_19_data()     GpioDataRegs.GPADAT.bit.GPIO19 // Read the data from GPIO
#define IO_19_Toggle()    GpioDataRegs.GPATOGGLE.bit.GPIO19 = 1 // Toggles the state of the GPIO
*/

#define IO_20_ON()        GpioDataRegs.GPASET.bit.GPIO20 = 1 // Turn on the IO
#define IO_20_OFF()        GpioDataRegs.GPACLEAR.bit.GPIO20 = 1 // Turn off the IO
#define IO_20_data()     GpioDataRegs.GPADAT.bit.GPIO20 // Read the data from GPIO
#define IO_20_Toggle()    GpioDataRegs.GPATOGGLE.bit.GPIO20 = 1 // Toggles the state of the GPIO

#define IO_21_ON()        GpioDataRegs.GPASET.bit.GPIO21 = 1 // Turn on the IO
#define IO_21_OFF()        GpioDataRegs.GPACLEAR.bit.GPIO21 = 1 // Turn off the IO
#define IO_21_data()     GpioDataRegs.GPADAT.bit.GPIO21 // Read the data from GPIO
#define IO_21_Toggle()    GpioDataRegs.GPATOGGLE.bit.GPIO21 = 1 // Toggles the state of the GPIO

#define IO_22_ON()        GpioDataRegs.GPASET.bit.GPIO22 = 1 // Turn on the IO
#define IO_22_OFF()        GpioDataRegs.GPACLEAR.bit.GPIO22 = 1 // Turn off the IO
#define IO_22_data()     GpioDataRegs.GPADAT.bit.GPIO22 // Read the data from GPIO
#define IO_22_Toggle()    GpioDataRegs.GPATOGGLE.bit.GPIO22 = 1 // Toggles the state of the GPIO

#define IO_23_ON()        GpioDataRegs.GPASET.bit.GPIO23 = 1 // Turn on the IO
#define IO_23_OFF()        GpioDataRegs.GPACLEAR.bit.GPIO23 = 1 // Turn off the IO
#define IO_23_data()     GpioDataRegs.GPADAT.bit.GPIO23 // Read the data from GPIO
#define IO_23_Toggle()    GpioDataRegs.GPATOGGLE.bit.GPIO23 = 1 // Toggles the state of the GPIO

#define IO_24_ON()        GpioDataRegs.GPASET.bit.GPIO24 = 1 // Turn on the IO
#define IO_24_OFF()        GpioDataRegs.GPACLEAR.bit.GPIO24 = 1 // Turn off the IO
#define IO_24_data()     GpioDataRegs.GPADAT.bit.GPIO24 // Read the data from GPIO
#define IO_24_Toggle()    GpioDataRegs.GPATOGGLE.bit.GPIO24 = 1 // Toggles the state of the GPIO

#define IO_25_ON()        GpioDataRegs.GPASET.bit.GPIO25 = 1 // Turn on the IO
#define IO_25_OFF()        GpioDataRegs.GPACLEAR.bit.GPIO25 = 1 // Turn off the IO
#define IO_25_data()     GpioDataRegs.GPADAT.bit.GPIO25 // Read the data from GPIO
#define IO_25_Toggle()    GpioDataRegs.GPATOGGLE.bit.GPIO25 = 1 // Toggles the state of the GPIO

#define IO_26_ON()        GpioDataRegs.GPASET.bit.GPIO26 = 1 // Turn on the IO
#define IO_26_OFF()        GpioDataRegs.GPACLEAR.bit.GPIO26 = 1 // Turn off the IO
#define IO_26_data()     GpioDataRegs.GPADAT.bit.GPIO26 // Read the data from GPIO
#define IO_26_Toggle()    GpioDataRegs.GPATOGGLE.bit.GPIO26 = 1 // Toggles the state of the GPIO

#define IO_27_ON()        GpioDataRegs.GPASET.bit.GPIO27 = 1 // Turn on the IO
#define IO_27_OFF()        GpioDataRegs.GPACLEAR.bit.GPIO27 = 1 // Turn off the IO
#define IO_27_data()     GpioDataRegs.GPADAT.bit.GPIO27 // Read the data from GPIO
#define IO_27_Toggle()    GpioDataRegs.GPATOGGLE.bit.GPIO27 = 1 // Toggles the state of the GPIO

#define IO_28_ON()        GpioDataRegs.GPASET.bit.GPIO28 = 1 // Turn on the IO
#define IO_28_OFF()        GpioDataRegs.GPACLEAR.bit.GPIO28 = 1 // Turn off the IO
#define IO_28_data()     GpioDataRegs.GPADAT.bit.GPIO28 // Read the data from GPIO
#define IO_28_Toggle()    GpioDataRegs.GPATOGGLE.bit.GPIO28 = 1 // Toggles the state

#define IO_ALL_ON()        GpioDataRegs.GPASET.all = 0xFFFFFFFF // Turn on all the IO
#define IO_ALL_OFF()    GpioDataRegs.GPACLEAR.all = 0xFFFFFFFF // Turn off all the IO
#define IO_ALL_data()     GpioDataRegs.GPADAT.all // Read the data from all GPIO
#define IO_ALL_Toggle()    GpioDataRegs.GPATOGGLE.all=0xFFFF // Toggles the state of all GPIO




void IO_Init()    // This function initialises the I/O's, and it is used in the IO_377D.h file.
{
    EALLOW;
    
    
    //OUTPUTS
    /*
    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0; // Enable pullup on GPIO16
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0; // GPIO16 = I/O ************note: GPIO's 16 to 32 are going through GPAMUX2
    GpioCtrlRegs.GPADIR.bit.GPIO16 = 1; // GPIO16 = output

    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0; // Enable pullup on GPIO17
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0; // GPIO17 = I/O
    GpioCtrlRegs.GPADIR.bit.GPIO17 = 1; // GPIO17 = output
    
    GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0; // Enable pullup on GPIO20
    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 0; // GPIO20 = I/O
    GpioCtrlRegs.GPADIR.bit.GPIO20 = 1; // GPIO20 = output
    
    GpioCtrlRegs.GPAPUD.bit.GPIO21 = 0; // Enable pullup on GPIO21
    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 0; // GPIO21 = I/O
    GpioCtrlRegs.GPADIR.bit.GPIO21 = 1; // GPIO21 = output
    
    GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0; // Enable pullup on GPIO25
    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0; // GPIO25 = I/O
    GpioCtrlRegs.GPADIR.bit.GPIO25 = 1; // GPIO25 = output
    
    GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0; // Enable pullup on GPIO26
    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0; // GPIO26 = I/O
    GpioCtrlRegs.GPADIR.bit.GPIO26 = 1; // GPIO26 = output
    
    GpioCtrlRegs.GPAPUD.bit.GPIO27 = 0; // Enable pullup on GPIO27
    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0; // GPIO27 = I/O
    GpioCtrlRegs.GPADIR.bit.GPIO27 = 1; // GPIO27 = output
    */
    
    //GpioCtrlRegs.GPCPUD.bit.GPIO73 = 0; // Enable pullup on GPIO73
    //GpioCtrlRegs.GPCMUX1.bit.GPIO73 = 3; // GPIO73 = XCLKOUT(0)
    //GpioCtrlRegs.GPCDIR.bit.GPIO73 = 1; // GPIO73 OUTPUT
    
    
    // INPUTS
    /*
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0; // Enable pullup on GPIO18
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 0; // GPIO18 = I/O
    GpioCtrlRegs.GPADIR.bit.GPIO18 = 0; // GPIO18 = ***input***
    
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0; // Enable pullup on GPIO19
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0; // GPIO19 = I/O
    GpioCtrlRegs.GPADIR.bit.GPIO19 = 0; // GPIO19 = ***input***
    
    GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0; // Enable pullup on GPIO22
    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0; // GPIO22 = I/O
    GpioCtrlRegs.GPADIR.bit.GPIO22 = 0; // GPIO22 = *** input***
    
    GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0; // Enable pullup on GPIO23
    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0; // GPIO23 = I/O
    GpioCtrlRegs.GPADIR.bit.GPIO23 = 0; // GPIO23 = ***input***
    
    GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0; // Enable pullup on GPIO24
    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0; // GPIO24 = I/O
    GpioCtrlRegs.GPADIR.bit.GPIO24 = 0; // GPIO24 = ***input***
    
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0; // Enable pullup on GPIO28
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 0; // GPIO28 = I/O
    GpioCtrlRegs.GPADIR.bit.GPIO28 = 0; // GPIO28 = ***input***
    */
    EDIS;
    
}

void digitalWrite(Uint16 IO_number, Uint16 IO_state){
    if (IO_number ==16){
        if (IO_state)
            GpioDataRegs.GPASET.bit.GPIO16 = 1;
        if (IO_state==0)
            GpioDataRegs.GPACLEAR.bit.GPIO16 = 1;
        if (IO_state==2)
            GpioDataRegs.GPATOGGLE.bit.GPIO16 = 1;
    }
    if (IO_number ==17){
        if (IO_state)
            GpioDataRegs.GPASET.bit.GPIO17 = 1;
        if (IO_state==0)
            GpioDataRegs.GPACLEAR.bit.GPIO17 = 1;
        if (IO_state==2)
            GpioDataRegs.GPATOGGLE.bit.GPIO17 = 1;
    }
    if (IO_number ==24){
        if (IO_state)
            GpioDataRegs.GPASET.bit.GPIO24 = 1;
        if (IO_state==0)
            GpioDataRegs.GPACLEAR.bit.GPIO24 = 1;
        if (IO_state==2)
            GpioDataRegs.GPATOGGLE.bit.GPIO24 = 1;
        }
}



void GPIO_Mode(Uint16 gp_pin,Uint16 pin_state){
    EALLOW;
    //if (gp_pin>15 && gp_pin<29){
    //    GPIO_SetupPinOptions(gp_pin,pin_state,GPIO_PULLUP);
    //}
    GPIO_SetupPinOptions(gp_pin,pin_state,GPIO_PULLUP);
    EDIS;

}
