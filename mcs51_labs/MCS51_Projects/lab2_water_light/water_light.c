#include <8051.h>

void delay(unsigned int ms) {
	unsigned int i, j;
	for(i = 0; i < ms; i++){
	for(j = 0; j < 120; j++);
	}
}

void main(){
	unsigned char light = 0x01;

	while(1){
		P1 = ~light;

		delay(500);

		light = light << 1;

		if(light == 0x00){
		light = 0x01;
		}
	}
}

