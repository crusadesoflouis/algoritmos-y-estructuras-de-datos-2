#include <iostream>
#include "mini_test.h"
//#include "DiccString.h"
//#include "Cola.h"
#include "DiccMatriz.h"
//#include "Multiconjunto.h"
using namespace ::std;


/*
void encolar_y_borrar() {
  Cola<int> c;
  Cola<int>::Iterador IT_42 = c.Encolar(42);
  Cola<int>::Iterador IT_40 = c.Encolar(40);
  ASSERT_EQ(c.Cardinal(),2);
  ASSERT_EQ(c.Tope(),40);
  Cola<int>::Iterador IT_51 = c.Encolar(51);
  ASSERT_EQ(c.Cardinal(),3);
  ASSERT_EQ(c.Tope(),40);
  Cola<int>::Iterador IT_30 = c.Encolar(30);
  ASSERT_EQ(c.Cardinal(),4);
  ASSERT_EQ(c.Tope(),30);
  Cola<int>::Iterador IT_29 = c.Encolar(29);
  ASSERT_EQ(c.Cardinal(),5);
  ASSERT_EQ(c.Tope(),29);
  Cola<int>::Iterador IT_28 = c.Encolar(28);
  ASSERT_EQ(c.Cardinal(),6);
  ASSERT_EQ(c.Tope(),28);
  Cola<int>::Iterador IT_27 = c.Encolar(27);
  ASSERT_EQ(c.Cardinal(),7);
  ASSERT_EQ(c.Tope(),27);
  Cola<int>::Iterador IT_26 = c.Encolar(26);
  ASSERT_EQ(c.Tope(),26);
  Cola<int>::Iterador IT_10 = c.Encolar(10);
  ASSERT_EQ(c.Cardinal(),9);
  ASSERT_EQ(c.Tope(),10);
  IT_10.EliminarSiguiente();
  ASSERT_EQ(c.Cardinal(),8);
  ASSERT_EQ(c.Tope(),26);
  IT_51.EliminarSiguiente();
  ASSERT_EQ(c.Cardinal(),7);
  ASSERT_EQ(c.Tope(),26);
}
*/
/*
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
*/

void diccmatriz(){
  //inicializacion de datos
  DiccMatriz<int*> mat;
  int* a = NULL;
  int valor = 12;
  a = &valor;
  Coordenada c_0_0(0,0);
  Coordenada c_1_1(1,1);
  Coordenada c_3_3(3,3);
  Coordenada c_3_1(3,1);
  Coordenada c_3_2(3,2);
  Coordenada c_7_2(7,2);
  Coordenada c_2_2(2,2);
  Coordenada c_4_4(4,4);
  Coordenada c_9_9(9,9);
  Coordenada c_10_10(10,10);
  ASSERT_EQ(mat.Vacio(),true);


  mat.Definir(c_4_4,a);
  mat.Definir(c_0_0,a);
  mat.mostrar();
  ASSERT_EQ(mat.Definido(c_4_4),true);
  ASSERT_EQ(mat.Definido(c_0_0),true);
  /*
  mat.Definir(c_2_2,a);
  mat.Definir(c_3_3,a);
  mat.Definir(c_9_9,a);
  mat.Definir(c_10_10,a);

  ASSERT_EQ(mat.Definido(c_1_1),true);
  ASSERT_EQ(mat.Definido(c_3_3),true);
  ASSERT_EQ(mat.Definido(c_2_2),true);
  ASSERT_EQ(mat.Definido(c_9_9),true);
  ASSERT_EQ(mat.Definido(c_10_10),true);
*/
  //fin inicializacion datos
/*
  mat.Definir(c_2_2,a);
  mat.mostrar();
  mat.Definir(c_1_1,a);
  ASSERT_EQ(mat.Vacio(),false);
  mat.Definir(c_3_3,a);
  mat.Definir(c_3_1,a);
  mat.mostrar();
  ASSERT_EQ(mat.Definido(c_3_1),true);
  ASSERT_EQ(mat.Definido(c_3_2),false);
  mat.Borrar(c_3_1);
  ASSERT_EQ(mat.Definido(c_3_1),false);
  ASSERT_EQ(mat.Obtener(c_1_1),a);
  mat.Definir(c_7_2,a);
  ASSERT_EQ(mat.Obtener(c_7_2),a);
  ASSERT_EQ(mat.Definido(c_0_0),false);
  mat.Definir(c_0_0,a);
  ASSERT_EQ(mat.Definido(c_0_0),true);

  */
}

void diccmatriz_2(){
  //inicializacion de datos
  DiccMatriz<bool> mat;
  Coordenada c_0_0(0,0);
  Coordenada c_1_1(1,1);
  Coordenada c_3_3(3,3);
  Coordenada c_3_1(3,1);
  Coordenada c_3_2(3,2);
  Coordenada c_7_2(7,2);
  Coordenada c_2_2(2,2);
  Coordenada c_4_4(4,4);
  Coordenada c_9_9(9,9);
  Coordenada c_10_10(10,10);
  ASSERT_EQ(mat.Vacio(),true);

  mat.Definir(c_0_0,true);
  mat.Definir(c_4_4,true);
  mat.mostrar();
  ASSERT_EQ(mat.Definido(c_4_4),true);
  ASSERT_EQ(mat.Definido(c_0_0),true);

}





int main() {

//  RUN_TEST(diccmatriz);
  RUN_TEST(diccmatriz_2);
//	RUN_TEST(diccString);
//  RUN_TEST(encolar_y_borrar);


  return 0;
}
