
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
		Lista<T> Elementos();
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

bool EsRaiz(Nodo* padre){
	return padre == raiz;
}
bool eshoja(Nodo* padre){
	return padre->der == NULL && padre->izq == NULL;
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

bool UltimoAgregado(Nodo* &encolado){
	Lista<bool> l;
	Nat tamanio = card;
	bool flag = false;
	to_binary(l,tamanio);
	Lista<bool>::const_Iterador IT = l.CrearIt();
	IT.Avanzar();
	while (IT.HaySiguiente()) {
		flag = IT.Siguiente();
		IT.Siguiente() ? encolado = encolado->der: encolado = encolado->izq;
		IT.Avanzar();
	}
	return flag;
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

void sift_UP_borrando(Nodo* &puntero){
	while (puntero != raiz && puntero->valor < puntero->padre->valor) {
		bool flag = HijoDerecho(puntero) ? true:false;
		cout << "yay"<< endl;
		swap(puntero,puntero->padre,flag);
	}
}
bool elMinimo(Nodo* puntero,Nodo* &minimo){
	bool flag = false;
	if (puntero->der != NULL && puntero->der != NULL) {
		if (puntero->der->valor < puntero->izq->valor) {
			minimo = puntero->der;
			flag = true;
		}
		else{
			minimo = puntero->izq;
			flag = false;
		}
	}
	//un else de mas pero no importa lo dejo asi por si las dudas
	else{
		minimo = puntero->izq;
		flag = false;
	}
	return flag;
}

void sift_DOWN(Nodo* puntero){
	Nodo* minimo = NULL;
	bool flag = elMinimo(puntero,minimo);
	while (!eshoja(puntero) && puntero->valor>minimo->valor) {
		swap(minimo,puntero,flag);
		puntero = minimo;
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
void deleteSwap(Nodo* A, Nodo* B){
	if (A == raiz) {
		raiz = B;
	}
	HijoDerecho(B) ? B->padre->der = NULL: B->padre->izq = NULL;
	B->padre = A->padre;
	if (B->padre != NULL) {
		HijoDerecho(B)? B->padre->der = B: B->padre->izq = B;
	}
	B->der = A->der;
	if (B->der != NULL)
		B->der->padre = B;
	B->izq = A->izq;
	if (B->izq != NULL)
		B->izq->padre = B;
		delete A;
}
void Remover(Nodo* Aborrar){
	//flag si es falso entonces ultimo es hijo izquierdo
	//flag si es verdadero entonces ultimo es hijo derecho
Nodo* ultimo = raiz;
if (card == 1) {
	raiz = NULL;
	delete Aborrar;
}
else{
		bool flag = false;
		flag = UltimoAgregado(ultimo);
		if (Aborrar == ultimo) {
		flag ? ultimo->padre->izq = NULL: ultimo->padre->der = NULL;
		delete Aborrar;
		}
		else{
			deleteSwap(Aborrar,ultimo);
		}
		sift_UP_borrando(ultimo);
		sift_DOWN(ultimo);
	}
	card--;

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

Lista<T> DameTodos(Nodo* nodulo,Lista<T> & elems){
	if (nodulo != NULL) {
		cout << "entre aca0" << endl;
		elems.AgregarAdelante(nodulo->valor);
		cout <<"sali"<< endl;
		if (nodulo->der != NULL) {
			cout << "no tuve que entrar aca 0"<< endl;
			DameTodos(nodulo->der,elems);
		}
		if (nodulo->izq != NULL) {
		cout << "no tuve que entrar aca 0"<< endl;
			DameTodos(nodulo->izq,elems);
		}
	}
	cout << " end" << endl;

}

	void mostrarNodo(Nodo* nodulo){
		if (!(nodulo == NULL)) {
			mostrarNodo(nodulo->izq);
			std::cout << nodulo->valor << " ";
			mostrarNodo(nodulo->der);
		}
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
	while (card != 0) {
		Remover(this->raiz);
	}
}

template <class T>
bool Cola<T>::esVacia() const{
return raiz == NULL;
}

template <class T>
Lista<T> Cola<T>::Elementos(){
	Lista<T> elems;
 	DameTodos(this->raiz, elems);
	cout << "ase rompe aca " << endl;
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
