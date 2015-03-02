/********* Comunicacion serie dos arduinos***********

payload = 234, 214, numero de bytes , suma de bytes, datos.........,215,   235
           0    1     2                       3         4           l-2     l-1

		   el numero de bytes es numero de datos + 6




*/
#include "comunica.h"

byte dt[58]; //datos
byte longDatos;

comunica comserie;

void setup(){
	//Serial.begin(9600);

	dt[0] = 2;
	dt[1] = 8;
	comserie.enviaDatos(dt,2);

}
void loop(){
	longDatos = comserie.leePuerto();
	if (longDatos > 0){
		//Serial.print("Recibido   ");
		for(byte i=0;i< longDatos;i++){
			dt[i] = comserie.getDato(i);
			//Serial.print(dt[i]);
			//Serial.print("  ");
		}
		//Serial.println("");
	}
	delay(2000);
	dt[0] = 2;
	dt[1] = 8;
	dt[2] = 25;
	longDatos = 3;
	//Serial.print("Enviando   ");
	for(int i=0;i< longDatos;i++){
			//Serial.print(dt[i]);
			//Serial.print("  ");
	}
	//Serial.println("");
	comserie.enviaDatos(dt,longDatos);
}
