#ifndef CONJUNTO_HPP_
#define CONJUNTO_HPP_

#include <iostream>
#include <stack>
#include<math.h>
using namespace std;

template <class T>
class Cola
{
	public:
		class Iterador;
		// Constructor. Genera un heap vacio
		Cola();
		// Destructor. Debe dejar limpia la memoria.
		~Cola();
		// Inserta un elemento en el heap.
		typename Cola<T>::Iterador Encolar(const T&);
		// Decide si el arbol es vacio o no
		bool esVacia() const;
		// borra un elemento del conjunto.
		void Remover(typename Cola<T>::Iterador);
	 	const T& Tope();
		// devuelve la cantidad de elementos que tiene el arbol
		unsigned int Cardinal() const;
		//funcion exclusivamente de muestra para ser testeado
		//no debe quedar publica luego de comprobar la correctitud del programa
		void mostrar();

		class Iterador{
			public:
			  bool HaySiguiente() const;
				T& Siguiente() const;
			private:
	 void EliminarSiguiente();
				Iterador();
				Iterador(typename Cola<T>::Nodo* _proximo) : nodo_siguiente(_proximo) {};
				friend typename Cola<T>::Iterador Cola<T>::Encolar(const T&);
				//friend typename Cola<T>::Iterador void Cola<T>::Remover(typename Cola<T>::Iterador);
				friend typename Cola<T>::Iterador::EliminarSiguiente Cola<T>::Remover(typename Cola<T>::Iterador);
				typename Cola<T>::Nodo* nodo_siguiente;
		};


		private:

		// la representación de un nodo interno.
		struct Nodo
		{
			// el constructor, toma el elemento al que representa el nodo.
			Nodo(const T& v);
			// el elemento al que representa el nodo.
			T valor;
			// puntero a la raíz del subárbol izq.
			Nodo* izq;
			// puntero a la raíz del subárbol der.
			Nodo* der;
			Nodo* padre;
			int altura;
			int tamIzq;
			int tamDer;
		};

		// puntero a la raíz de nuestro árbol.
		Nodo* raiz;
	// funciones auxiliares
	void mostrarNodo(Nodo* nodulo){
		if (!(nodulo == NULL)) {
			mostrarNodo(nodulo->izq);
			std::cout << nodulo->valor << " ";
			mostrarNodo(nodulo->der);
		}
	}

bool completo( int tamanio, int altura){
	if (tamanio == (pow(2,altura)-1)) {
		return true;
	}
	else{
		return false;
	}
}
bool SinHijos(Nodo* padre){
	if (padre->der == NULL && padre->izq == NULL) {
		return true;
		}
	else{
		return false;
	}
}
bool TieneHijos(Nodo* padre){
	return !SinHijos(padre);
}
bool UnHijo(Nodo* padre){
	if ((padre->der != NULL && padre->izq == NULL)^(padre->der == NULL && padre->izq != NULL) ) {
		return true;
		}
	else{
		return false;
	}
}
bool HijosConPrioridad(Nodo* padre){

	return padre->izq->valor < padre->valor || padre->der->valor < padre->valor;

}

void elMinimoDeLosTres(Nodo* padre,Nodo* minimo){
	padre->izq->valor < padre->der->valor ? minimo = padre->izq: minimo = padre->der;

	if (padre->valor <minimo->valor) {
		minimo = padre;
	}
}


void buscarModificable(Nodo* &busca,const T& valor){
//casos base del algoritmo
if (SinHijos(busca)) {
	busca->izq = new Nodo(valor);
	busca->izq->padre = busca;
	busca->tamIzq ++;
	busca->altura ++;
	busca = busca->izq;
	}
else{

	if (UnHijo(busca)) {
	busca->tamDer++;
	busca->der = new Nodo(valor);
	busca->der->padre = busca;
	busca = busca->der;
	}
	else{
			//en este momento, tenemos que decidir hacia donde seguir con el buscador
			//y llamarse asi mismo recursivamente

			int alt = busca->altura -1;
			if (completo(busca->tamDer,alt) && completo(busca->tamIzq,alt)) {
				busca->altura++;
				busca->tamIzq++;
				busca= busca->izq;
				buscarModificable(busca,valor);
			}
			else{
				if (completo(busca->tamIzq,alt)) {
					busca->tamDer++;
					busca = busca->der;
					buscarModificable(busca,valor);
				}
				else{
					busca->tamIzq++;
					busca = busca->izq;
					buscarModificable(busca,valor);
				}
			}
		}

	}

}

void sift_UP(Nodo* &sube){
	while (sube->padre != NULL && sube->valor < sube->padre->valor) {
		T swap = sube->padre->valor;
		sube->padre->valor = sube->valor;
		sube->valor = swap;
		sube = sube->padre;

	}

}
void sift_DOWN(Nodo* &baja){
	while (TieneHijos(baja)&&HijosConPrioridad(baja)) {
		Nodo* minimo = NULL;
		elMinimoDeLosTres(baja,minimo);
		if (baja->der < minimo) {
			T swap = baja->valor;
			baja->valor = baja->der->valor;
			baja->der->valor = swap;
			baja= baja->der;
		}
		else{
			T swap = baja->valor;
			baja->valor = baja->izq->valor;
			baja->izq->valor = swap;
			baja = baja->izq;
		}
	}
}

bool EsRaiz(Nodo* & padre){
	if (padre == NULL) {
		return true;
	}
	else{
		return false;
			}
	}


