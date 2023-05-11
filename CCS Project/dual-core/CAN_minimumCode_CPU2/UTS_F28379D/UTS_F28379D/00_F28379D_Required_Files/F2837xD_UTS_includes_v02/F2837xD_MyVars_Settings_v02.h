// Board
unsigned int Board_Type = 1;  //0: LaunchPad;  1: ControlCard_AERI

// Sampling Time in seconds
float Ts = 0.001;           //This value will be recalculated when setting the ADCA

Uint16 baut_int =139;
Uint16 update_uart_speed = 0;
/* PWM Setting Variables
******************************************************************/

// PWM Settings
Uint16          update_Epwms = 1;
Uint16    EPWM_ALL_CMP = 0;  //1: All EPWMs complementary A(pos) and B(inv)
                             //0: ALL EPWMs independent

Uint16          EPWM_ALL_TYPE = 0; //0:Symmetric, 1: Up, 2: Down

// Main PWM Clock
float CLK_FQ = 100000;      // in kHz
float DB_Gain_ns = 0.1;     // Dead-time gain

// Carriers Frequency
float EPWM_ALL_FQ = 1;          //fc in kHz
float EPWM_ALL_PRD = 0.001;     //Carriers Period in seconds (Tc=1000/fc)
float EPWMx_FQ[12];             //frequency of each ePWM in kHz
Uint16 EPWMx_IND_FQ=0;    //Ues first 12 bits to indicate if a ePWM is independant
Uint16 EPWMx_FQ_MULT[12]={1,1,1,1,1,1,1,1,1,1,1,1};   //Use if one ePWM is faster than ePWM1


// PWMs Maximum Count
unsigned int EPWM_ALL_TMAX = 5000;  //Max count for all sync carriers
unsigned int EPWMx_TMAX[12];        //Max count per ePWM

// Phase shift
float EPWMx_PS_DEG[12];             //Phase shif in degree per ePWM
unsigned int EPWMx_PS[12];          //Phase shif in counts per ePWM
Uint16 EPWMx_PHSDIR[12];          //ePWM initial direcion up or down

// Dead-Time
float EPWM_ALL_DB = 0;              //Dead-time in nanoseonds for all sync carriers
float EPWMx_DB[12];                 //Dead-time in nanoseonds for each ePWM
Uint16 EPWMx_COMP[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

/* ADCs
******************************************************************/

#define SingleUpdate_Zero    0
#define SingleUpdate_Max     1
#define DoubleUpdate        2
#define RES_12BIT           12
#define RES_16BIT           16

Uint16 ADC_EPWM = 2;   // 1 defaults
Uint16 ADC_Trigger = 0;
Uint16 ADC_A_ch_in[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
Uint16 ADC_B_ch_in[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
Uint16 ADC_C_ch_in[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
Uint16 ADC_D_ch_in[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
Uint16 ADC_A_input[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
Uint16 ADC_B_input[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
Uint16 ADC_C_input[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
Uint16 ADC_D_input[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
Uint16 SOC_counter=0;
Uint16 SOC_EOC=0;

/* IOs
******************************************************************/
#define ON      1
#define OFF     0
#define HIGH    1
#define LOW     0
#define INPUT   0
#define OUTPUT  1
#define TOGGLE  2

/* Serial Communication
******************************************************************/
#define Buffer_size 1000

int     External_int[20];
float   External_float[20];
Uint16  External_instruction=0;
Uint16  data_buff[6][Buffer_size];
Uint16  flag_fill_buffer =1;
Uint16  cont_buffer=0;


typedef union
{
 float number;
 Uint16 uint16[2];
} FloatUnion_t;

FloatUnion_t myfloat;

