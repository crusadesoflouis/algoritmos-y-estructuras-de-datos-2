#include <iostream>
#include "aed2.h"
#include "DiccMatriz.h"
using namespace std;


class Mapa {

        public:

  //              Class const_Iterador;

                Mapa();

                ~Mapa();

                bool Vacia() const;

                void AgregarCoord(const Coordenada& c);

                bool PosExistente(const Coordenada& c) const;

                bool HayCamino(const Coordenada &c,const Coordenada &d) const;

                typename Conj<Coordenada>::const_Iterador PosicionesValidas()const;
              //  void mostrar();
/*
              class Iterador
              {
                public:

                  Iterador();
                  bool HaySiguiente() const;
                  const T& Siguiente() const;
                  void Avanzar();

                private:

                  typename DiccMatriz<bool>::Iterador it_dicc_;

                  Iterador(Conj<T>& c);

                  Iterador(const typename Dicc<T,bool>::Iterador& itDict);
              };
*/

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
