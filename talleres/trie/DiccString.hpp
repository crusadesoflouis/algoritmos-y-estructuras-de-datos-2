#ifndef DICC_STRING_H_
#define DICC_STRING_H_

#include "Conj.hpp"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;


template<typename T>
class DiccString {
        public:
                /**
                CONSTRUCTOR
                * Construye un diccionario vacio.
                **/
                DiccString();

                /**
                CONSTRUCTOR POR COPIA
                * Construye un diccionario por copia.
                **/
                DiccString(const DiccString<T>&);


                /**
                DESTRUCTOR
                **/
                ~DiccString();

                /**
                DEFINIR
                * Recibe una clave con su significado de tipo T y la define.
                * Si ya estaba definida, la reescribe.
                **/
                void Definir(const string& clave, const T& significado);

                /**
                DEFINIDO?
                * Devuelve un bool, que es true si la clave pasada está definida en
                * el diccionario.
                **/
                bool Definido(const string& clave) const;

                /**
                OBTENER
                * Dada una clave, devuelve su significado.
                * PRE: La clave está definida.
                --PRODUCE ALIASING--
				-- Versión modificable y no modificable
                **/
				const T& Obtener(const string& clave) const;
                T& Obtener(const string& clave);

                /**
                OBTENER
                * Dada una clave, la borra del diccionario junto a su significado.
                * PRE: La clave está definida.
                --PRODUCE ALIASING--
                **/
                void Borrar(const string& clave);


                /**
                CLAVES
                * Devuelve las claves del diccionario.
                --NO PRODUCE ALIASING--
                **/
                const Conj<string>& Claves() const;

        private:

                struct Nodo{
                    Nodo** siguientes;
                    T* definicion;
                    Nodo(){
						siguientes = new Nodo*[256];
                        for (int i = 0; i < 256; i++){
                            siguientes[i] = NULL;
                        }
                        definicion = NULL;
                    }
                    ~Nodo(){
                        delete definicion;
						            delete [] siguientes;
                    }
                };

                //TODO: funciones auxiliares

                bool vacio(){
                  if (raiz == NULL) {
                    return true;
                    }
                  else{
                    return false;
                    }
                  }

                void buscarNodos( Nodo* &padre, Nodo* &hijo, const string& clave, int &posicion){
                    //hijo es raiz padre es NULL

                  for (unsigned int i = 0; i < clave.size(); i++) {


                    if ((cantidadDeHijos(hijo) > 1) || !(hijo->definicion == NULL)) {
                        padre = hijo;
                        posicion = i;
                    }
                    hijo = hijo->siguientes[int(clave[i])];

                  }
                }


                void buscarPosicion(Nodo* &auxiliar, const string& clave){

                  for (unsigned int i = 0; i < clave.size(); i++) {

                    if (auxiliar->siguientes[int(clave[i])] == NULL) {
                      Nodo* puntero = new Nodo;
                      auxiliar->siguientes[int(clave[i])] = puntero;
                    }

                    auxiliar = auxiliar->siguientes[int(clave[i])];

                  }


                }
                int cantidadDeHijos(Nodo* hijo){

                  int valor = 0;
                  for (int i = 0; i < 256; i++) {
                    if (!(hijo->siguientes[i] == NULL)){
                      valor ++;
                    }
                  }
                  return valor;
                }

              bool tienehijos(Nodo* hijo){

                if (cantidadDeHijos(hijo) > 0) {
                  return true;
                }
                else{
                  return false;
                }
              }

              void borrarSinHijos(Nodo* &padre, Nodo* &hijo,const string& clave, int posicion){
                Nodo* auxiliar = padre->siguientes[int(clave[posicion])];
                padre->siguientes[int(clave[posicion])] = NULL;
                int i = posicion + 1;
                while (!(auxiliar == hijo)) {
                  Nodo* deleter = auxiliar;
                  auxiliar = auxiliar->siguientes[int(clave[i])];

                  deleter->siguientes[int(clave[i])] = NULL;
                  delete deleter;
                  i++;
                }
                if (auxiliar == hijo) {
                  delete hijo;
                }

              }

                Nodo* raiz;
                Conj<string> claves;
};


template <typename T>
DiccString<T>::DiccString()
    : raiz(NULL), claves(){
}


