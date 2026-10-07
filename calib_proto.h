// COMMUNICATION
#define CP_CLRL   0
#define CP_STRT   3
#define CP_STOP   2
#define CP_DELE   4
#define CP_SAVE   5
#define CP_PING   6
#define CP_FRSR   0x09
#define CP_FRED   0x0A
// VOLTAGE CONSTANT
#define CP_CV_GT  0x0B
#define CP_CV_ST  0x0C
#define CP_CV_IN  0x0D
#define CP_CV_DE  0x0E
#define CP_CV_SV  0x0F
#define CP_CV_CN  0x10
#define CP_CV_MO  0x11
// CURRENT CONSTANT
#define CP_CC_GT  0x3D
#define CP_CC_ST  0x3E
#define CP_CC_IN  0x3F
#define CP_CC_DE  0x40
#define CP_CC_SV  0x41
#define CP_CC_CN  0x42
#define CP_CC_MO  0x43
// CURRENT TRICKLE
#define CP_TC_GT  0x45
#define CP_TC_ST  0x46
#define CP_TC_IN  0x47
#define CP_TC_DE  0x48
#define CP_TC_SV  0x49
#define CP_TC_CN  0x4A
#define CP_TC_MO  0x4B

#define CP_MX_INV	10000
#define CP_MX_TRY	10

char CP_IN_BUF[5]={0,0,0,0,0};
char CP_CUR_MOD=0;

unsigned int CP_FR_DAT=0;
unsigned int CP_INV_TIM=0;
byte CP_FR_TIM=0;
byte CP_FR_STT=CP_FRED;
byte CP_FR_CMD=0;
byte CP_FR_CNT=0;

char CP_COM_STT=CP_STOP;
byte CP_NEW_PRO=0;

void CP_parse(char a,char b){
				switch(b){
					case 0:if(a==CP_FRSR)CP_FR_STT=CP_FRSR;break;
					case 1:CP_FR_CMD=a;break;
					case 2:CP_FR_DAT=a;break;
					case 3:CP_FR_DAT|=a<<8;break;
					case 4:if(a==CP_FRED)CP_FR_STT=CP_FRED;CP_FR_TIM=0;CP_NEW_PRO=1;CP_INV_TIM=0;break;
		};
 }

void CP_buffer(char a){if(CP_FR_CNT<5){CP_FR_STT=CP_FRSR;CP_IN_BUF[CP_FR_CNT++]=a; };if(CP_FR_CNT>=5){byte i=0;CP_FR_CNT=0;for(i=0;i<5;i++)CP_parse(CP_IN_BUF[i],i); } }

void CP_compile(char c,word d){writeUART(CP_FRSR);writeUART(c);writeUART((byte)d);writeUART((byte)(d>>8));writeUART(CP_FRED); }
void CP_resend(){CP_compile(CP_CUR_MOD,0); }

void CP_comm(char m){CP_CUR_MOD=CP_COM_STT=m;CP_compile(CP_CUR_MOD,0); }
void CP_ping(){CP_compile(CP_PING,0); }
void CP_mode(char m){CP_CUR_MOD=m;CP_compile(CP_CUR_MOD,0); }