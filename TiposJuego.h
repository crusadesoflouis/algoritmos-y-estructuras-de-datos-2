#ifndef TIPOSJUEGO_H_
#define TIPOSJUEGO_H_

#include "aed2/TiposBasicos.h"

typedef unsigned int Jugador;
typedef std::string Pokemon;



struct Coordenada
{
	Nat latitud;
	Nat longitud;
	Coordenada(Nat lat, Nat longi) : latitud(lat), longitud(longi){
	}

	bool operator == (const Coordenada& c1){
	 return latitud == c1.latitud and longitud == c1.longitud;
	}

	bool operator != (const Coordenada& c1){
	 return not (latitud == c1.latitud and longitud == c1.longitud);
	}


};


#endif