template <typename T>
DiccString<T>::DiccString(const DiccString& d) {
  Conj<string> nuevo = Conj<string>(d.Claves());
	Nodo* auxiliar = new Nodo();
	raiz = auxiliar;
	string palabra;
	T valor;
	while(nuevo.cardinal()>0){
		palabra = nuevo.minimo();
		valor = d.Obtener(palabra);
		Definir(palabra,valor);
		nuevo.remover(palabra);
	}
}

template <typename T>
DiccString<T>::~DiccString(){
  std::cout << "entre al destructor" << std::endl;
while (claves.cardinal() > 0) {
  Borrar(claves.minimo());
  std::cout << "sali del borrar dentro del destructor" << std::endl;
}
delete raiz;

}


template <typename T>
void DiccString<T>::Definir(const string& clave, const T& significado){


      if (vacio()) {
         Nodo* aux = new Nodo;
         raiz = aux;
      }
      Nodo* auxiliar = raiz;
      buscarPosicion(auxiliar,clave);
      if (auxiliar->definicion == NULL) {
        auxiliar->definicion = new T(significado);
      }
      else{
          delete auxiliar->definicion;
          auxiliar->definicion = NULL;
          auxiliar->definicion = new T(significado);
      }

      claves.insertar(clave);
}

        /* si yo quiero enviar un puntero del otro lado lo que tengo que hacer es
        desreferenciar desde el lado de la izquierda se hace con *(desreferenciar) = &(desreferenciar)
        ahora el problema es que si de un lado tengo no const  =   const no me va a compilar porque tengo que
        tener  dos cosas no const de un lado porque en cualquier momento podria modificar las cosas de un lado
        y mi otra funcion podria toquetearla y explotar todo, por lo tanto tengo que agarrar y llamar al constructor
        por copia por defecto del tipo T y ADEMAS tengo que crear un new (que me crea un espacio de memoria y me devuelve un puntero)
        por lo tanto puedo sacar el &(signficado) ya que no me hace falta enviar la direccion de donde esta el significado y ademàs puedo
        modificar crear y hacerle todo lo que quiera al puntero AHORA EL PROBLEMA ESTA que si yo tengo que eliminar el significado
        en algun otro momento de mi algoritmo, tengo que llamar al destructor por nodo o encargarme de detelet T(significado) o como sea que se
        escriba el significado ese*/





template <typename T>
bool DiccString<T>::Definido(const string& clave) const{
std::cout << "entre a definido" << std::endl;
std::cout << clave << std::endl;
  if (this->raiz == NULL) {
    return false;
  }

  unsigned int i = 0;
  Nodo* iterador = raiz;
  while (!(iterador->siguientes[int(clave[i])] == NULL)) {
    iterador = iterador->siguientes[int(clave[i])];
    i++;
}
  if (i < clave.size()) {

    return false;
  }
  if ((iterador->definicion == NULL)) {
    return false;
  }

  return true;

}


template <typename T>
T& DiccString<T>::Obtener(const string& clave) {

  Nodo* iterador = raiz;
  for (unsigned int i = 0; i < clave.size(); i++) {
  iterador = iterador->siguientes[int(clave[i])];
    }
  return *(iterador->definicion);


}


template <typename T>
const T& DiccString<T>::Obtener(const string& clave) const {
  Nodo* iterador = raiz;

for (unsigned int i = 0; i < clave.size(); i++) {
iterador = iterador->siguientes[int(clave[i])];
  }
  return *(iterador->definicion);
}


template <typename T>
const Conj<string>& DiccString<T>::Claves() const{
    return claves;
}


template <typename T>
void DiccString<T>::Borrar(const string& clave) {
// ejemplo de como usar assert
std::cout << clave << std::endl;
      assert(Definido(clave));
      std::cout << "pase el assert" << std::endl;
      Nodo* hijo = raiz;
      Nodo* padre = raiz;
      int posicion = 0;
      buscarNodos(padre,hijo,clave,posicion);
      delete hijo->definicion;
      hijo->definicion = NULL;
      if (!(tienehijos(hijo))) {
        borrarSinHijos(padre,hijo,clave,posicion);
        }
          claves.remover(clave);
}


#endif
