/********* Comunicacion serie dos arduinos***********

payload = 234, 214, numero de bytes , suma de bytes, datos.........,215,   235
           0    1     2                       3         4           l-2     l-1

		   el numero de bytes es numero de datos + 6




*/


#include "comunica.h"
/*
#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
*/

comunica::comunica(){
		cadenaAcabada = false;
		contador = 0;
		Serial2.begin(9600);
}

byte comunica::leePuerto(){
	byte longDatos=0;
	byte b1;
	while (Serial2.available()){
			b1 = Serial2.read();
			if (contador < 64){
				pl[contador] = b1;
				contador ++;
			}else{
				contador = 0;
				pl[contador] = b1;
				contador ++;
			}
			if (b1 == C_FIN_DOS){
				if (contador > 1){
					if (pl[contador-2] == C_FIN_UNO){
						cadenaAcabada = true;
						contador = 0;
						break;
					}
				}
			}
			if (b1 == C_INI_DOS){
				if (contador > 1){
					if (pl[contador-2] == C_INI_UNO){
						contador = 2;
						pl[1] = C_INI_DOS;
						pl[0] = C_INI_UNO;
					}
				}
			}
	}
	if (cadenaAcabada == true){
		if (cadenaComprueba() == true){
				longDatos = pl[2]-6 ;
				for(int i=0 ; i<longDatos ; i++){
					dt[i] = pl [i +4];
				}
		}
		cadenaAcabada = false;
		contador = 0;
	}
	return(longDatos);
}
byte comunica::getDato(byte posicion){
	return(dt[posicion]);
}

void comunica::enviaDatos(byte datos[58],byte longDatos){
	for(int i=0;i<longDatos;i++){
		pl[i+4] = datos[i];
	}
	pl[0] = C_INI_UNO; pl[1] = C_INI_DOS ; pl[longDatos + 4] = C_FIN_UNO; pl[longDatos + 5] = C_FIN_DOS;
	pl[2] = longDatos + 6;
	pl[3] = calculaChecksum();
	Serial2.write(pl,longDatos + 6);
}

boolean comunica::cadenaComprueba(){
	boolean esCorrecta = true;
	int largo = pl[2];
	esCorrecta = (pl[0] == C_INI_UNO) && (pl[1] == C_INI_DOS) && (pl[largo-2] == C_FIN_UNO) && (pl[largo-1] == C_FIN_DOS);
	if (esCorrecta == true){
		esCorrecta = (calculaChecksum() == pl[3]);
	}
	return(esCorrecta);
}
byte comunica::calculaChecksum(){
	int suma = 0;
	byte cs;
	for (int i = 4 ; i < pl[2] ; i++){
		suma = suma + pl[i];
	}
	cs =  (suma % 256);
	cs = 255 - cs;
	return(cs);
}
