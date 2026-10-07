#include "Param_define.h"

typedef unsigned char u8;
typedef unsigned char byte;
typedef unsigned int  word;

extern word cal_TC;
extern word cal_CC;
extern word cal_CV;

extern byte phase;
extern byte prs_phase;
extern word prs_ib;
extern word prs_vb;
//////////////////////////////////////////////////////
////////////////		RES CALC		//////////////////
//////////////////////////////////////////////////////
//extern const unsigned int I_IN_RR;
//extern const float ADC_V_IN_V_OUT_RR;
//extern const float ADC_V_OUT_V_IN_RR;
//////////////////////////////////////////////////////
////////////////		CURRENT CALC		//////////////////
//////////////////////////////////////////////////////
//extern const unsigned int CC_IREF_DIG;
//extern const unsigned int TC_IREF_DIG;
//extern const unsigned int SB_IREF_DIG;
//extern const unsigned int CC_IREF_MIN_DIG;
//extern const unsigned int CC_IREF_MAX_DIG;

//extern const unsigned int CR_IND_0_DIG;
//extern const unsigned int CR_IND_1_DIG;
//extern const unsigned int I_ACC_DIG;

extern const unsigned int TC_OUT_DIG;
extern const unsigned int CC_OUT_DIG;
extern const unsigned int SB_OUT_DIG;
extern const unsigned int CC_CALIB_DIG;
//////////////////////////////////////////////////////
////////////////		VOLTAGE CALC		//////////////////
//////////////////////////////////////////////////////
//extern const unsigned int FV_OUT_DIG;
extern const unsigned int CV_OUT_DIG;

//extern const unsigned int V_ACC_DIG;
//extern const unsigned int TC_ON_VREF_DIG;
//extern const unsigned int CC_ON_VREF_DIG;
//extern const unsigned int CV_ON_VREF_DIG;
//extern const unsigned int CV_ON_VREF_MIN_DIG;
extern const unsigned int MAX_VREF_DIG;
//extern const unsigned int CV_MAX_VREF_DIG;
//extern const unsigned int CV_MAX_DIG;
//extern float adc_err;
extern float adc_v_err;
extern float adc_i_err;
extern int millis;
//////////////////////////////////////////////////////
/////////////////////	STATICS	 ///////////////////////
//////////////////////////////////////////////////////
__attribute__((at(0x12))) static volatile word _sado; //_sad0l and _sad0h synthesize 16bit _sado
__attribute__((at(0x32))) static volatile word _da0; //_da0l and _da0h synthesize 16bit _da0
__attribute__((at(0x34))) static volatile word _da1; //_da1l and _da1h synthesize 16bit _da1
__attribute__((at(0x43))) static volatile word _ed0; //_ed0l and _ed0h synthesize 16bit _ed0
__attribute__((at(0x45))) static volatile word _ed1;  	
__attribute__((at(0x47))) static volatile word _ed2;  
__attribute__((at(0x49))) static volatile word _ed3; 

//init.c
void initial(void);
//void ClearRAM(void);
void initEEPROMset(void);
void initCharger();
void initAdc();
void initRelay();
void initLed();
void initCalb();
//void initUart();

//sub.c
//void writeMod(char a);
//void writeFloat(float v);
//void writeWord(word v);
//void writeUART(char a);
void ledMode(word vb,word ib);
word ADCData(char channel);
void caliber();
//word ADC10Data2(char channel);
word ADC10Data3(char c);
void ledMode(word vb,word ib);
void relayMode(byte a);

//Timer.c
void Delayus(char delaycount);
void Delayms(word delaycount);
void initTime0(void);

//Phase.c
word GET_IB();
word GET_VB();
word CK_IN_V_Chn();
word CK_IN_C_Chn();

//void PH_str_SB(word vb,word ib);
void PH_str_TC(word vb,word ib);
void PH_str_CC(word vb,word ib);
void PH_str_CV(word vb,word ib);

//void PH_run_SB(word vb,word ib);
//void PH_run_TC(word vb,word ib);
void PH_run_CC(word vb,word ib);
//void PH_run_CV(word vb,word ib);

void PH_Check(word vb,word ib);
void PH_Start(word vb,word ib);
void PH_Run(word vb,word ib);
//EEPROM.c
void EraseEEPROM(byte Addr);
void WriteEEPROM(byte Addr,word val,word val1,word val2,word val3);
word ReadEEPROM(byte Addr);
void EEP_VAL_Write(byte adr,word val,word stt);
//word EEP_VAL_Read(byte adr);

//calib_proto.c
//void CP_Check();
//void CP_Proc();
//void CP_Call();
//void CP_parse(char a,char b);
//void CP_compile(char c,word d);
//void CP_resend();
//void CP_comm(char m);
//void CP_ping();
//void CP_mode(char m);
//void CP_buffer(char a);
//void CP_Tick();