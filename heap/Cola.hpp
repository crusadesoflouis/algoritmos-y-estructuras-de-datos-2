#ifndef CONJUNTO_HPP_
#define CONJUNTO_HPP_

#include <iostream>
#include <stack>
using namespace std;

template <class T>
class Cola
{
	public:

		// Constructor. Genera un heap vacio
		Cola();

		// Destructor. Debe dejar limpia la memoria.
		~Cola();

		// Inserta un elemento en el heap.
		void Encolar(const T&);

		// Decide si el arbol es vacio o no
		bool esVacia() const;

		// borra un elemento del conjunto.
		void remover(const T&);

		// devuelve la cantidad de elementos que tiene el arbol
		unsigned int cardinal() const;
		//funcion exclusivamente de muestra para ser testeado
		//no debe quedar publica luego de comprobar la correctitud del programa
		void mostrar();

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
	if (tamanio == ((2^altura) -1)) {
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
bool UnHijo(Nodo* padre){
	if ((padre->der != NULL && padre->izq == NULL)^(padre->der == NULL && padre->izq != NULL) ) {
		return true;
		}
	else{
		return false;
	}
}
void buscarModificable(Nodo* &busca,const T& valor){
//casos base del algoritmo
if (SinHijos(busca)) {
	busca->izq = new Nodo(valor);
	busca->tamIzq ++;
	busca->altura ++;
	}
else{
	if (UnHijo(busca)) {
	busca->tamDer++;
	busca->der = new Nodo(valor);
	}
	else{
			//en este momento, tenemos que decidir hacia donde seguir con el buscador
			//y llamarse asi mismo recursivamente
			if (completo(busca->tamDer,busca->altura-1) && completo(busca->tamIzq,busca->altura-1)) {
				busca->altura++;
				busca->tamIzq++;
				buscarModificable(busca->izq,valor);
			}
			else{
				if (completo(busca->tamIzq,busca->altura-1)) {
					busca->tamDer++;
					buscarModificable(busca->der,valor);
				}
			}
		}

	}


	//TODO
}

void sift_UP(Nodo* &sube){
	//TODO
}
void sift_DOWN(Nodo* &baja){
	//TODO
}

bool EsRaiz(Nodo* & padre){
	if (padre == NULL) {
		return true;
	}
	else{
		return false;
			}
	}
};


template <class T>
Cola<T>::Nodo::Nodo(const T& v)
	 : valor(v), izq(NULL), der(NULL), padre(NULL), altura(1),tamIzq(0),tamDer(0)
{

}

template <class T>
Cola<T>::Cola() : raiz(NULL){
}



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
void Cola<T>::Encolar(const T& clave){

	if (esVacia()) {
		Nodo* auxiliar = new Nodo(clave);
		auxiliar->valor = clave;
		raiz = auxiliar;
	}
	else{
		Nodo* busca = raiz;
		buscarModificable(busca,clave);
		sift_UP(busca);
	}
}

template <class T>
unsigned int Cola<T>::cardinal() const{
if (esVacia()) {
		return 0;
		}
	else{
		return raiz->tamDer + raiz->tamIzq +1;
	}
}

template <class T>
void Cola<T>::remover(const T& clave){
//TODO
}
template <class T>
void Cola<T>::mostrar() {
      mostrarNodo(this->raiz);
}

#endif // CONJUNTO_HPP_
