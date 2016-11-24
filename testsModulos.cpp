#include <iostream>
#include "mini_test.h"
#include "DiccString.h"
#include "Cola.h"
#include "DiccMatriz.h"
//#include "Multiconjunto.h"
using namespace ::std;

 

void encolar_y_borrar() {
  Cola<int> c;
//  Cola<int>::Iterador IT_42 = c.Encolar(42);
//  Cola<int>::Iterador IT_40 = c.Encolar(40);
  Cola<int>::Iterador IT_51 = c.Encolar(51);
  Cola<int>::Iterador IT_40 = c.Encolar(40);
  Cola<int>::Iterador IT_30 = c.Encolar(30);
  std::cout << "encolo 29" << std::endl;
  Cola<int>::Iterador IT_29 = c.Encolar(29);
//  Cola<int>::Iterador IT_28 = c.Encolar(28);
//  Cola<int>::Iterador IT_27 = c.Encolar(27);
//  Cola<int>::Iterador IT_26 = c.Encolar(26);
  c.mostrar();
  //IT_51.EliminarSiguiente();
  ASSERT_EQ(c.Cardinal(),4);
  ASSERT_EQ(c.Tope(),29);

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
  Coordenada c_7_2(7,2);
  ASSERT_EQ(mat.Vacio(),true);
  //fin inicializacion datos
  mat.Definir(c_1_1,a);
  ASSERT_EQ(mat.Vacio(),false);
  mat.Definir(c_3_3,a);
//  mat.mostrar();
  mat.Definir(c_3_1,a);
//  mat.mostrar();
  ASSERT_EQ(mat.Definido(c_3_1),true);
  ASSERT_EQ(mat.Definido(c_3_2),false);
  mat.Borrar(c_3_1);
  ASSERT_EQ(mat.Definido(c_3_1),false);
  ASSERT_EQ(mat.Obtener(c_1_1),a);
  mat.Definir(c_7_2,a);
  ASSERT_EQ(mat.Obtener(c_7_2),a);
}

int main() {

  RUN_TEST(diccmatriz);
	RUN_TEST(diccString);
  RUN_TEST(encolar_y_borrar);


  return 0;
}
