#ifndef DICC_STRING_H_
#define DICC_STRING_H_

#include "aed2.h"
#include <iostream>
#include <cassert>
#include "aed2/TiposBasicos.h"

using namespace std;



template<typename T>

class DiccMatriz {

        public:
				
                /**
                CONSTRUCTOR
                * Construye un diccionario vacio.
                **/
                DiccMatriz();

                void Mostrar() const;

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
                bool Definido(tup tupla) const;

                /**
                OBTENER
                * Dada una clave, devuelve su significado.
                * PRE: La clave está definida.
                */
                T& Obtener(tup tupla);

                /**
                OBTENER
                * Dada una clave, la borra del diccionario junto a su significado.
                * PRE: La clave está definida.
                --PRODUCE ALIASING--
                **/
                void Borrar(tup tupla);


                /**
                CLAVES
                * Devuelve las claves del diccionario.
                --NO PRODUCE ALIASING--
                **/
                const Conj<tup>& Claves() const;

        private:
				
              //latitud es x
              //latitud es Y
              Vector <Vector <T> > grilla;
              int maxLatitud;
              int maxLongitud;
              
              Conj<tup> keys;
      };

                
//TODO: funciones auxiliares
bool FueraDeRango(int posicionX, int posicionY,int latitud,int longitud){
  if (posicionX > latitud || posicionY > longitud) {
    return false;
  }
  else{
    return true;
  }
}

//creo que no hace falta definir tampoco el constructor

template <typename T>
DiccMatriz<T>::DiccMatriz():Matriz(),claves(),{

}


template <typename T>
void DiccMatriz<T>::Definir(tup tupla, const T& significado){
if (!(tupla.lat < latitud || tupla.log < longitud)) {
  for (int i = 0; i < tupla.lat - latitud; i++) {
  	Vector<T> aux;
    Matriz.AgregarAtras(aux.Vacia());
    for (int j = 0; j < tupla.log - longitud; j++) {
      Matriz[i].AgregarAtras(NULL);
      }
    }
  }
Matriz[tupla.lat][tupla.log] = significado;
claves.Agregar(tupla);

}


template <typename T>
bool DiccMatriz<T>::Definido(tup tupla) const{
if (FueraDeRango(tupla.lat,tupla.log,latitud,longitud)) {
  return false;
}
else{
    if (!(Matriz[tupla.lat][tupla.log] == NULL)) {
      return true;
    }
    else{
      return false;
    }
}
}


template <typename T>
T& DiccMatriz<T>::Obtener(tup tupla) {
assert(Definido(tupla));
return Matriz[tupla.lat][tupla.log];
}


template <typename T>
const Conj<tup>& DiccMatriz<T>::Claves() const{
return claves;
}

template <typename T>
void DiccMatriz<T>::Mostrar() const {
    std::cout << "[";

}

template <typename T>
void DiccMatriz<T>::Borrar(tup tupla) {
assert(Definido(tupla));
Matriz[tupla.lat][tupla.log] = NULL;
claves.Eliminar(tupla);
}


#endif
