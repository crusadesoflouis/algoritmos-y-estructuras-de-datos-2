#include <iostream>
#include "Cola.hpp"

#include "mini_test.h"



void encolar_inserta() {
  Cola<int> c;
  c.Encolar(42);
  c.Encolar(32);
  c.Encolar(40);
  c.Encolar(33);
	c.Encolar(69);
	c.Encolar(2058);
	c.Encolar(-499);
  c.remover(42);
  c.remover(40);
  c.remover(33);
  c.mostrar();
  ASSERT_EQ(c.cardinal(),4);


}
/*
void test_remover() {
	// Chequear por lo menos los siguientes 3 casos:
 	// - Borrar una hoja
 	// - Borrar un nodo interno con un hijo
 	// - Borrrun nodo interno con dos hijos
 	Cola<int> c;
 	c.Encolar(42);
 	c.Encolar(44);
 	c.Encolar(104);
 	c.Encolar(450);
 	c.Encolar(-46);
 	c.Encolar(-460);
 	c.Encolar(130);
 	c.Encolar(43);
	}
*/
void mostrar() {
  Cola<int> c;
  c.Encolar(42);
  c.Encolar(32);
  c.Encolar(40);
  c.Encolar(33);
  c.mostrar();
}

void maximoyminimo(){
  Cola<int> c;
  c.Encolar(42);
  c.Encolar(32);
  c.Encolar(40);
  c.Encolar(33);
  c.Encolar(489);
  c.Encolar(35);
  c.Encolar(349);
  c.Encolar(-300);
  c.Encolar(-420);
  c.Encolar(5999);
  c.remover(40);
  c.mostrar();
  ASSERT_EQ(c.cardinal(),9);
}

void borrar(){
  Cola<int> c;
  c.Encolar(12);
  c.Encolar(20);
  c.Encolar(1);
  c.Encolar(599);

}

int main() {
  /*
    RUN_TEST(si_no_lo_agrego_no_pertenece);
    RUN_TEST(encolar_inserta);
    RUN_TEST(mostrar);
  RUN_TEST(maximoyminimo);
  */
    return 0;
}
