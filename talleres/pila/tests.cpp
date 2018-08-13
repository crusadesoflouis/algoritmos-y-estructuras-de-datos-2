#include "Pila.h"
#include "mini_test.h"

// para compilar:$ g++ -g tests.cpp Pila.cpp -o Pila
// para ejecutar con valgrind:$ valgrind --leak-check=full -v ./Pila

void test_vacia() {
  Pila p;
  ASSERT_EQ(p.tamanio(), 0);
}

void test_apilar() {
  Pila p;
  ElemPila asd;
  ElemPila dsa;
  p.apilar(asd);
  p.apilar(dsa);
  ASSERT_EQ(p.tamanio(),2);
  ASSERT_EQ(p.esVacia(),false);
}

void test_desapilar() {
  Pila p;
  ElemPila asd;
  ElemPila dsa;
  p.apilar(asd);
  p.apilar(dsa);
  p.desapilar();
  p.desapilar();
  p.apilar(dsa);
  p.desapilar();
  ASSERT_EQ(p.tamanio(),0);
  ASSERT_EQ(p.esVacia(),true);

}

void test_asignacion() {
  Pila p;
  ElemPila asd;
  ElemPila dsa;
  p.apilar(asd);
  p.apilar(dsa);
  Pila q;
  ElemPila fdj;
  q.apilar(fdj);
  p = q;
  ASSERT_EQ(p.tamanio(),1);
  ASSERT_EQ(p.esVacia(),false);
  ASSERT_EQ(q.tamanio(),1)
  ASSERT_EQ(q.esVacia(),false)
}
void test_mostrar(){
  Pila p;
  ElemPila asd;
  asd.id = 1;
  asd.nombre = "luis";
  asd.descripcion = "arroyo";
  ElemPila dsa;
  dsa.id = 2;
  dsa.nombre = "evelyn";
  dsa.descripcion = "ferrero";
  ElemPila tumama;
  tumama.id = 3;
  tumama.nombre = "emiliana";
  tumama.descripcion = "castez";
//  ostream os;
  p.apilar(asd);
  p.apilar(dsa);
  p.apilar(tumama);
  //p.mostrar(os);
  cout << p;
}

int main() {
  RUN_TEST(test_vacia);
  RUN_TEST(test_apilar);
  RUN_TEST(test_desapilar);
  RUN_TEST(test_asignacion);
  RUN_TEST(test_mostrar);

  return 0;
}
