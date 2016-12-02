#include <iostream>
#include "aed2.h"
#include "mini_test.h"
#include "coordenada.h"
#include "DiccMatriz.h"
#include "TiposJuego.h"
using namespace ::std;


void diccmatriz(){
  //inicializacion de datos
  DiccMatriz<int*> mat;
  int* a = NULL;
  int valor = 12;
  a = &valor;
  coordenada c_1_1(1,1);
  coordenada c_3_3(3,3);
  coordenada c_3_1(3,1);
  coordenada c_3_2(3,2);
  coordenada c_7_2(7,2);
  ASSERT_EQ(mat.Vacio(),true);
  //fin inicializacion datos
  ASSERT_EQ(mat.Latitud(),0);
  ASSERT_EQ(mat.Longitud(),0);
  mat.Definir(c_1_1,a);
  ASSERT_EQ(mat.Latitud(),1);
  ASSERT_EQ(mat.Longitud(),1);
  ASSERT_EQ(mat.Vacio(),false);
  ASSERT_EQ(mat.Definido(c_1_1),true);
  ASSERT_EQ(mat.Definido(c_7_2),false);
  mat.Definir(c_3_3,a);
  ASSERT_EQ(mat.Definido(c_3_3),true);
  ASSERT_EQ(mat.Obtener(c_3_3),a);
  ASSERT_EQ(mat.Latitud(),3);
  ASSERT_EQ(mat.Longitud(),3);
//  mat.mostrar();
//  mat.Definir(c_3_1,a);
//  mat.mostrar();
//  ASSERT_EQ(mat.Definido(c_3_1),true);
  //ASSERT_EQ(mat.Definido(c_3_2),false);
//  mat.Borrar(c_3_1);
//  ASSERT_EQ(mat.Definido(c_3_1),false);
//  ASSERT_EQ(mat.Obtener(c_1_1),a);
//  mat.Definir(c_7_2,a);
//  ASSERT_EQ(mat.Obtener(c_7_2),a);
}

int main() {
  RUN_TEST(diccmatriz);
  return 0;
}
