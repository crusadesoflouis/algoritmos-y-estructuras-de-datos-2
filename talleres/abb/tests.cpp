#include <iostream>
#include "Conjunto.hpp"

#include "mini_test.h"


void si_no_lo_agrego_no_pertenece() {
  Conjunto<char> c;
  ASSERT( !c.pertenece('a') );
}


void insertar_inserta() {
  Conjunto<int> c;
  c.insertar(42);
  c.insertar(32);
  c.insertar(40);
  c.insertar(33);
	c.insertar(69);
	c.insertar(2058);
	c.insertar(-499);
  c.remover(42);
  c.remover(40);
  c.remover(33);
  c.mostrar();
  ASSERT_EQ( c.pertenece(42), false );
  ASSERT_EQ(c.maximo(),2058);
  ASSERT_EQ(c.minimo(),-499);
  ASSERT_EQ(c.cardinal(),4);


}

void test_remover() {
	// Chequear por lo menos los siguientes 3 casos:
 	// - Borrar una hoja
 	// - Borrar un nodo interno con un hijo
 	// - Borrrun nodo interno con dos hijos
 	Conjunto<int> c;
 	c.insertar(42);
 	c.insertar(44);
 	c.insertar(104);
 	c.insertar(450);
 	c.insertar(-46);
 	c.insertar(-460);
 	c.insertar(130);
 	c.insertar(43);
	}

void mostrar() {
  Conjunto<int> c;
  c.insertar(42);
  c.insertar(32);
  c.insertar(40);
  c.insertar(33);
  c.mostrar();
  c.pertenece(65);
}

void maximoyminimo(){
  Conjunto<int> c;
  c.insertar(42);
  c.insertar(32);
  c.insertar(40);
  c.insertar(33);
  c.insertar(489);
  c.insertar(35);
  c.insertar(349);
  c.insertar(-300);
  c.insertar(-420);
  c.insertar(5999);
  c.remover(40);
  c.mostrar();
  ASSERT_EQ(c.cardinal(),9);
}

void borrar(){
  Conjunto<int> c;
  c.insertar(12);
  c.insertar(20);
  c.insertar(1);
  c.insertar(599);

}

int main() {
    RUN_TEST(si_no_lo_agrego_no_pertenece);
    RUN_TEST(insertar_inserta);
    RUN_TEST(mostrar);
    RUN_TEST(maximoyminimo);
    RUN_TEST(test_remover);
    return 0;
}
