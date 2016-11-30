#include <iostream>
#include "DiccMatriz.h"
using namespace std;


class Mapa {

        public:

                Mapa();

                ~Mapa();

                bool Vacia() const;

                void AgregarCoord(const coordenada& c);

                bool PosExistente(const coordenada& c) const;

                bool HayCamino(const coordenada &c,const coordenada &d) const;


              //  void mostrar();

        private:

              DiccMatriz <bool> mapa;
              //latitud es x
              //Nat maxLatitud;
              //longitud es y
			        //Nat maxLongitud;
              void AgregarAdyacentes(Conj<coordenada> &Avisitar,const coordenada &c);
};
