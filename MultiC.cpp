#include "MultiC.h"
//inicializacion


  MultiC::MultiC() {
    cardinalidad = 0;
    DiccS<Nat> trie;
  }
  MultiC::~MultiC(){
  }

void MultiC::Agregar(const String k){
  if (trie.Definido(k)) {
    Nat Valor = trie.Significado(k) +1;
    trie.Borrar(k);
    trie.Definir(k,Valor);
  }
  else{
    Nat a = 1;
    trie.Definir(k,a);
    cardinalidad ++;
  }

}

void MultiC::Eliminar(const String k){
  if (trie.Significado(k) == 1) {
    trie.Borrar(k);
  }
  else{
    Nat Valor = trie.Significado(k) -1;
    trie.Borrar(k);
    trie.Definir(k,Valor);
  }
}

bool MultiC::Definido(const String k){
  return trie.Definido(k);
}

Nat MultiC::Repeticiones(const String k)const{
  return trie.Significado(k);
}

Nat MultiC::Cardinal()const {
  return cardinalidad;
}

bool MultiC::Vacia(){
  return cardinalidad == 0;
}

Conj<String>::const_Iterador MultiC::CrearIt()const{
  return trie.ClavesDicc();
}
