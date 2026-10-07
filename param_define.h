#include "HT45F5Q-2A.h"

#define Fsys 									8000000	//Fsys=HIRC Ext:8M=8000000
//////////////////////////////////////////////////////
////////////		PIN DEFINE	 		//////////////
//////////////////////////////////////////////////////
#define	PIN_LED_G  						    _pa4
#define	PIN_LED_R 						    _pa3
#define	PIN_REL							    _pb6
#define	PIN_CALB						    _pa7
#define	PIN_CALB_ADC_V					    5
#define PIN_CALB_SEL_TC                     _pa7
#define PIN_CALB_SEL_CC                     _pb5
#define PIN_CALB_SEL_VA                     _pa0
//////////////////////////////////////////////////////
////////////			ADC VARS 		//////////////
//////////////////////////////////////////////////////
#define ADC_SRT								100//adc sampling rate
#define ADC_ERR								1
#define	ADC_REF								(float)2.5
#define ADC_SIZ								4096
#define ADC_SIZ_1							16384
#define ADC_VPB								(float)(ADC_REF/ADC_SIZ)
#define ADC_BPV								(float)(ADC_SIZ/ADC_REF)

#define OP2A_GN								20
//////////////////////////////////////////////////////
////////////			DAC VARS 		//////////////
//////////////////////////////////////////////////////
#define	DAC_REF								(float)5
#define DAC_SIZ								4096
#define DAC_SIZ_1							16384
//////////////////////////////////////////////////////
////////////		PHASE NUMBER 		//////////////
//////////////////////////////////////////////////////
#define PH_SB 								0//phase standby
#define PH_TC								1//phase tricle charge
#define PH_CC								2//phase constant current
#define PH_CV								3//phase constant voltage
#define	PH_DEL								500//
//////////////////////////////////////////////////////
////////////	RESISTOR SETTING		//////////////
//////////////////////////////////////////////////////
#define	I_IN_RSH							101//Current shunt resistor in mili ohm
#define I_IN_R1                             27000
#define I_IN_R2                             18000
#define I_IN_RR                             (int)(((float)I_IN_R2/(float)((float)I_IN_R1+(float)I_IN_R2))*(float)I_IN_RSH)

#define	V_IN_R1								56350//Voltage divider r1 V_BAT	 	to V_ADC_CH	[ohm]	 		   	
#define	V_IN_R2								2700 //Voltage divider r2 V_ADC_CH 	to GND 		[ohm]

#define WIRE_RES                            3//a*100 mili ohm
//////////////////////////////////////////////////////
////////////	CURRENT SETTING 		//////////////
//////////////////////////////////////////////////////
#define	TC_OUT_ANL 						    500//Tricle charge [mili ampere]				 		   	
#define	CC_OUT_ANL						    2550//Constant current [mili ampere]
#define	CC_CALIB_ANL						3200//Constant current [mili ampere]
#define	SB_OUT_ANL						    300//Constant current [x*100 mili ampere]
#define	CC_IREF_MAX_ANL				        (CC_OUT_ANL-100)//Constant current differential ref [mili ampere]
#define	CC_IREF_MIN_ANL				        300
#define	I_ACC_ANL							30//Constant current differential ref [mili ampere]
#define	CR_IND_0_ANL					    300//Trickle on current [mili ampere]
#define	CR_IND_1_ANL					    500//Trickle on current [mili ampere]

#define I_Y2_REF_ANL                        1837  
#define I_X2_REF_ANL                        100
#define V_TRN_VREF_ANL                      300//mode transition voltage differance
#define I_ADC_CALIB_DIG                     3238
//////////////////////////////////////////////////////
////////////		VOLTAGE SETTING		//////////////
//////////////////////////////////////////////////////
#define CV_V_ANL		 					42200//full voltage [mv]
//#define CV_MAX_ANL  		 				425//full voltage [mv]
#define MAX_V_ANL		 					45000//max voltage for increament [mv]
#define V_ACC_ANL		 					100//full voltage [mv]
#define V_CHN_DEL							10//delay [ms]

#define TC_ON_VREF_ANL				        22000//Trickle current on at voltage [mv]
#define CC_ON_VREF_ANL				        29000//constant current on at voltage [mv]
#define CV_ON_VREF_ANL				        41600//constant voltage on at voltage [mv]

#define V_ADC_CALIB_DIG                     1808
//#define CV_ON_VREF_MIN_ANL				    41000//constant voltage increament at voltage [mv]
//////////////////////////////////////////////////////
////////////	TEMPERATURE SETTING		//////////////
//////////////////////////////////////////////////////
//#define	c_OTCCSetting					13//??:0.1A exp:13=0.1A*13=1.3A,????100??1.25?????1.3
//#define c_TempResistor				    10000//Unit ohm, resistance value of over-temperature protection			 		   	
//#define	c_TempRwarning				    1900//Unit ohm, resistance value to release over-temperature protection			 		   	
//#define	c_TempRwarningRemove	        2200

//#define	c_ADCTempRwarning               (long)4096*c_TempRwarning/(c_TempRwarning+c_TempResistor)
//#define	c_ADCTempRwarningRemove	        (long)4096*c_TempRwarningRemove/(c_TempRwarningRemove+c_TempResistor) //739
//////////////////////////////////////////////////////
////////////		CHANNEL SETTING		//////////////
//////////////////////////////////////////////////////
#define Tbat_ch								4//ADC temp channel	 		 										 		   	
#define Vbat_ch								2//ADC voltage channel
#define Ibat_ch								0x10//ADC current channel
//////////////////////////////////////////////////////
////////////			EEPROM SETTING				//////////////
//////////////////////////////////////////////////////
#define EEP_AD_CAS						    0
#define EEP_AD_NU1						    4
#define EEP_AD_TC							8
#define EEP_AD_CC							12
#define EEP_AD_CV							16
#define EEP_AD_NU2						    20
#define EEP_AD_CE							24
#define EEP_AD_VE							28