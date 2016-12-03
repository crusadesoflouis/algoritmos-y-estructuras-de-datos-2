#ifndef DICC_MATRIZ_H
#define DICC_MATRIZ_H

#include <iostream>
#include <cassert>
#include "aed2.h"
#include "Coordenada.h"


using namespace std;



template<typename T>

class DiccMatriz {

        public:

                /**
                CONSTRUCTOR
                * Construye un diccionario vacio.
                **/
                DiccMatriz();

                DiccMatriz(T default_value);
                /**
                DEFINIR
                * Recibe una clave con su significado de tipo T y la define.
                * Si ya estaba definida, la reescribe.
                **/
                void Definir(const Coordenada & c, const T& significado);

                /**
                DEFINIDO?
                * Devuelve un bool, que es true si la clave pasada está definida en
                * el diccionario.
                **/
                bool Definido(const Coordenada & c) const;


                bool Vacio() const;
                /**
                OBTENER
                * Dada una clave, devuelve su significado.
                * PRE: La clave está definidac
                */
                T& Obtener(const Coordenada & c);

                /**
                OBTENER
                * Dada una clave, la borra del diccionario junto a su significado.
                * PRE: La clave está definida.
                --PRODUCE ALIASING--
                **/
                void Borrar(const Coordenada & c);

                bool FueraDeRango(const Coordenada & c) const;
                /**
                CLAVES
                * Devuelve las claves del diccionario.
                --NO PRODUCE ALIASING--
                **/
                const Conj<Coordenada > & Claves() const;

                Nat Latitud() const;

                Nat Longitud() const;
                //mostrar es solo para debug
                void mostrar();
        private:

              Vector < Vector <T> > grilla;
              T default_value;
              //latitud es x
              //Nat Latitud;
              //longitud es y
			        //Nat Longitud;
              Conj<Coordenada > posicionesValidas;
              bool enRango(const Coordenada  & c)const{
                return c.latitud() <= Latitud() && c.longitud() <= Longitud();
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
bool DiccMatriz<T>::FueraDeRango(const Coordenada & c) const {
    return  ! enRango(c);
}


template <typename T>
DiccMatriz<T>::DiccMatriz(){};


template <typename T>
DiccMatriz<T>::DiccMatriz(T default_value): grilla(), default_value(default_value),posicionesValidas(){
}

template <typename T>
void DiccMatriz<T>::Definir(const Coordenada & c, const T& significado){

  if (grilla.EsVacio()) {
      Vector<T> aux;
      grilla.AgregarAtras(aux);
      grilla[0].AgregarAtras(default_value);
    }

  if (c.latitud() < (Latitud()) && c.longitud() < (Longitud())) {
    grilla[c.latitud()][c.longitud()] = significado;
  }
  else{
    Vector<T> aux;
    unsigned int guarda = grilla.Longitud();
    for (unsigned int i = guarda; i < c.longitud()+1; i++) {
      grilla.AgregarAtras(aux);
    }
    Nat flag = c.latitud()+1;
    for (unsigned int i = 0; i < flag; i++) {
      for (unsigned int j = grilla[i].Longitud()  ; j < c.longitud()+1; j++) {
        grilla[i].AgregarAtras(default_value);
      }
    }
/*
    cout << "bom" << endl;
    cout << "la latitud es: "<< grilla.Longitud()<<endl;
    cout << "la longitud es: "<< grilla[0].Longitud()<<endl;
    cout << "la longitud es: "<< grilla[1].Longitud()<<endl;

    cout << "la longitud es: "<< grilla[3].Longitud()<<endl;
    cout << "la longitud es: "<< grilla[4].Longitud()<<endl;
    cout << "la longitud es: "<< grilla[5].Longitud()<<endl;
    cout << "la longitud es: "<< grilla[6].Longitud()<<endl;
    cout << "la longitud es: "<< grilla[7].Longitud()<<endl;
    cout << "la longitud es: "<< grilla[8].Longitud()<<endl;
    cout << "la longitud es: "<< grilla[9].Longitud()<<endl;
    cout << "la longitud es: "<< grilla[10].Longitud()<<endl;
    cout << "bom" << endl;
*/
    grilla[c.latitud()][c.longitud()] = significado;
  }

  posicionesValidas.Agregar(c);
}

template <typename T>
bool DiccMatriz<T>::Definido(const Coordenada & c) const{
  if (FueraDeRango(c)) {
    return false;
  }
  else{
    return grilla[c.latitud()][c.longitud()] != default_value;
  }
}

template <typename T>
void DiccMatriz<T>::Borrar(const Coordenada & c) {
assert(Definido(c));
grilla[c.latitud()][c.longitud()] = default_value;
posicionesValidas.Eliminar(c);
}

template <typename T>
T& DiccMatriz<T>::Obtener(const Coordenada & c) {
assert(Definido(c));
return grilla[c.latitud()][c.longitud()];
}

template <typename T>
const Conj<Coordenada >& DiccMatriz<T>::Claves() const{
	return posicionesValidas;
}

template <typename T>
void DiccMatriz<T>::mostrar(){

  std::cout << "la cantidad de columnas son " << grilla.Longitud() << std::endl;
  for (unsigned int i = 0; i < grilla.Longitud(); i++) {
    std::cout << "la cantidad de filas en grilla_"<< i <<  " son " << grilla[i].Longitud() << std::endl;
  }
}



#endif
