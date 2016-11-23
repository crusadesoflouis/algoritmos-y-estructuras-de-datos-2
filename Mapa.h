#include <iostream>
#include "DiccMatriz.h"
using namespace std;


class Mapa {

        public:

                Mapa();

                ~Mapa();

                bool Vacia() const;

                void AgregarCoord(const Coordenada& c);

                bool PosExistente(const Coordenada& c) const;

                bool HayCamino(const Coordenada &c,const Coordenada &d) const;


              //  void mostrar();

        private:

              DiccMatriz <bool> mapa;
              //latitud es x
              //Nat maxLatitud;
              //longitud es y
			        //Nat maxLongitud;
              void AgregarAdyacentes(Conj<Coordenada> &Avisitar,const Coordenada &c);

};
