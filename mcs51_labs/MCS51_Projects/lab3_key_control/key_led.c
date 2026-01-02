#include<8051.h>

#define LED P1_0
#define KEY P3_2

void delay(unsigned int ms) {
	unsigned int i, j;
	for(i = 0; i < ms; i++){
		for(j = 0; j < 120; j++);
	}
}

void main(){
	//初始化
	LED = 1;
	KEY = 1;

	while(1){
		if(KEY == 0) {
			
			delay(20);
			if(KEY == 0){
				LED = !LED;

				while(KEY == 0);
			}
		}
	}
}
