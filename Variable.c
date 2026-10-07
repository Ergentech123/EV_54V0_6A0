#include "VariableAndSub.h"

word cal_TC;
word cal_CC;
word cal_CV;

byte phase;
byte prs_phase;
word prs_ib;
word prs_vb;
word prs_tm;
//float adc_err;
float adc_v_err;
float adc_i_err;
int millis;
//const unsigned int I_IN_RR=(int)(((float)I_IN_R2/(float)((float)I_IN_R1+(float)I_IN_R2))*(float)I_IN_RSH);
//const float ADC_V_IN_V_OUT_RR=(float)(((float)V_IN_R1+(float)V_IN_R2)/(float)V_IN_R2);
//const float ADC_V_OUT_V_IN_RR=(float)V_IN_R2/((float)V_IN_R1+(float)V_IN_R2);
//////////////////////////////////////////////////////
////////////////		CURRENT CALC		//////////////////
//////////////////////////////////////////////////////
//const unsigned int CC_IREF_DIG=(long)CC_OUT_ANL*I_IN_RR*OP2A_GN*(ADC_SIZ/ADC_REF)/1000000;
//const unsigned int TC_IREF_DIG=(long)TC_OUT_ANL*I_IN_RR*OP2A_GN*(ADC_SIZ/ADC_REF)/1000000;
//const unsigned int SB_IREF_DIG=(long)SB_OUT_ANL*I_IN_RR*OP2A_GN*(ADC_SIZ/ADC_REF)/1000000;
//const unsigned int CC_IREF_MIN_DIG=(long)CC_IREF_MIN_ANL*I_IN_RR*OP2A_GN*(ADC_SIZ/ADC_REF)/1000000;
//const unsigned int CC_IREF_MAX_DIG=(long)CC_IREF_MAX_ANL*I_IN_RR*OP2A_GN*(ADC_SIZ/ADC_REF)/1000000;

//const unsigned int CR_IND_0_DIG=((long)CR_IND_0_ANL*I_IN_RR*OP2A_GN*(ADC_SIZ/ADC_REF)/1000000);//-310
//const unsigned int CR_IND_1_DIG=((long)CR_IND_1_ANL*I_IN_RR*OP2A_GN*(ADC_SIZ/ADC_REF)/1000000);
//const unsigned int I_ACC_DIG=(long)I_ACC_ANL*I_IN_RR*OP2A_GN*(ADC_SIZ/ADC_REF)/1000000;
word cal_CC_NT=(long)(I_IN_RR)*CC_OUT_ANL*(DAC_SIZ_1/DAC_REF)/1000000;
word cal_CC_OT=(long)(I_IN_RR)*CC_OUT_OT_ANL*(DAC_SIZ_1/DAC_REF)/1000000;
const unsigned int TC_OUT_DIG=(long)(I_IN_RR)*TC_OUT_ANL*(DAC_SIZ_1/DAC_REF)/1000000;
const unsigned int CC_OUT_DIG=(long)(I_IN_RR)*CC_OUT_ANL*(DAC_SIZ_1/DAC_REF)/1000000;
const unsigned int SB_OUT_DIG=(long)(I_IN_RR)*SB_OUT_ANL*(DAC_SIZ_1/DAC_REF)/1000000;
const unsigned int CC_CALIB_DIG=(long)(I_IN_RR)*CC_CALIB_ANL*(DAC_SIZ_1/DAC_REF)/1000000;
//////////////////////////////////////////////////////
////////////////		VOLTAGE CALC		//////////////////
//////////////////////////////////////////////////////
//const unsigned int FV_OUT_DIG=(long)FV_ANL*(float)((float)V_IN_R2/(float)(V_IN_R1+V_IN_R2))/10*(DAC_SIZ/DAC_REF);
const unsigned int CV_OUT_DIG=(long)CV_V_ANL*(float)((float)V_IN_R2/(float)(V_IN_R1+V_IN_R2))/1000*(float)((float)DAC_SIZ/(float)DAC_REF);
//const unsigned int V_ACC_DIG=(long)V_ACC_ANL*(float)((float)V_IN_R2/(float)(V_IN_R1+V_IN_R2))/1000*(float)((float)ADC_SIZ/(float)ADC_REF);

//const unsigned int TC_ON_VREF_DIG=(long)TC_ON_VREF_ANL*(float)((float)V_IN_R2/(float)(V_IN_R1+V_IN_R2))/1000*(float)((float)ADC_SIZ/(float)ADC_REF);
//const unsigned int CC_ON_VREF_DIG=(long)CC_ON_VREF_ANL*(float)((float)V_IN_R2/(float)(V_IN_R1+V_IN_R2))/1000*(float)((float)ADC_SIZ/(float)ADC_REF);
//const unsigned int CV_ON_VREF_DIG=(long)CV_ON_VREF_ANL*(float)((float)V_IN_R2/(float)(V_IN_R1+V_IN_R2))/1000*(float)((float)ADC_SIZ/(float)ADC_REF);
//const unsigned int CV_ON_VREF_MIN_DIG=CV_ON_VREF_MIN_ANL*(float)((float)V_IN_R2/(float)(V_IN_R1+V_IN_R2))/10*(float)((float)ADC_SIZ/(float)ADC_REF);
//const unsigned int CV_MAX_VREF_DIG=(long)CV_V_ANL*(float)((float)V_IN_R2/(float)(V_IN_R1+V_IN_R2))/1000*(float)((float)ADC_SIZ/(float)ADC_REF);
//const unsigned int CV_MAX_DIG=CV_MAX_ANL*(float)((float)V_IN_R2/(float)(V_IN_R1+V_IN_R2))/10*(float)((float)ADC_SIZ/(float)ADC_REF);
const unsigned int MAX_VREF_DIG=(long)MAX_V_ANL*(float)((float)V_IN_R2/(float)(V_IN_R1+V_IN_R2))/1000*(float)((float)DAC_SIZ/(float)DAC_REF);

word TEM_ADC_DEG_EN=((long)4096*TEM_RES_DEG_EN/(TEM_RES_DEG_EN+TEM_RES_CONST))*2;//628
word TEM_ADC_DEG_DS=((long)4096*TEM_RES_DEG_DS/(TEM_RES_DEG_DS+TEM_RES_CONST))*2;//726