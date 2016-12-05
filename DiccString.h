#ifndef DICCSTRING_H_INCLUDED
#define	DICCSTRING_H_INCLUDED

#include <iostream>
#include "aed2.h"


using namespace aed2;

template<class T>
class DiccS
{
  public:

    DiccS();

    DiccS(const DiccS<T>& otro);

    ~DiccS();

    void Definir(const String k, const T& v);

    void Borrar(const String k);

    bool Definido(const String k) const;

    T& Significado(const String k) const;

    // typename Conj<T>::Iterador SignificadoR(String k);

    typename Conj<String>::const_Iterador ClavesDicc() const; // Devuelve iterador de conjunto

  private:

    struct Nodo{
      T* val;
      Conj<String>::Iterador nombre;
      Nodo* chars[256];

      Nodo(){
        val = NULL;
        nombre = Conj<String>::Iterador();
        for (int i = 0; i < 256; ++i){
          chars[i] = NULL;
        }
      };
    };

    Nodo* raiz;
    Conj<String> ConjClaves;

};

template<class T>
DiccS<T>::DiccS(){
  Nodo* n = new Nodo();
  raiz = n;
}

template<class T>
DiccS<T>::DiccS(const DiccS<T>& otro){
  Nodo* n = new Nodo();
  raiz = n;
  Conj<String>::const_Iterador it = otro.ClavesDicc();
  while (it.HaySiguiente()){
    String k = it.Siguiente();
    Definir(k, otro.Significado(k));
    it.Avanzar();
  }
}

template<class T>
DiccS<T>::~DiccS(){
  Conj<String>::const_Iterador it = ClavesDicc();
  String remover;
  while(it.HaySiguiente()){
    remover = it.Siguiente();
    it.Avanzar();
    Borrar(remover);
  }
  delete raiz;
}

template<class T>
void DiccS<T>::Definir(const String k, const T& v){
  Nodo* aux = raiz;
  for (unsigned int i = 0; i < k.length(); ++i){
    int s = (int)k[i];
    if (aux->chars[s] == NULL){
      aux->chars[s] = new Nodo();
    }
    aux = aux->chars[s];
  }
  T* x = new T(v);
  aux->val = x;
  aux->nombre = ConjClaves.AgregarRapido(k);
}

template<class T>
void DiccS<T>::Borrar(const String k){
  Nodo* aux = raiz;
  for (unsigned int i=0; i < k.length(); ++i){
    aux = aux->chars[ (int)k[i] ];
  }
  aux->nombre.EliminarSiguiente();

  delete aux->val;
  aux->val = NULL;
  aux->nombre = Conj<String>::Iterador();

  int l = k.length();
  Nodo* padre;
  bool puedoBorrar = true;
  int j;
  while (l>0 && puedoBorrar){
    aux = raiz;
    for (int i=0; i<l; ++i){
      padre = aux;
      aux = aux->chars[ (int)k[i] ];
    }
    j=0;
    if (aux->val == NULL){
      while (j<256 && aux->chars[j]==NULL){
        j++;
      }
    }
    puedoBorrar = j==256;
    if(puedoBorrar){
      padre->chars[(int)k[l-1]] = NULL;
      delete aux;
    }
    l--;
  }
}

template<class T>
bool DiccS<T>::Definido(const String k) const{
  int i = 0;
  int len = k.length();
  Nodo* aux = raiz;
  while (i < len && aux->chars[(int)k[i]] != NULL){
    aux = aux->chars[ (int)k[i] ];
    i++;
  }
  return (i==len && aux->val!=NULL);
}

template<class T>
T& DiccS<T>::Significado(const String k) const{
  Nodo* aux = raiz;
  for (unsigned int i = 0; i < k.length(); ++i){
    int s = (int)k[i];
    aux = aux->chars[ s ];
  }
  return *aux->val;
}

template<class T>
Conj<String>::const_Iterador DiccS<T>::ClavesDicc() const{
  return ConjClaves.CrearIt();
}


#endif	//DICCSTRING_H_INCLUDED
