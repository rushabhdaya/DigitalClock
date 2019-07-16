#include<reg51.h>
sbit rs = P2^1;
sbit rw = P2^2;
sbit en = P2^3;
unsigned char h = 0, m = 0, s = 0;

void delay() {
 	char a = 0;
	for (a = 0; a <100; a++); 
}

void cmd_lcd(unsigned char a) {
	rs = 0;
	rw = 0;
	P0 = a;
	en = 1;
	delay();
	en = 0;
}
void data_lcd(unsigned char b) {
 	rs = 1;
	rw = 0;
	P0 = b;
	en = 1;
	delay();
	en = 0;
}

void init_lcd() {
	cmd_lcd(0x38);
	cmd_lcd(0x01);
	cmd_lcd(0x0C);
	cmd_lcd(0x06); 	
}

 void hdelay() {
	unsigned char a;
	for (a = 0; a < 20; a++) {
	 	TMOD = 0x01;
		TH0 = 0x4b;
		TL0 = 0x27;
		TR0 = 1;
		while(TF0 == 0);
		TF0=0;
		TR0 = 0;
	}
}

void main() {
	int i = 0;
	init_lcd();
	cmd_lcd(0x80);
	while(1) {
		hdelay();
		s++;
		if (s % 60 == 0) {
			s = 0;
			m++;
			if (m % 60 == 0) {
				m = 0;
				h++;
				if (h % 24 == 0) {
					h = 0;
				}
			}
		}
		P3 = s;
		P1 = m;
	} 

}
