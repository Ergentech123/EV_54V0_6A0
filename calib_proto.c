#include "VariableAndSub.h"
#include "calib_proto.h"

void CP_Proc(){while(CP_COM_STT==CP_STRT){PIN_LED_G=0;PIN_LED_R=0;
if(CP_NEW_PRO==1){
		switch(CP_FR_CMD){
//    case CP_CLRL:CP_IC_BUF=0;break;
    case CP_STRT:CP_comm(CP_STRT);break;
    case CP_DELE:EraseEEPROM(EEP_AD_CAS);EraseEEPROM(EEP_AD_CV);EraseEEPROM(EEP_AD_CC);EraseEEPROM(EEP_AD_TC);CP_mode(CP_DELE);break;

    case CP_CV_MO:_da0=cal_CC;_da1=cal_CV;CP_mode(CP_CV_MO);break;
		case CP_CV_IN:cal_CV+=CP_FR_DAT;_da1=cal_CV;CP_mode(CP_CV_CN);break;
		case CP_CV_DE:cal_CV-=CP_FR_DAT;_da1=cal_CV;CP_mode(CP_CV_CN);break;
    case CP_CV_CN:CP_mode(CP_CV_CN);break;
    case CP_CV_SV:EEP_VAL_Write(EEP_AD_CV,cal_CV,1);CP_mode(CP_CV_SV);break;

    /*case CP_TC_MO:cal_TC=TC_OUT_DIG;_da0=TC_OUT_DIG;_da1=cal_CV;CP_mode(CP_TC_MO);break;
		case CP_TC_IN:cal_TC+=CP_FR_DAT;_da0=cal_TC;CP_mode(CP_TC_CN);break;
		case CP_TC_DE:cal_TC-=CP_FR_DAT;_da0=cal_TC;CP_mode(CP_TC_CN);break;
    case CP_TC_CN:CP_mode(CP_TC_CN);break;
    case CP_TC_SV:EEP_VAL_Write(EEP_AD_TC,cal_TC,1);CP_mode(CP_TC_SV);break;*/

    case CP_CC_MO:_da0=cal_CC;_da1=cal_CV;CP_mode(CP_CC_MO);break;
		case CP_CC_IN:cal_CC+=CP_FR_DAT;_da0=cal_CC;CP_mode(CP_CC_CN);break;
		case CP_CC_DE:cal_CC-=CP_FR_DAT;_da0=cal_CC;CP_mode(CP_CC_CN);break;
    case CP_CC_CN:CP_mode(CP_CC_CN);break;
    case CP_CC_SV:EEP_VAL_Write(EEP_AD_CC,cal_CC,1);CP_mode(CP_CC_SV);break;

    case CP_SAVE:EEP_VAL_Write(EEP_AD_CAS,1,1);CP_mode(CP_SAVE);break;
    case CP_STOP:CP_comm(CP_STOP);break;
		case CP_PING:CP_ping();break;
  };
Delayus(1);CP_NEW_PRO=0; };if(CP_INV_TIM>CP_MX_INV){CP_INV_TIM=0;CP_COM_STT=CP_STOP;return; } } }

void CP_Check(){if(CP_NEW_PRO){Delayus(1);CP_NEW_PRO=0;if(CP_FR_CMD==CP_PING)CP_ping();if(CP_FR_CMD==CP_STRT)CP_comm(CP_STRT); } }

void CP_Tick(){CP_INV_TIM++;if(CP_FR_STT==CP_FRSR)CP_FR_TIM++;if(CP_FR_TIM>12){CP_FR_STT=CP_FRED;CP_FR_CNT=0;CP_FR_TIM=0; }; }