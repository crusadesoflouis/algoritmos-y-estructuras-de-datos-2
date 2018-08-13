#ifndef CONJUNTO_HPP_
#define CONJUNTO_HPP_
#include <iostream>
#include <stack>
using namespace std;

template <class T>
class Conjunto
{
	public:
		// Constructor. Genera un conjunto vacío.
		Conjunto();
		// Destructor. Debe dejar limpia la memoria.
		~Conjunto();
		// Inserta un elemento en el conjunto. Si éste ya existe,
		// el conjunto no se modifica.
		void insertar(const T&);
		// Decide si un elemento pertenece al conjunto o no.
		bool pertenece(const T&) const;
		// borra un elemento del conjunto. Si éste no existe,
		// el conjunto no se modifica.
		void remover(const T&);
		// devuelve el mínimo elemento del conjunto según <.
		const T& minimo() const;
		// devuelve el máximo elemento del conjunto según <.
		const T& maximo() const;
		// devuelve la cantidad de elementos que tiene el conjunto.
		unsigned int cardinal() const;
		// muestra el conjunto.
		/*
		void mostrar(std::ostream&) const;
		friend ostream& operator<<(ostream& os, const Conjunto<T> &c) {
			c.mostrar(os);
			return os;
		}*/
		void mostrar();

	private:
		// la representación de un nodo interno.
		struct Nodo{
			// el constructor, toma el elemento al que representa el nodo.
			Nodo(const T& v);
			// el elemento al que representa el nodo.
			T valor;
			// puntero a la raíz del subárbol izq.
			Nodo* izq;
			// puntero a la raíz del subárbol der.
			Nodo* der;
		};
		// puntero a la raíz de nuestro árbol.
		Nodo* raiz;
		Nodo* min;
		Nodo* max;
		unsigned int card;
	// funciones auxiliares
	void mostrarNodo(Nodo* nodulo){
		if (!(nodulo == NULL)) {
			mostrarNodo(nodulo->izq);
			std::cout << nodulo->valor << " ";
			mostrarNodo(nodulo->der);
		}
	}
bool EsRaiz(Nodo* & padre){
	if (padre == NULL) {
		return true;
	}
	else{
		return true;
	}
}

void buscar (Nodo* &padre, Nodo* &hijo,const T& clave){
	hijo = this->raiz;
		while (!((hijo->der == NULL) && (hijo->izq == NULL))&& !(clave == hijo->valor)){
			padre = hijo;
			if (hijo->valor > clave) {
				hijo = hijo->izq;
			}
			else{
				hijo = hijo->der;
			}
		}
	}

	int hijos (const Nodo *nodulo){
	  int cantidadDeHijos = 0;
	  if (!(nodulo->der == NULL)){
	    cantidadDeHijos++;
	  }
	  if (!(nodulo->izq == NULL)){
	    cantidadDeHijos++;
	  }
	  return cantidadDeHijos;
	}

	void borrarSinHijos(Nodo* &padre, Nodo* &hijo){
		Nodo* auxiliar;
		auxiliar = hijo;
		if (padre->valor > auxiliar ->valor) {
			padre->izq = NULL;
		}
		else{
			padre->der = NULL;
			}
			delete auxiliar;
			hijo = NULL;
		}
		void dameHijo(Nodo* &hijo,Nodo* &puntero){


			if (hijo->der == NULL) {
				puntero = hijo->izq;
			}
			else{
				puntero = hijo->der;
			}
		}
		void damePredecesor(Nodo* &hijo, Nodo* &puntero,Nodo* &NuevoPadre){
			NuevoPadre = hijo->izq;
			puntero = hijo->izq;
					while (!(puntero->der == NULL)) {
						NuevoPadre = puntero;
						puntero = puntero->der;
					}
		}

		void borrarConUnHijo(Nodo* &padre,Nodo* &hijo){
			Nodo* auxiliar = NULL;
			dameHijo(hijo,auxiliar);
			if (padre->valor < hijo->valor) {
					padre->der = auxiliar;
				}
				else{
					padre->izq = auxiliar;
						}
			delete hijo;
			}

		void borrarConDosHijos(Nodo* &padre, Nodo* &hijo){
			Nodo* predecesor = NULL;
			Nodo* nuevopadre = NULL;
			damePredecesor(hijo,predecesor,nuevopadre);
					if (hijos(hijo->izq) == 0 ) {
							hijo->valor = hijo->izq->valor;
							Nodo* kill;
							kill = hijo->izq;
							hijo->izq = NULL;
							delete kill;
					}
					else{
						hijo->valor = predecesor->valor;
						borrarConUnHijo(nuevopadre,predecesor);
						}

			}


};

