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
