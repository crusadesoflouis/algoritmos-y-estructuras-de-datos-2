#include "Pila.h"
//constructor
  Pila::Pila(){prim = NULL; tam = 0;}
//destructor
Pila::~Pila(){
  while (!(this->tam == 0 )) {
  this->desapilar();
  }
}
void Pila::apilar(ElemPila& elemento){
  Nodo* puntero = new Nodo;
  puntero->elem = elemento;
  puntero->sig = this->prim;
  this->prim = puntero;
  this->tam ++;
}
bool Pila::esVacia(){
  if (this->tam == 0) {return true;}
      else {return false;}
}
ElemPila& Pila::tope(){
  return this->prim->elem;
}
void Pila::desapilar(){
  Nodo* auxiliar = this->prim;
  this->prim = this->prim->sig;
  delete auxiliar;
  this->tam --;
  }
Nat Pila::tamanio() const{
  return this->tam;
}
Pila& Pila::operator=(const Pila & aCopiar){
  while (!(this->esVacia())) {
    this->desapilar();
  }
  while (this->tam < aCopiar.tamanio()) {
    Nodo* auxiliar = aCopiar.prim;
    for (Nat i = 1; i < aCopiar.tamanio(); i++) {
      auxiliar = auxiliar->sig;
    }
    this->apilar(auxiliar->elem);
  }
      return (*this);
}
  void Pila::mostrar(ostream& os) const {
    Nodo* iterador = this->prim;
    os << "[";
    while (!(iterador == NULL)) {
      os << iterador->elem <<","<< endl; ;
      iterador = iterador->sig;
    }
    os << "]";
    }
