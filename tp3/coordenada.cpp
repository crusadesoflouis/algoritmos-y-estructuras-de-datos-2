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

coordenada coordenada::operator = (const coordenada &c2){
  latitu = c2.latitud();
  longitu = c2.longitud();
  return *this;
}
bool coordenada::operator == (const coordenada& c2)const{
  return latitu == c2.latitud() and longitu == c2.longitud();
}

bool coordenada::operator != (const coordenada& c2)const{
return ! (latitu == c2.latitud()) && (longitu==c2.longitud());
}

/*
Nat coordenada::cuadRestaLat(const coordenada &c2){
  latitu > c2.latitud() ? return ( (latitu - c2.latitud()) ^ 2 ): return ( (c2.latitud() - latitu) ^ 2 )
}
*/
Nat coordenada::cuadRestaLat(const coordenada& c2){
		if (latitu > c2.latitud())
			return ( (latitu - c2.latitud()) ^ 2 );
		else
			return ( (c2.latitud() - latitu) ^ 2 );
}

Nat coordenada::cuadRestaLong (const coordenada& c2 ){
		if (longitu > c2.longitud())
			return ( (longitu - c2.longitud()) ^ 2 );
		else
			return ( (c2.longitud() - longitu) ^ 2 );
}


Nat coordenada::distEuclidea(const coordenada& c2 ){
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
