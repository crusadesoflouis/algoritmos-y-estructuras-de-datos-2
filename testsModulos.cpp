#include <iostream>
#include "mini_test.h"
#include "DiccString.h"
#include "DiccAbb.h"
#include "Cola.h"
#include "DiccMatriz.hpp"

void encolar_y_borrar() {
  Cola<int> c;
//  Cola<int>::Iterador IT_42 = c.Encolar(42);
//  Cola<int>::Iterador IT_40 = c.Encolar(40);
  Cola<int>::Iterador IT_51 = c.Encolar(51);
  Cola<int>::Iterador IT_3 = c.Encolar(3);
  c.mostrar();
  //IT_51.EliminarSiguiente();
  ASSERT_EQ(c.Cardinal(),2);
  ASSERT_EQ(c.Tope(),3);

}

void diccString(){
  DiccS<int> trie;
  String s = "casa";
  int x = 16;
  String k = "casablanca";
  int y = 22;
  String m = "lo";
  int z = 28;

  ASSERT_EQ(trie.Definido(s) , false);
  ASSERT_EQ( s.length(), 4);
  trie.Definir(k, y);
  trie.Definir(m, z);
  trie.Definir(s, x);
  trie.Borrar(m);
  ASSERT_EQ(trie.Significado(s) , 16);
  ASSERT_EQ(trie.Definido(s) , true);
  ASSERT_EQ(trie.Definido("pepe") , false);

  Conj<String>::const_Iterador it = trie.ClavesDicc();
  ASSERT_EQ( it.HaySiguiente() , true);
  it.Avanzar();


  DiccS<int> trie2 = DiccS<int>(trie);
  ASSERT_EQ(trie2.Definido(s) , true);
  ASSERT_EQ(trie2.Significado(s) , 16);
  ASSERT_EQ(trie2.Significado(k) , 22);
  ASSERT_EQ(trie == trie2 , true);

  trie.Borrar(s);
  ASSERT_EQ(trie.Definido(s) , false);
  ASSERT_EQ(trie == trie2 , false);
	//era necesario hacer el constructor por copia?
}

using namespace ::std;

void diccAbb(){
  DiccN<int> abb;
  int x = 16;
  int y = 22;
  int z = 28;
  ASSERT_EQ(abb.Definido(12) , false);
  abb.Definir(12, 16);
  abb.Definir(17, 22);
  abb.Definir(8, 28);
  abb.Definir(9, 12);
  ASSERT_EQ(abb.Definido(12) , true);
  ASSERT_EQ(abb.Definido(9) , true);
  abb.Borrar(9);
  ASSERT_EQ(abb.Definido(9) , false);
  //cout << abb.Significado(17) << endl;
  ASSERT_EQ(abb.Significado(17), y);
  ASSERT_EQ(abb.BuscarMin(), 8);
  ASSERT_EQ(abb.BuscarMax(), 17);

  DiccN<int> abb2;
  ASSERT_EQ(abb2.Definido(12) , false);
  abb2.Definir(12, x);
  abb2.Definir(17, y);
  abb2.Definir(8, z);
  abb2.Definir(9, x);
  ASSERT_EQ(abb2.Definido(12) , true);
  ASSERT_EQ(abb2.Definido(9) , true);
  abb2.Borrar(9);
  ASSERT_EQ(abb2.Definido(9) , false);
  ASSERT_EQ(abb2.Significado(17), y);
  ASSERT_EQ(abb2.BuscarMin(), 8);
  ASSERT_EQ(abb2.BuscarMax(), 17);

  ASSERT_EQ(abb == abb2, true);

  DiccN<int> abb3;
  DiccN<int> abb4  = DiccN<int>(abb3);
  ASSERT_EQ(abb3 == abb4, true);
}

void diccmatriz(){
  //inicializacion de datos
  DiccMatriz<int*> mat;
  int* a = NULL;
  int valor = 12;
  a = &valor;
  Coordenada c_1_1(1,1);
  Coordenada c_3_3(3,3);
  Coordenada c_3_1(3,1);
  Coordenada c_3_2(3,2);
  //fin inicializacion datos
  mat.Definir(c_1_1,a);
  mat.Definir(c_3_3,a);
//  mat.mostrar();
  mat.Definir(c_3_1,a);
  mat.mostrar();
  ASSERT_EQ(mat.Definido(c_3_1),true);
  ASSERT_EQ(mat.Definido(c_3_2),false);
  mat.Borrar(c_3_1);
  ASSERT_EQ(mat.Definido(c_3_1),false);
}

int main() {
  RUN_TEST(diccmatriz);
/*
	RUN_TEST(diccString);
  RUN_TEST(diccAbb);
  RUN_TEST(encolar_y_borrar);

*/
  return 0;
}
