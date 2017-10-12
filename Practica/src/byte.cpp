#include <iostream>
#include "byte.h"
using namespace std;


void onBit(Byte &b, int pos){
	Byte mask = 0x1 << pos;
	b= b | mask;
}

void offBit(Byte &b, int pos){
	Byte mask = 0x1<<pos;
	mask= ~mask;
	b=b&mask;
}

bool getBit(Byte b, int pos){
	Byte mask = 0x1<<pos;
	return (b & mask)==mask;
}

void imprimirByte(Byte b){
	for(int i=7; i>=0; i--){
		cout << getBit(b, i);
	}
}

void onByte(Byte &b){
	Byte mask = ~(0x0);
	b=b|mask;
}

void offByte(Byte &b){
	Byte mask = 0x0;
	b=b&mask;
}

void asignarByte(Byte &b, const bool v[]){
	offByte(b);
	for(int i=7; i>=0; i--){
		if(v[i]){
			onBit(b,7-i);
		}
	}
}

void volcarByte(Byte b, bool v[]){
	for(int i=0; i<8; i++){
		v[i]=getBit(b,i);
	}
}

void encendidosByte(Byte b, int posic[], int &cuantos){
	cuantos=0;
	for(int i=0; i<8; i++){
		if(getBit(b,i)){
			posic[cuantos]=i;
			cuantos++;
		}
	}
}
