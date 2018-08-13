#include <iostream>
#include "aed2.h"
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
              Nat max;

              //latitud es x
              //Nat maxLatitud;
              //longitud es y
			        //Nat maxLongitud;
              void AgregarAdyacentes(Conj<Coordenada> &Avisitar,const Coordenada &c);
              Nat FDX(const Nat x,const Nat y, const bool FDR )const ;
              Coordenada PosicionReal(const Coordenada &c)const ;
              Nat Maximo(const Nat x, const Nat y )const;
              Coordenada correccion(const Coordenada &c)const;
};
