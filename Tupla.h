#include "aed2.h"
#include "TiposJuego.h"


template <class T>
class Tupla {

public:
  Tupla(T& otro, Nat Atrapados, Jugador ID);

  T& Iter();

  Nat Capturados() const;

  unsigned int Identificacion();

  bool operator< (Tupla<T>& t2) const;

private:
  T jugador;
  Jugador ID;
  Nat Atrapados;
};




template <class T>
 Tupla<T>::Tupla(T& A,Nat B,Jugador C): jugador(A),ID(C),Atrapados(B){
}
template <class T>
T&  Tupla<T>::Iter(){
  return jugador;
}

template <class T>
Nat  Tupla<T>::Capturados() const{
  return Atrapados;
}
template <class T>
unsigned int  Tupla<T>::Identificacion(){
  return ID;
}
template <class T>
bool Tupla<T>::operator< (Tupla<T>& t2) const {

  if (Atrapados == t2.Atrapados) {
    return ID < t2.Identificacion();
  }
  else{
    return Atrapados < t2.Capturados();
  }
}
