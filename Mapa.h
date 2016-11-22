#ifndef DICC_STRING_H_
#define DICC_STRING_H_

#include <iostream>
#include <cassert>
#include <DiccMatriz.h>




using namespace std;



template<typename T>

class Mapa {

        public:

                CrearMapa();

                void AgregarCoord(const Coordenada& c);

                bool posExistente(const Coordenada& c) const;

                bool hayCamino(const Coordenada &c) const;

                void mostrar();

        private:

              DiccMatriz< bool > mapa;
              //latitud es x
              //Nat maxLatitud;
              //longitud es y
			        //Nat maxLongitud;
              Nat maxLatitud()const{
                return mapa.Longitud();
              }
              Nat maxLongitud()const{
                return mapa.EsVacio() ? 0 : mapa[0].Longitud();
              }
              bool enRango(const Coordenada & c)const{
                return c.latitud <= maxLatitud() && c.longitud <= maxLongitud();
              }
};




#endif