	//funciones auxiliares de Borrar

	void UltimoAgregado(Nodo* ultimo){
		if (TieneHijos(ultimo)) {
			//si tiene exactamente un hijo
			if (UnHijo(ultimo)) {
				ultimo = ultimo->izq;
			}
			//entonces tiene dos hijos
			else{
				int alt = ultimo->altura -1; //ahorro de escritura

				if (completo(ultimo->tamDer,alt)&&completo(ultimo->tamIzq,alt)) {
					//en el caso de que este completo de ambos lados, tengo que avanzar hacia la derecha
					UltimoAgregado(ultimo->der);
				}
				else{
						//si los dos no estan completos puede ser que este uno completo y el otro no, o que ninguno/
						//de los dos este completo

						//en el caso de que el de la izquierda este completo y a la derecha no tenga absolutamente nada
					if (completo(ultimo->tamIzq,alt)&&completo(ultimo->tamDer,alt-1)) {
						UltimoAgregado(ultimo->izq);
					}
					else{
						UltimoAgregado(ultimo->der);
					}

				}
			}
		}
		//como no tiene hijos el nodo es el que queria, el ultimo agregado
	}
	void reconstruir(Nodo* armando){
		if (TieneHermano(armando)) {
			armando->padre->tamDer--;
		}
		else{
			armando = armando->padre;
			armando->altura--;
			armando->tamIzq--;
			while (!SoyHijoDerecho(armando)) {
				armando->tamIzq--;
				armando->altura--;
				armando = armando->padre;
				}
			}
		}
	bool TieneHermano(Nodo* hijo){
		return (hijo->padre->der != NULL)&&(hijo->padre->izq);
	}

	bool SoyHijoDerecho(Nodo* ultimo){
	return ultimo->padre->der == ultimo;
	}



};



template <class T>
const T& Cola<T>::Tope(){
	return raiz->valor;
}

template <class T>
Cola<T>::Nodo::Nodo(const T& v)
	 : valor(v), izq(NULL), der(NULL), padre(NULL), altura(1),tamIzq(0),tamDer(0){
}

template <class T>
Cola<T>::Cola() : raiz(NULL){
}


///////////////////////////////////////////////////////////////////////////////////
template <class T>
Cola<T>::~Cola()
{
//TODO
}

template <class T>
bool Cola<T>::esVacia() const{
	if (raiz == NULL) {
		return true;
	}
	else{
		return false;
	}
}

template <class T>
typename Cola<T>::Iterador Cola<T>::Encolar(const T& clave){

	if (esVacia()) {
		Nodo* auxiliar = new Nodo(clave);
		auxiliar->valor = clave;
		raiz = auxiliar;
		Cola<T>::Iterador IT(auxiliar);
		return IT;
	}
	else{
		Nodo* busca = raiz;
		buscarModificable(busca,clave);
		sift_UP(busca);
		Cola<T>::Iterador IT(busca);
		return IT;
	}
}

template <class T>
unsigned int Cola<T>::Cardinal() const{
if (esVacia()) {
		return 0;
		}
	else{
		return raiz->tamDer + raiz->tamIzq +1;
	}
}

template <class T>
void Cola<T>::mostrar() {
      mostrarNodo(this->raiz);
}
///////////////////////////////////////////////////////////////////////////////////////
template <class T>
void Cola<T>::Remover(typename Cola<T>::Iterador IT){

IT.EliminarSiguiente();
}




//class Iterador

template <typename T>
Cola<T>::Iterador::Iterador()
	:nodo_siguiente(NULL){
	}

template <typename T>
bool Cola<T>::Iterador::HaySiguiente() const{
	return nodo_siguiente != NULL;
}

template <typename T>
void Cola<T>::Iterador::EliminarSiguiente(){
Nodo* Aborrar = nodo_siguiente;
Nodo* ultimo = raiz;
cout << ultimo->valor << endl;
if (raiz = Aborrar) {
	raiz = NULL;
	delete Aborrar;
}
else{
	UltimoAgregado(ultimo);
	Aborrar->valor = ultimo->valor;
	SoyHijoDerecho(ultimo) ? ultimo->padre->der = NULL:ultimo->padre->izq = NULL;
	reconstruir(ultimo);
	delete ultimo;
	sift_UP(Aborrar);
	sift_DOWN(Aborrar);
	}
}



/*
*/
#endif // CONJUNTO_HPP_
