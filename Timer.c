#include "VariableAndSub.h"

void Delayus(char delaycount){
	if(Fsys==16000000){
	  	asm("nop");     //1CLK
  		asm("sdz acc"); //1CLK
   	 	asm("jmp $-2"); //2CLK
	}
	
	if(Fsys==8000000){
	  	GCC_RR(_acc);     //1CLK
  		asm("and a,7fh");   		
	    asm("sz z"); //1CLK
    	asm("jmp Delayusend");
  		asm("nop");     //1CLK
    	asm("sdz acc"); //1CLK
	    asm("jmp $-2"); //2CLK
	    asm ("Delayusend:");
	}
}

void Delayms(word delaycount){int i;
    for(i=0;i<delaycount;i++){
        Delayus(250);
        Delayus(250);
        Delayus(250);
        Delayus(250);
    	GCC_CLRWDT();
    }
}