template <class T>
Conjunto<T>::Nodo::Nodo(const T& v)
	 : valor(v), izq(NULL), der(NULL)
{}

template <class T>
Conjunto<T>::Conjunto() : raiz(NULL)
{
	min = NULL;
	max = NULL;
	card = 0;
}



template <class T>
Conjunto<T>::~Conjunto()
{
	  while (!(this->card == 0)){
	    remover(this->raiz->valor);
		}
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const
{
	Nodo* puntero = this->raiz;
		while (!(puntero == NULL)){
				if(clave == puntero->valor) {
							return true;
				}
				else {
						if (clave > puntero->valor){
								puntero = puntero->der;
						}
						else{
								puntero = puntero->izq;
						}
				}

		}
		return false;

}

template <class T>
void Conjunto<T>::insertar(const T& clave)
{
	if (this->card == 0){
	  Nodo* nuevo = new Nodo(clave);
	  this->raiz = nuevo;
	}
	else{
	      Nodo* puntero = NULL;
	      Nodo* buscador = NULL;
	      puntero = this->raiz;
	      if (clave > puntero->valor) {
	          buscador = puntero->der;
	          while (!(buscador == NULL)) {
	              puntero = buscador;
	              if (clave > buscador->valor) {
	                  buscador = buscador->der;
	                }
	              else{
	                  buscador = buscador->izq;
	              }
	            }
	      }
	    else{
	        buscador = puntero->izq;
	        while (!(buscador == NULL)){
	            puntero = buscador;
	            if (clave > buscador->valor){
	              buscador = buscador->der;
	            }
	            else{
	              buscador = buscador->izq;
	            }
	        }
	    }
	    Nodo* nuevo = new Nodo(clave);
	    if (clave > puntero->valor) {
	      puntero->der = nuevo;
	    }
	    else{
	      puntero->izq = nuevo;
	    }
	  }
	    this->card++;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const
{
    return card;
}

template <class T>
void Conjunto<T>::remover(const T& clave){
	if (raiz->valor == clave) {
		if (hijos(raiz) == 0) {
			Nodo* auxiliar = NULL;
			auxiliar = raiz;
			raiz = NULL;
			delete auxiliar;
			}
		else{
				if (hijos(raiz) == 1) {
					Nodo* auxiliar = NULL;
					dameHijo(raiz,auxiliar);
					Nodo* swap = raiz;
					raiz = auxiliar;
					delete swap;
				}
				else{
						if (raiz->izq->der == NULL) {
								Nodo* auxiliar = raiz;
								raiz = auxiliar->izq;
								raiz->der = auxiliar->der;
								delete auxiliar;
							}
							else{
									Nodo* predecesor = NULL;
									Nodo* nuevopadre = NULL;
									damePredecesor(raiz,predecesor,nuevopadre);
									raiz->valor = predecesor->valor;
									borrarConUnHijo(nuevopadre,predecesor);
									}
						}
			}
	}
	// si no es el el valor de la raiz
	else{
		Nodo* padre = NULL;
		Nodo* hijo = NULL;
		buscar(padre,hijo,clave);
			if (hijos(hijo) == 0 ) {
				borrarSinHijos(padre,hijo);
			}
			else{
					if (hijos(hijo) == 1) {
						borrarConUnHijo(padre,hijo);
					}
					else{
						borrarConDosHijos(padre,hijo);
							}
			}
	}
			this->card --;
	}

template <class T>
const T&  Conjunto<T>::minimo() const{

	if(cardinal() == 1){
			return raiz->valor;
	} else {
			Nodo* auxiliar = raiz->izq;
			while(auxiliar->izq != NULL){
					auxiliar = auxiliar->izq;
			}
			return auxiliar->valor;
	}
}
template <class T>
const T&  Conjunto<T>::maximo() const{
	if(cardinal() == 1){
			return raiz->valor;
	} else {
			Nodo* auxiliar = raiz->der;
			while(auxiliar->der != NULL){
					auxiliar = auxiliar->der;
			}
			return auxiliar->valor;
	}
}
/*
template <class T>
void Conjunto<T>::mostrar(std::ostream& os) const {
	stack<Nodo*> pila;
	Nodo* next = raiz;
	do {
		if (next != NULL) {
			//os << next -> valor << " "; //preorder
			pila.push(next);
			next = next -> izq;
		} else {
			next = pila.top(); pila.pop();
			os << next -> valor << " "; //inorder
			next = next -> der;
		}
		// y postorder?? Se puede con este esquema?
	} while (!pila.empty() or next != NULL);
	os << endl;
}
*/
template <class T>
void Conjunto<T>::mostrar() {
      mostrarNodo(this->raiz);
}
#endif // CONJUNTO_HPP_
