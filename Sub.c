#include "VariableAndSub.h"
typedef unsigned int uint;
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//////////////////////////		ADC NO SAM 1		////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
word ADCData(char channel){word ret=0;
//    _sadc1&=0b00011111;
  if(channel==0x10){_sadc0=0b00110000|(0x0f); }else{_sadc0=0b00110000|(channel & 0x0f); }			
//	if((channel&0x80)==0)_sadc1=0b00001011;else _sadc1=0b00010011;	
  if(channel==0x10){_sains0=1; }else{_sains0=0; };
  _start=0;_start=1;_start=0;while(_adbz==1);
ret=((_sadoh&0x00ff)<<8)|_sadol;_start=0;_start=1;_start=0;return ret;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//////////////////////////		ADC 10 SAM 2		////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*word ADC10Data2(char channel){byte i;word adcmax,adcmin;unsigned long int adcacc;word ret;_sadc1&=0b00011111;
	if(channel==0x10){_sadc0=0b00110000|(0x0f); }else{_sadc0=0b00110000|(channel & 0x0f); }			
	if((channel&0x80)==0)_sadc1=0b00001011;else _sadc1=0b00010011;	
  if(channel==0x10){_sains0=1; }
  _start=0;_start=1;_start=0;
	adcmax=0;adcmin=65535;adcacc=0;				

  for(i=0;i<ADC_SRT;i++){while(_adbz==1){};ret=((_sadoh&0x00ff)<<8)|_sadol;_start=0;_start=1;_start=0;			
   if(ret>adcmax)adcmax=ret;if(ret<adcmin)adcmin=ret;adcacc=ret+adcacc; }
	 ret=adcacc-adcmax;ret=ret-adcmin;ret=ret>>3;_adcen=0;return ret;
}*/

word ADC10Data3(char c){byte i;unsigned long a=0;for(i=0;i<ADC_SRT;i++){a+=ADCData(c); }; return(word)(a/ADC_SRT); }
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//////////////////////////			UART COM		////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*void writeUART(char a){_txr_rxr=a;while(_tidle==0); }
    	
/ *void writeFloat(float v){
    	writeUART((((word)v)/10)+0x30);
      writeUART(((((word)v&0xff))%10)+0x30);
    	writeUART('.');
    	writeUART(((((word)(v*10)))%10)+0x30);
		writeUART(((((word)(v*100)))%10)+0x30);
    writeUART(((((word)(v*1000)))%10)+0x30); }
* /
void writeWord(word v){writeUART(v&0xff);writeUART(v>>8); }*/
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//////////////////////////					LED DISPLAY			////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ledMode(word vb,word ib){if(ib>CR_IND_1_ANL){PIN_LED_R=0;PIN_LED_G=1; }else if(ib<CR_IND_0_ANL){PIN_LED_R=1;PIN_LED_G=0; } }
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//////////////////////////					RELAY ON_OF			////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void relayMode(byte a){PIN_REL=a;Delayms(1000); }
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//////////////////////////					CALIBER			////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void caliber(){PIN_LED_R=0;PIN_LED_G=0;Delayms(3000);
	word adv=0,adi=0;
//	word dav=0;
//	float dav_err=1;
//	EEP_VAL_Write(EEP_AD_VE,adv,1);
	_da0=20;
	relayMode(1);
	//dav=(word)(adc_v_err>=1?((float)(CV_OUT_DIG)*adc_v_err):((float)(CV_OUT_DIG)/adc_v_err))+30;
	cal_CV=CV_OUT_DIG;cal_CC=CC_OUT_DIG;
	_da1=cal_CV;//_da0=cal_CC;
//	while(1);
	PIN_LED_G=0;PIN_LED_R=1;
	Delayms(1000);PIN_CALB_SEL_TC=1;Delayms(5000);
	ADC10Data3(Vbat_ch);
	adv=ADC10Data3(Vbat_ch);
	adv=ADC10Data3(Vbat_ch);
	adc_v_err=(float)V_ADC_CALIB_DIG/(float)adv;

	PIN_CALB_SEL_TC=0;
	Delayms(1000);_da0=CC_CALIB_DIG;Delayms(10);
	PIN_LED_R=0;PIN_LED_G=1;
	PIN_CALB_SEL_CC=1;Delayms(5000);

	ADC10Data3(Ibat_ch);
	adi=ADC10Data3(Ibat_ch);
	adc_i_err=(float)I_ADC_CALIB_DIG/(float)adi;
	PIN_CALB_SEL_CC=0;Delayms(1000);

	while(1){word vb=GET_VB();
    if(vb<CV_V_ANL-15)cal_CV++;else if(vb>(CV_V_ANL+15))cal_CV--;else break;_da1=cal_CV-5;Delayus(20);_da1=cal_CV;
	Delayms(300);PIN_LED_G=0;Delayms(300);PIN_LED_G=1; };

	PIN_LED_G=1;PIN_CALB_SEL_TC=1;_da0=cal_CC;Delayms(2000);
	
	while(1){word ib=GET_IB();
    if(ib<CC_OUT_ANL-10)cal_CC++;else if(ib>(CC_OUT_ANL+10))cal_CC--;else break;_da0=cal_CC-5;Delayus(20);_da0=cal_CC;
	Delayms(300);PIN_LED_R=0;Delayms(300);PIN_LED_R=1; };

	PIN_CALB_SEL_TC=0;Delayms(1000);_da0=cal_TC;Delayms(100);PIN_CALB_SEL_TC=1;Delayms(2000);
	
	while(1){word ib=GET_IB();
    if(ib<TC_OUT_ANL-10)cal_TC++;else if(ib>(TC_OUT_ANL+10))cal_TC--;else break;_da0=cal_TC-5;Delayus(20);_da0=cal_TC;
	Delayms(300);PIN_LED_R=0;Delayms(300);PIN_LED_R=1; };

	PIN_CALB_SEL_TC=0;Delayms(1000);

	//dav_err=(((float)cal_CV/(float)CV_OUT_DIG)*2)-1;
//	cal_CC=(word)((float)cal_CC*dav_err);
	EEP_VAL_Write(EEP_AD_CAS,1,1);
	EEP_VAL_Write(EEP_AD_CV,cal_CV,1);
	EEP_VAL_Write(EEP_AD_VE,adv,1);
	EEP_VAL_Write(EEP_AD_CE,adi,1);
	EEP_VAL_Write(EEP_AD_CC,cal_CC,1);
	EEP_VAL_Write(EEP_AD_TC,cal_TC,1);
	PIN_LED_R=1;PIN_LED_G=1;relayMode(0);
};