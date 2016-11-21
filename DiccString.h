#ifndef DICCSTRING_H_INCLUDED
#define	DICCSTRING_H_INCLUDED

#include <iostream>
// #include "Dicc.h"

#include "aed2.h"
//#include "Conj.h"
//#include "TiposBasicos.h"
// #include "Registro.h"

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

    bool operator == (const DiccS<T>& otro) const;

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

    Nodo* raiz_;
    Conj<String> ConjClaves;

};

template<class T>
bool operator==(const DiccS<T>&, const DiccS<T>&);


template<class T>
DiccS<T>::DiccS(){
  Nodo* n = new Nodo();
  raiz_ = n;
}

template<class T>
DiccS<T>::DiccS(const DiccS<T>& otro){
  Nodo* n = new Nodo();
  raiz_ = n;
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
  String remove;
  while(it.HaySiguiente()){
    remove = it.Siguiente();
    it.Avanzar();
    Borrar(remove);
  }
  delete raiz_;
}

template<class T>
void DiccS<T>::Definir(const String k, const T& v){
  Nodo* tr = raiz_;
  for (unsigned int i = 0; i < k.length(); ++i){
    int s = (int)k[i];
    if (tr->chars[s] == NULL){
      tr->chars[s] = new Nodo();
    }
    tr = tr->chars[s];
  }
  T* x = new T(v);
  tr->val = x;
  tr->nombre = ConjClaves.AgregarRapido(k);
}

template<class T>
void DiccS<T>::Borrar(const String k){
  Nodo* tr = raiz_;
  for (unsigned int i=0; i < k.length(); ++i){
    tr = tr->chars[ (int)k[i] ];
  }
  tr->nombre.EliminarSiguiente();

  delete tr->val;
  tr->val = NULL;
  tr->nombre = Conj<String>::Iterador();

  int l = k.length();
  Nodo* padre;
  bool puedoBorrar = true;
  int j;
  while (l>0 && puedoBorrar){
    tr = raiz_;
    for (int i=0; i<l; ++i){
      padre = tr;
      tr = tr->chars[ (int)k[i] ];
    }
    j=0;
    if (tr->val == NULL){
      while (j<256 && tr->chars[j]==NULL){
        j++;
      }
    }
    puedoBorrar = j==256;
    if(puedoBorrar){
      padre->chars[(int)k[l-1]] = NULL;
      delete tr;
    }
    l--;
  }
}

template<class T>
bool DiccS<T>::Definido(const String k) const{
  int i = 0;
  int len = k.length();
  Nodo* tr = raiz_;
  while (i < len && tr->chars[(int)k[i]] != NULL){
    tr = tr->chars[ (int)k[i] ];
    i++;
  }
  return (i==len && tr->val!=NULL);
}

template<class T>
T& DiccS<T>::Significado(const String k) const{
  Nodo* tr = raiz_;
  for (unsigned int i = 0; i < k.length(); ++i){
    int s = (int)k[i];
    tr = tr->chars[ s ];
  }
  return *tr->val;
}

template<class T>
Conj<String>::const_Iterador DiccS<T>::ClavesDicc() const{
  return ConjClaves.CrearIt();
}

template<class T>
bool DiccS<T>::operator==(const DiccS<T>& otro) const {
  bool res = true;
  if (ConjClaves == otro.ConjClaves){
    Conj<String>::const_Iterador it = ClavesDicc();
    while (it.HaySiguiente() && res){
      res = Significado(it.Siguiente()) == otro.Significado(it.Siguiente());
      it.Avanzar();
    }
  } else{
    res = false;
  }
  return res;
}

#endif	//DICCSTRING_H_INCLUDED
