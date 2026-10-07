#include "VariableAndSub.h"

void main(){initial();initLed();
	initRelay();_emi=1;
	initCharger();//_lvrc=0b10100101;
	initTime0();
	initEEPROMset();
	_emi=1;
	prs_ib=0;prs_vb=0;
	phase=PH_SB;prs_phase=PH_SB;
	_wdtc=0b10101111;
	initAdc();
	initCalb();
	Delayms(1);
	if(!ReadEEPROM(EEP_AD_CAS)){caliber(); }
	_da1=cal_CV;_da0=cal_CC;
//	initUart();
	relayMode(1);PIN_LED_R=1;PIN_LED_G=0;//PIN_CALB_SEL_CV=1;
//	while(1);
while(1){
word p_phase=phase;
word vb=CK_IN_V_Chn();
word ib=CK_IN_C_Chn();
	PH_Check(vb,ib);
	ledMode(vb,ib);
	if(phase!=prs_phase){prs_phase=phase;PH_Start(vb,ib); }
	PH_Run(vb,ib);
	Delayms(10);
	};
}

//DEFINE_ISR(ISR_UR,0x08){CP_buffer(_txr_rxr); }
DEFINE_ISR(ISR_T0,0x0c){/*CP_Tick();*/ }