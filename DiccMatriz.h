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


                bool Vacio() const;
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

                Nat Latitud() const;

                Nat Longitud() const;

                void mostrar();
        private:

              Vector < Vector <T> > grilla;
              //latitud es x
              //Nat Latitud;
              //longitud es y
			        //Nat Longitud;

              Conj<Coordenada> posicionesValidas;
              
              bool enRango(const Coordenada & c)const{
                return c.latitud <= Latitud() && c.longitud <= Longitud();
              }
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
bool DiccMatriz<T>::Vacio() const{
  return grilla.EsVacio();
}

template <typename T>
Nat DiccMatriz<T>::Latitud() const{
return grilla.EsVacio() ? 0 : grilla[0].Longitud();
}

template <typename T>
Nat DiccMatriz<T>::Longitud() const{
return grilla.Longitud();
}

template <typename T>
bool DiccMatriz<T>::FueraDeRango(const Coordenada& c) const {
    return  ! enRango(c);
}

//creo que no hace falta definir tampoco el constructor

template <typename T>
DiccMatriz<T>::DiccMatriz(): grilla(),posicionesValidas(){
}

template <typename T>
void DiccMatriz<T>::Definir(const Coordenada& c, const T& significado){

  if (grilla.EsVacio()) {
      Vector<T> aux;
      grilla.AgregarAtras(aux);
      grilla[0].AgregarAtras(NULL);
      grilla[0][0] = significado;
  }
  else{
    if (c.latitud < Latitud() && c.longitud < Longitud()) {
      grilla[c.latitud-1][c.longitud-1] = significado;
    }
    else{
      Vector<T> aux;
      for (unsigned int i = Latitud(); i < c.latitud; i++) {
        grilla.AgregarAtras(aux);
      }
      for (unsigned int i = 0; i < c.latitud; i++) {
        for (unsigned int j = grilla[i].Longitud() ; j < c.longitud; j++) {
          grilla[i].AgregarAtras(NULL);
        }
      }
      grilla[c.latitud-1][c.longitud-1] = significado;
    }
  }
  posicionesValidas.Agregar(c);
}

template <typename T>
bool DiccMatriz<T>::Definido(const Coordenada& c) const{
  if (FueraDeRango(c)) {
    return false;
  }
  else{
    return grilla[c.latitud-1][c.longitud-1] != NULL;
  }
}

template <typename T>
void DiccMatriz<T>::Borrar(const Coordenada& c) {
assert(Definido(c));
grilla[c.latitud-1][c.longitud-1] = NULL;
posicionesValidas.Eliminar(c);
}

template <typename T>
T& DiccMatriz<T>::Obtener(const Coordenada& c) {
assert(Definido(c));
return grilla[c.latitud-1][c.longitud-1];
}

template <typename T>
const Conj<Coordenada>& DiccMatriz<T>::Claves() const{
	return posicionesValidas;
}

template <typename T>
void DiccMatriz<T>::mostrar(){

  std::cout << "la cantidad de columnas son " << grilla.Longitud() << std::endl;
  for (int i = 0; i < grilla.Longitud(); i++) {
    std::cout << "la cantidad de filas en grilla_"<< i <<  " son " << grilla[i].Longitud() << std::endl;
  }
}



#endif
