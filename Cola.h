
#ifndef CONJUNTO_HPP_
#define CONJUNTO_HPP_

#include <iostream>
#include <math.h>
#include "aed2.h"
using namespace std;

template <class T>
class Cola
{
	public:
		class Iterador;
		Cola();
		~Cola();
		bool esVacia() const;
	 	T Tope();
		typename Cola<T>::Iterador Encolar(const T);
		Nat Cardinal() const;
		void mostrar();
		Conj<T> Elementos();
		Iterador CrearIt();
		Iterador CrearIt(typename Cola<T>::Nodo* );

		class Iterador{
			public:
				Iterador();
				Iterador(Cola<T>* cola, typename Cola<T>::Nodo* proximo) : cola(cola),nodo_siguiente(proximo){};
				typename Cola<T>::Iterador& operator = (const typename Cola<T>::Iterador& otro);
			  bool HaySiguiente() const;
				T Siguiente() const;
		 		void EliminarSiguiente();
			private:
				friend typename Cola<T>::Iterador Cola<T>::CrearIt();
				friend typename Cola<T>::Iterador Cola<T>::CrearIt(typename Cola<T>::Nodo*);
				Cola<T>* cola;
				typename Cola<T>::Nodo* nodo_siguiente;
		};


		private:
		struct Nodo
		{
			Nodo(const T v);
			T valor;
			Nodo* izq;
			Nodo* der;
			Nodo* padre;
		};
		Nodo* raiz;
		Nat card;
//****************************Conversor a binario******************//
			 void to_binary(Lista<bool> &binary,Nat tam){
						while (tam > 1) {
							if (tam%2 == 0) {
								binary.AgregarAdelante(false);
							}
							else{
								binary.AgregarAdelante(true);
							}
							tam = tam/2;
						}
						if (tam == 0) {
								binary.AgregarAdelante(false);
						}
						else{
								binary.AgregarAdelante(true);
						}
			}
//***********************************************************///

//************************Funciones Auxiliares simples *******************//
bool SinHijos(Nodo* padre){
return padre->der == NULL && padre->izq == NULL;
}
bool TieneHijos(Nodo* padre){
	return !SinHijos(padre);
}

bool EsRaiz(Nodo* & padre){
	return padre == raiz;
}

bool HijoDerecho(Nodo* auxiliar){
return auxiliar->padre->der == auxiliar;
}

//*********************************************************************//
//**********************auxiliares del encolado del nodo***********************

void EncolarEnPosicion(Nodo* &encolado,const T clave){
	Lista<bool> l;
	Nat tamanio = card + 1;
	to_binary(l,tamanio);
	Lista<bool>::const_Iterador IT = l.CrearIt();
	//me creo la lista con el camino de insercion
	IT.Avanzar();
//avanzo porque la primera posicion se debe descartar
	bool flag = false;
	while(IT.HaySiguiente()){
		IT.Siguiente() ? flag = true: flag = false;
		IT.Avanzar();
		if (IT.HaySiguiente()) {
			flag ? encolado = encolado->der: encolado = encolado->izq;
		}
	}
	//tengo la posición en donde debo agregar y el puntero al padre
	if (flag) {
		encolado->der = new Nodo(clave);
		encolado->der->padre = encolado;
		encolado = encolado->der;
	}
	else{
		encolado->izq = new Nodo(clave);
		encolado->izq->padre = encolado;
		encolado = encolado->izq;
	}
}

void sift_UP(Nodo* &puntero){
	Lista<bool> l;
	Nat tamanio = card + 1;
	to_binary(l,tamanio);
	Lista<bool>::const_Iterador IT = l.CrearItUlt();
	Nat stop = l.Longitud();
	Nat cont = 1;
	while ((cont < stop)&&(puntero->valor < puntero->padre->valor)) {
		swap(puntero,puntero->padre,IT.Anterior());
		cont++;
		IT.Retroceder();
	}
}

void swap(Nodo* A, Nodo* B,bool flag){
	//flag si es falso entonces A es hijo izquierdo de B
	//flag si es verdadero entonces A es hijo derecho de B
	if (B == raiz){
		raiz = A;
	}
	Nodo* padre = NULL;
	Nodo* derecho = NULL;
	Nodo* izquierdo = NULL;

	padre = B->padre;
	derecho = B->der;
	izquierdo = B->izq;

	Nodo* auxiliarDer = A->der;
	Nodo* auxiliarIzq = A->izq;

 	A->padre = padre;

	if (padre != NULL) {
		HijoDerecho(B) ? A->padre->der = A: A->padre->izq = A;
	}
	B->padre = A;
	B->der = auxiliarDer;
	B->izq = auxiliarIzq;

	if (auxiliarDer != NULL) {
		auxiliarDer->padre = B;
	}
	if (auxiliarIzq != NULL) {
		auxiliarIzq->padre = B;
	}

	if (flag) {
		A->der = B;
		A->izq = izquierdo;
		if (izquierdo != NULL) {
			izquierdo->padre = A;
		}
	}
	else{
		A->izq = B;
		A->der = derecho;
		if (derecho != NULL) {
			derecho->padre = A;
		}
	}
}
//************************************************************************//

void Remover(Nodo* Aborrar){
/*
Nodo* ultimo = raiz;
	if (raiz == Aborrar) {
		raiz = NULL;
		delete Aborrar;
	}
	else{
		UltimoAgregado(ultimo);
		Aborrar->valor = ultimo->valor;
		HijoDerecho(ultimo) ? ultimo->padre->der = NULL:ultimo->padre->izq = NULL;
		delete ultimo;
		sift_UP(Aborrar);
		sift_DOWN(Aborrar);
	}
	card--;
	*/
}

