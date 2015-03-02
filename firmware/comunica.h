/********* Comunicacion serie dos arduinos***********

payload = 234, 214, numero de bytes , suma de bytes, datos.........,215,   235
           0    1     2                       3         4           l-2     l-1

		   el numero de bytes es numero de datos + 6




*/
#ifndef comunica_h
#define comunica_h

/**********para arduino**********
#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
********************************/

//***********para spark************
#include "application.h"
#include "Serial2/Serial2.h"
/*******************************/

#define C_FIN_UNO 215
#define C_FIN_DOS 235
#define C_INI_UNO 234
#define C_INI_DOS 214

class comunica{
	public:
		comunica();
		byte leePuerto();//devuelve longitud datos
		byte getDato(byte posicion);
		void enviaDatos(byte datos[58],byte longDatos);
	private:
		byte pl[64];  //64 es el tamaño del buffer serie
		byte dt[58]; //datos
		byte contador ;
		boolean cadenaAcabada ;
		boolean cadenaComprueba();
		byte calculaChecksum();

};

#endif
