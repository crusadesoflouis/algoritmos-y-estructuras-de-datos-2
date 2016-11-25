#include "aed2.h"
#include "coordenada.h"


coordenada::coordenada(Nat lat, Nat lon): latitu(lat),longitu(lon){

}

Nat coordenada::latitud()const {
  return latitu;
}

Nat coordenada::longitud()const{
  return longitu;
}

bool coordenada::operator == (const coordenada& c2)const{
  return latitu == c2.latitud() and longitu == c2.longitud();
}

bool coordenada::operator != (const coordenada& c2)const{
return ! (latitu == c2.latitud()) && (longitu==c2.longitud());
}

Nat coordenada::cuadRestaLat(const coordenada& c1 , const coordenada& c2){
		if (c1.latitud() > c2.latitud())
			return ( (c1.latitud() - c2.latitud()) ^ 2 );
		else
			return ( (c2.latitud() - c1.latitud()) ^ 2 );
}

Nat coordenada::cuadRestaLong (const coordenada& c1 , const coordenada& c2 ){
		if (c1.longitud() > c2.longitud())
			return ( (c1.longitud() - c2.longitud()) ^ 2 );
		else
			return ( (c2.longitud() - c1.longitud()) ^ 2 );
}

Nat coordenada::distEuclidea(const coordenada& c1 , const coordenada& c2 ){
		return cuadRestaLat(c1,c2) + cuadRestaLong(c1,c2);
}
/*
*/