	void Destruir(Nodo* nodulo){

	if (nodulo != NULL) {
		if (nodulo->der != NULL) {
			Destruir(nodulo->der);
		}
		if (nodulo->izq != NULL) {
			Destruir(nodulo->izq);
		}
	}
	delete nodulo;
}

Conj<T> DameTodos(Nodo* nodulo,Conj<T> & elems){
	if (nodulo != NULL) {
		elems.AgregarRapido();
		if (nodulo->der != NULL) {
			DameTodos(nodulo->der,elems);
		}
		if (nodulo->izq != NULL) {
			DameTodos(nodulo->izq,elems);
		}
	}

}

	void mostrarNodo(Nodo* nodulo){
		if (!(nodulo == NULL)) {
			mostrarNodo(nodulo->izq);
			std::cout << nodulo->valor << " ";
			mostrarNodo(nodulo->der);
		}
	}

void sift_DOWN(Nodo* &baja){
}


};
///////////////////////////////////////////class Iterador/////////////////////////////////
template <typename T>
Cola<T>::Iterador::Iterador()
	:cola(NULL), nodo_siguiente(NULL){
	}

template <typename T>
typename Cola<T>::Iterador& Cola<T>::Iterador::operator = (const Cola<T>::Iterador& otro){
	cola = otro.cola;
	nodo_siguiente = otro.nodo_siguiente;
	return *this;
}
template <typename T>
bool Cola<T>::Iterador::HaySiguiente() const{
	return nodo_siguiente != NULL;
}

template <typename T>
typename Cola<T>::Iterador Cola<T>::CrearIt() {
	return typename Cola<T>::Iterador::Iterador();
}

template <typename T>
typename Cola<T>::Iterador Cola<T>::CrearIt(typename Cola<T>::Nodo* auxiliar) {
	return typename Cola<T>::Iterador::Iterador(this,auxiliar);
}

template <typename T>
void Cola<T>::Iterador::EliminarSiguiente(){
	cola->Remover(nodo_siguiente);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
T Cola<T>::Tope(){
	return raiz->valor;
}

template <class T>
Cola<T>::Nodo::Nodo(const T v)
	 : valor(v), izq(NULL), der(NULL), padre(NULL){
}

template <class T>
Cola<T>::Cola() : raiz(NULL),card(0){
}

///////////////////////////////////////////////////////////////////////////////////
template <class T>
Cola<T>::~Cola(){
	//Destruir(this->raiz);
}

template <class T>
bool Cola<T>::esVacia() const{
return raiz == NULL;
}

template <class T>
Conj<T> Cola<T>::Elementos(){
	Conj<T> elems;
 	DameTodos(this->raiz, elems);
	return elems;
}

template <class T>
typename Cola<T>::Iterador Cola<T>::Encolar(const T clave){
	Cola<T>::Iterador IT;
	if (esVacia()) {
		Nodo* auxiliar = new Nodo(clave);
		auxiliar->valor = clave;
		raiz = auxiliar;
		IT = CrearIt(auxiliar);
	}
	else{
		Nodo* to_add = raiz;
		EncolarEnPosicion(to_add,clave);
		sift_UP(to_add);
		IT = CrearIt(to_add);
	}
	card++;
	return IT;

}

template <class T>
Nat Cola<T>::Cardinal() const{
return card;
}

template <class T>
void Cola<T>::mostrar() {
      mostrarNodo(this->raiz);
}
///////////////////////////////////////////////////////////////////////////////////////
/*
*/
#endif // CONJUNTO_HPP_
