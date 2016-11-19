#ifndef DICCNAT_H_INCLUDED
#define	DICCNAT_H_INCLUDED

#include <iostream>
#include "aed2.h"

using namespace aed2;

template<class T>
class DiccN
{
  public:

    DiccN();

    DiccN(const DiccN<T>& otro);

    ~DiccN();

    void Definir(const Nat k, const T& v);

    void Borrar(const Nat k);

    bool Definido(const Nat k) const;

    T& Significado(const Nat k) const;

    Nat BuscarMin() const;

    Nat BuscarMax() const;

    bool operator == (const DiccN<T>& otro) const;

    typename Conj<Nat>::const_Iterador ClavesDicc() const;


  private:

    struct Nodo
    {
      T* signif;
      Nat clave;
      Nodo* izq;
      Nodo* der;
      Conj<Nat>::Iterador nat;
      Nodo(Nat n, const T& v): signif(new T(v)), izq(NULL), der(NULL), clave(n), nat(Conj<Nat>::Iterador()){}
      ~Nodo() { delete signif; }
    };

    Nodo* raiz;
    Nat cantidad;
    Conj<Nat> conjClaves;

    Lista<Nodo*> BFS() const{
      Lista<Nodo*> res = Lista<Nodo*>();
      if (raiz != NULL){
        Lista<Nodo*> bfs = Lista<Nodo*>();
        bfs.AgregarAtras(raiz);
        Nodo* prox;
        while ( !bfs.EsVacia() ){
          res.AgregarAtras(bfs.Primero());
          prox = bfs.Primero();
          bfs.Fin();
          if (prox->izq != NULL){
            bfs.AgregarAtras(prox->izq);
          }
          if (prox->der != NULL){
            bfs.AgregarAtras(prox->der);
          }
        }
      }
      return res;
    }

};

template<class T>
bool operator==(const DiccN<T>&, const DiccN<T>&);

  //  Implementacion de Conjunto

template<class T>
DiccN<T>::DiccN(){
  raiz = NULL;
  cantidad = 0;
}

template<class T>
DiccN<T>::DiccN(const DiccN<T>& otro){
  raiz = NULL;
  cantidad = 0;
  Lista<Nodo*> aCopiar = otro.BFS();
  while (!aCopiar.EsVacia()){
    T significadoACopiar = *aCopiar.Primero()->signif;
    Definir(aCopiar.Primero()->clave, significadoACopiar);
    aCopiar.Fin();
  }
}

template<class T>
DiccN<T>::~DiccN(){
  while(cantidad> 0){
    Borrar(raiz->clave);
  }
}

template<class T>
void DiccN<T>::Definir(const Nat k, const T& v){
  if (raiz == NULL){
    raiz = new Nodo(k, v);
    raiz->nat = conjClaves.AgregarRapido(k);
  }else{
    Nodo* sig = raiz;
    Nodo* padre;
    while (sig != NULL){
      padre = sig;
      if (k > sig->clave){
        sig = sig->der;
      }else{
        sig = sig->izq;
      }
    }
    sig = new Nodo(k, v);
    sig->nat = conjClaves.AgregarRapido(k);
    if (padre->clave < sig->clave){
      padre->der = sig;
    }else{
      padre->izq = sig;
    }
  }
  cantidad = cantidad + 1;
}

template<typename T>
void miswap(T& a, T& b)
{
  T tmp = a;
  a = b;
  b = tmp;
}

template<class T>
void DiccN<T>::Borrar(const Nat k){
  Nodo* sig = raiz;
  Nodo* padre;
  while (sig->clave != k){
    padre = sig;
    if (k < sig->clave){
      sig = sig->izq;
    }else{
      sig = sig->der;
    }
  }
  // caso 1 : sin hijos
  if (sig->izq==NULL && sig->der==NULL){
    if (sig==raiz){
      raiz =  NULL;
    }else if (k < padre->clave){
      padre->izq = NULL;
    }else{
      padre->der = NULL;
    }
  }
  // caso 2 : un hijo
  if (sig->izq==NULL && sig->der!=NULL){
    if (sig==raiz){
      raiz = sig->der;
    }else if (k < padre->clave){
      padre->izq = sig->der;
    }else{
      padre->der = sig->der;
    }
  }
  if (sig->izq!=NULL && sig->der==NULL){
    if (sig==raiz){
      raiz = sig->izq;
    }else if (k < padre->clave){
      padre->izq = sig->izq;
    }else{
      padre->der = sig->izq;
    }
  }
  // caso 3 : dos hijos
  if (sig->izq!=NULL && sig->der!=NULL){
    Nodo* swap = sig;
    padre = sig;
    sig = sig->der;
    while (sig->izq != NULL){
      padre = sig;
      sig = sig->izq;
    }
    miswap(swap->clave, sig->clave);
    miswap(swap->signif, sig->signif);
    miswap(swap->nat, sig->nat);
    padre->der = sig->der;
  }
  sig->nat.EliminarSiguiente();
  delete sig;
  cantidad = cantidad - 1;
}

template<class T>
bool DiccN<T>::Definido(const Nat k) const{
  Nodo* sig = raiz;
  while (sig != NULL && sig->clave != k){
    if (k > sig->clave){
      sig = sig->der;
    }else{
      sig = sig->izq;
    }
  }
  return sig != NULL;
}

template<class T>
T& DiccN<T>::Significado(const Nat k) const{
 Nodo* sig = raiz;
  while (sig->clave != k){
    if (k > sig->clave){
      sig = sig->der;
    }else{
      sig = sig->izq;
    }
  }
  return *sig->signif;
}

template<class T>
Nat DiccN<T>::BuscarMin() const{
  Nodo* buscador = raiz;
  while (buscador->izq != NULL){
    buscador = buscador->izq;
  }
  return buscador->clave;
}

template<class T>
Nat DiccN<T>::BuscarMax() const{
  Nodo* buscador = raiz;
  while (buscador->der != NULL){
  buscador = buscador->der;
  }
  return buscador->clave;
}

template<class T>
bool DiccN<T>::operator==(const DiccN<T>& otro) const {
  bool res = true;
  if (cantidad != otro.cantidad){
    res = false;
  }else{
    Lista<Nodo*> comp = otro.BFS();
    Nodo* prueba;
    while (!comp.EsVacia() && res){
      prueba = comp.Primero();
      comp.Fin();
      if (otro.Definido(prueba->clave)){
        T significadoAIgualar = *prueba->signif;
        res = significadoAIgualar == otro.Significado(prueba->clave);
      }
    }
  }
  return res;
}

template<class T>
Conj<Nat>::const_Iterador DiccN<T>::ClavesDicc() const{
  return conjClaves.CrearIt();
}



#endif	//AED2_CONJ_H_INCLUDED
