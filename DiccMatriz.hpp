#ifndef DICC_STRING_H_
#define DICC_STRING_H_

#include <iostream>
#include <cassert>
#include "aed2.h"
#include "TiposJuego.h"




using namespace std;



template<typename T>

class DiccMatriz {

        public:

                /**
                CONSTRUCTOR
                * Construye un diccionario vacio.
                **/
                DiccMatriz();
                /**
                DEFINIR
                * Recibe una clave con su significado de tipo T y la define.
                * Si ya estaba definida, la reescribe.
                **/
                void Definir(const Coordenada& c, const T& significado);

                /**
                DEFINIDO?
                * Devuelve un bool, que es true si la clave pasada está definida en
                * el diccionario.
                **/
                bool Definido(const Coordenada& c) const;

                /**
                OBTENER
                * Dada una clave, devuelve su significado.
                * PRE: La clave está definida.
                */
                T& Obtener(const Coordenada& c);

                /**
                OBTENER
                * Dada una clave, la borra del diccionario junto a su significado.
                * PRE: La clave está definida.
                --PRODUCE ALIASING--
                **/
                void Borrar(const Coordenada& c);

                bool FueraDeRango(const Coordenada& c) const;
                /**
                CLAVES
                * Devuelve las claves del diccionario.
                --NO PRODUCE ALIASING--
                **/
                const Conj<Coordenada> & Claves() const;

        private:

              Vector < Vector <T> > grilla;

              Nat maxLatitud;

			        Nat maxLongitud;

              Conj<Coordenada> posicionesValidas;
};


//TODO: funciones auxiliares
/*bool FueraDeRango(int posicionX, int posicionY,int latitud,int longitud){
  if (posicionX > latitud || posicionY > longitud) {
    return false;
  }
  else{
    return true;
  }
}*/
template <typename T>
bool DiccMatriz<T>::FueraDeRango(const Coordenada& c) const {
    return  ! (c.latitud() < maxLatitud && c.longitud() < maxLongitud );
}

//creo que no hace falta definir tampoco el constructor

template <typename T>
DiccMatriz<T>::DiccMatriz(): grilla(),posicionesValidas(),maxLatitud(0),maxLongitud(0){
}

/*
template <typename T>
void DiccMatriz<T>::Definir(const Coordenada& c , const T& significado){
		if ( c.longitud > maxLongitud ){
			for(Nat x = 0; x < c.longitud -  maxLongitud; x++ ){
				Vector<T> nuevoX;
				grilla.AgregarAtras(nuevoX);
			}
		}
		if ( c.latitud > maxLatitud ){
        std::cout << "entre a c.latitud mayor" << std::endl;
			for(Nat y=0; y < c.longitud -  maxLongitud; y++ ){

				grilla[c.longitud].AgregarAtras(NULL);
			}
		}
  std::cout << "tamaño de la matriz" << std::endl;
  std::cout << grilla.Longitud() << std::endl;
  std::cout << "tamaño de la altura" << std::endl;
  std::cout << grilla[c.longitud].Longitud() << std::endl;
	grilla [c.longitud][c.latitud] = significado;
	posicionesValidas.Agregar(c);
  maxLatitud = c.latitud;
  maxLongitud = c.longitud;

}
*/

template <typename T>
void DiccMatriz<T>::Definir(const Coordenada& c, const T& significado){
if (!(c.latitud < maxLatitud || c.longitud < maxLongitud)) {
  Vector<T> aux;
  for (unsigned int  i = 0; i < c.latitud - maxLatitud; i++) {
    grilla.AgregarAtras(aux);
    for (unsigned int  j = 0; j < c.longitud - maxLongitud; j++) {
      grilla[i].AgregarAtras(NULL);
      }
    }
  }
grilla[c.latitud-1][c.longitud-1] = significado;
posicionesValidas.Agregar(c);
maxLongitud = c.longitud;
maxLatitud = c.latitud;
}


template <typename T>
bool DiccMatriz<T>::Definido(const Coordenada& c) const{
	return false;
}



/*if (FueraDeRango(tupla.lat,tupla.log,latitud,longitud)) {
  return false;
}
else{
    if (!(Matriz[tupla.lat][tupla.log] == NULL)) {
      return true;
    }
    else{
      return false;
    }
}*/


///--------------------------------------------------------------------------------------------------


template <typename T>
T& DiccMatriz<T>::Obtener(const Coordenada& c) {
assert(Definido(c));
return grilla[c.latitud()][c.longitud()];
}

template <typename T>
const Conj<Coordenada>& DiccMatriz<T>::Claves() const{

	return posicionesValidas;
}

template <typename T>
void DiccMatriz<T>::Borrar(const Coordenada& c) {
assert(Definido(c));
grilla[c.latitud()][c.longitud()] = NULL;
posicionesValidas.Eliminar(c);
}


#endif
