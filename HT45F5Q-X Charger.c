#include "VariableAndSub.h"

void main(){initial();initLed();
	initRelay();_emi=1;
	initCharger();//_lvrc=0b10100101;
	initTime0();
	initEEPROMset();
	_emi=1;
	prs_ib=0;prs_vb=0;
	phase=PH_SB;prs_phase=PH_SB;prs_tm=0;
	_wdtc=0b10101111;
	initAdc();
	initCalb();
	Delayms(1);
	if(!ReadEEPROM(EEP_AD_CAS)){caliber(); }
	_da1=cal_CV;_da0=cal_CC;cal_CC_NT=cal_CC;
//	initUart();
	relayMode(1);PIN_LED_R=1;PIN_LED_G=0;//PIN_CALB_SEL_CV=1;
//	while(1);
while(1){
word p_phase=phase;
word vb=CK_IN_V_Chn();
word ib=CK_IN_C_Chn();
prs_tm=ADC10Data3(Tbat_ch);
if(phase==PH_CC){if(prs_tm<=TEM_ADC_DEG_EN){cal_CC=cal_CC_OT;_da0=cal_CC;Delayus(1); }
if(prs_tm>=TEM_ADC_DEG_DS){cal_CC=cal_CC_NT;_da0=cal_CC;Delayus(1); } }
	PH_Check(vb,ib);
	ledMode(vb,ib);
	if(phase!=prs_phase){prs_phase=phase;PH_Start(vb,ib); }
	PH_Run(vb,ib);
	Delayms(10);
	};
}

//DEFINE_ISR(ISR_UR,0x08){CP_buffer(_txr_rxr); }
DEFINE_ISR(ISR_T0,0x0c){/*CP_Tick();*/ }