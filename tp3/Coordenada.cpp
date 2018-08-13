#include "aed2.h"
#include "Coordenada.h"


Coordenada::Coordenada(Nat lat, Nat lon): latitu(lat),longitu(lon){

}

Nat Coordenada::latitud()const {
  return latitu;
}

Nat Coordenada::longitud()const{
  return longitu;
}

Coordenada Coordenada::operator = (const Coordenada &c2){
  latitu = c2.latitud();
  longitu = c2.longitud();
  return *this;
}
bool Coordenada::operator == (const Coordenada& c2)const{
  return latitu == c2.latitud() and longitu == c2.longitud();
}

bool Coordenada::operator != (const Coordenada& c2)const{
return ! (latitu == c2.latitud()) && (longitu==c2.longitud());
}

/*
Nat Coordenada::cuadRestaLat(const Coordenada &c2){
  latitu > c2.latitud() ? return ( (latitu - c2.latitud()) ^ 2 ): return ( (c2.latitud() - latitu) ^ 2 )
}
*/
Nat Coordenada::cuadRestaLat(const Coordenada& c2){
		if (latitu > c2.latitud())
			return ( (latitu - c2.latitud()) ^ 2 );
		else
			return ( (c2.latitud() - latitu) ^ 2 );
}

Nat Coordenada::cuadRestaLong (const Coordenada& c2 ){
		if (longitu > c2.longitud())
			return ( (longitu - c2.longitud()) ^ 2 );
		else
			return ( (c2.longitud() - longitu) ^ 2 );
}


Nat Coordenada::distEuclidea(const Coordenada& c2 ){
    Nat a = 0;
    Nat b = 0;
    if (latitu > c2.latitud())
      a = ( (latitu - c2.latitud()) ^ 2 );
    else
      a =  ( (c2.latitud() - latitu) ^ 2 );

      if (longitu > c2.longitud())
  		b =	 ( (longitu - c2.longitud()) ^ 2 );
  		else
  		b =  ( (c2.longitud() - longitu) ^ 2 );
		//return cuadRestaLat(c1,c2) + cuadRestaLong(c1,c2);
    return a+b;
}
