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
                * PRE: La clave está definida.
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
                return c.latitud() <= Latitud() && c.longitud() <= Longitud() && c.latitud() != 0 && c.longitud() != 0;
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

//creo que no hace falta definir tampoco el constructor

template <typename T>
DiccMatriz<T>::DiccMatriz(){};


template <typename T>
DiccMatriz<T>::DiccMatriz(T default_value): grilla(), default_value(default_value),posicionesValidas(){
}

template <typename T>
void DiccMatriz<T>::Definir(const Coordenada & c, const T& significado){

  if (grilla.EsVacio()) {
    cout << " la grilla es vacia" << endl;
      Vector<T> aux;
      grilla.AgregarAtras(aux);
      grilla[0].AgregarAtras(default_value);
    }
    cout << "latitud de la coordenada " << c.latitud() <<endl;
        cout << "longitud de la coordenada " << c.longitud() <<endl;
    cout << "salimos, la longitud de la grilla es  " << grilla.Longitud() << endl;
    cout << "la latitud de la grilla es:" << grilla[0].Longitud()<<endl;
  if (c.latitud() < (Latitud() - 1) && c.longitud() < (Longitud() - 1)) {
    cout << " estoy en rango "<< endl;
    grilla[c.latitud()][c.longitud()] = significado;
  }
  else{
    cout << " no estoy en rango  "<< endl;
    Vector<T> aux;
    for (unsigned int i = Latitud() -1; i < c.latitud(); i++) {
      cout << "agregue atras " << endl;
      grilla.AgregarAtras(aux);
    }
    cout << " la latitud es " << c.latitud() << endl;
    for (unsigned int i = 0; i < c.latitud(); i++) {
      cout << "grilla sub i . longitud: " << grilla[i].Longitud() << endl;
      for (unsigned int j = grilla[i].Longitud() - 1 ; j < c.longitud(); j++) {
                cout << " entre al segundo for " << endl;
        grilla[i].AgregarAtras(default_value);
      }
    }
    cout << "bom" << endl;
    cout << "la latitud es: "<< grilla.Longitud()<<endl;
    cout << "la longitud es: "<< grilla[0].Longitud()<<endl;
    cout << "la longitud es: "<< grilla[1].Longitud()<<endl;
        cout << "bom" << endl;
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
  for (int i = 0; i < grilla.Longitud(); i++) {
    std::cout << "la cantidad de filas en grilla_"<< i <<  " son " << grilla[i].Longitud() << std::endl;
  }
}



#endif
