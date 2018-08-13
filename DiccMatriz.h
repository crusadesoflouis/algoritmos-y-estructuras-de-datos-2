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
Nat DiccMatriz<T>::Longitud() const{
return grilla.EsVacio() ? 0 : grilla[0].Longitud();
}

template <typename T>
Nat DiccMatriz<T>::Latitud() const{
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
    //cout << "solo una vez"<<  endl;
      Vector<T> aux;
      grilla.AgregarAtras(aux);
      grilla[0].AgregarAtras(default_value);
    //  cout << " es vacio entre aca y agregue el prmer elemento por defalt el valor de la longitud es :"<< grilla.Longitud()<< endl;
    }
    //cout << "c.latitud()"<<c.latitud()<<endl;
    //cout << "c.longitud()"<<c.longitud()<<endl;

  if (c.latitud() < (Latitud()) && c.longitud() < (Longitud())) {
    //cout<< "estoy en rango "<< endl;
    grilla[c.latitud()][c.longitud()] = significado;
  }
  else{

    Vector<T> aux;
    unsigned int guarda = grilla.Longitud();
    //cout << "como no estoy en rango tengo que agrandar y la longitud aca es:"<< grilla.Longitud();
    //cout << " la latitud es: " << grilla[0].Longitud() << endl;
    for (unsigned int i = guarda; i < c.latitud()+1; i++) {
      grilla.AgregarAtras(aux);
    }
    Nat flag = c.latitud()+1;
    for (unsigned int i = 0; i < flag; i++) {
      for (unsigned int j = grilla[i].Longitud()  ; j < c.longitud()+1; j++) {
        grilla[i].AgregarAtras(default_value);
      }
    }
    grilla[c.latitud()][c.longitud()] = significado;
  }
  posicionesValidas.Agregar(c);
}

template <typename T>
bool DiccMatriz<T>::Definido(const Coordenada & c) const{
  //cout << "voy a buscar el dato a  : (" <<  c.latitud()<< ","<< c.longitud()<< ")"<< endl;
  if (FueraDeRango(c)) {
    return false;
  //  cout << "esta fuera de rango "<< endl;
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
