#include <iostream>
#include "MultiC.h"
#include "mini_test.h"
using namespace ::std;

void defvacia(){
  MultiC c;
  ASSERT_EQ(c.Vacia(),true);
}
/*
void agregar4elementosDistintos(){
  MultiC c;
  c.Agregar("mimamamemima");
  c.Agregar("casonacasasona");
  c.Agregar("tarararahey");
  c.Agregar("hola");
  ASSERT_EQ(c.Vacia(),false);
  ASSERT_EQ(c.Definido("hola"),true);
  ASSERT_EQ(c.Definido("mordor"),false);
  ASSERT_EQ(c.Cardinal(),4);
  ASSERT_EQ(c.Repeticiones("mimamamemima"),1);
}

void agregar3veceselmismo() {
  MultiC c;
  c.Agregar("hola");
  c.Agregar("hola");
  c.Agregar("hola");
  ASSERT_EQ(c.Vacia(),false);
  ASSERT_EQ(c.Cardinal(),1);
  ASSERT_EQ(c.Repeticiones("hola"),3);
}
*/
int main() {
  RUN_TEST(defvacia);
//  RUN_TEST(agregar4elementosDistintos);
//  RUN_TEST(agregar3veceselmismo);
  return 0;
};
