#ifndef DICCSTRING_H_INCLUDED
#define	DICCSTRING_H_INCLUDED

#include <iostream>
#include "DiccString.h"
#include "aed2.h"


using namespace aed2;

template<class T>
class MultiC
{
  public:

    MultiC();

    MultiC(const MultiC<T>& otro);

    ~MultiC();

    void Definir(const String k, const T& v);

    void Borrar(const String k);

    bool Definido(const String k) const;

    T& Significado(const String k) const;

    Nat Repeticiones(const String k) const;

    Nat Cardinal() const;

    typename Conj<String>::const_Iterador ClavesDicc() const; // Devuelve iterador de conjunto

  private:
    Nat cardinal;
    DiccS<T> trie;
};


template<class T>
MultiC<T>::MultiC():cardinal(0),trie(DiccS()){

}

template<class T>
MultiC<T>::MultiC(const MultiC<T>& otro){
  cardinal = otro.Cardinal();
  trie(otro);
}














#endif	//DICCSTRING_H_INCLUDED
