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
};

bool operator == (const Coordenada& c1, const Coordenada& c2){
 return c1.latitud == c2.latitud and c1.longitud == c2.longitud;
}

bool operator != (const Coordenada& c1, const Coordenada& c2){
 return not (c1 == c2);
}

Nat cuadRestaLat (const Coordenada& c1 , const Coordenada& c2 ){
		if (c1.latitud > c2.latitud)
			return ( (c1.latitud - c2.latitud) ^ 2 );
		else
			return ( (c2.latitud - c1.latitud) ^ 2 );
}

Nat cuadRestaLong (const Coordenada& c1 , const Coordenada& c2 ){
		if (c1.longitud > c2.longitud)
			return ( (c1.longitud - c2.longitud) ^ 2 );
		else
			return ( (c2.longitud - c1.longitud) ^ 2 );
}

Nat distEuclidea(const Coordenada& c1 , const Coordenada& c2 ){
		return cuadRestaLat(c1,c2) + cuadRestaLong(c1,c2);
}



#endif
