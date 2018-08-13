#include <iostream>
#include "mini_test.h"

#include "DiccString.hpp"


//Chequea que el diccionario vacio no tenga claves

void test_claves_dicc_vacio() {
	DiccString<int> d;
	ASSERT(d.Claves().cardinal() == 0);
}


//Chequea el definir y definido
void test_definir_definido() {
	DiccString<int> d;
	d.Definir("hola",42);
	ASSERT( d.Definido("hola") );
	ASSERT( !d.Definido("casona") );
 	ASSERT( !d.Definido("casa") );

	d.Definir("casona",13);
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("casona") );
  	ASSERT( !d.Definido("casa") );

  	d.Definir("casa",6);
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("casona") );
  	ASSERT( d.Definido("casa") );
}



//cheque el obtener
void test_obtener() {
	DiccString<int> d;
	d.Definir("hola",42);
	d.Definir("casa",22);

	ASSERT( d.Obtener("hola") == 42 );
	ASSERT( d.Obtener("casa") == 22 );

}



//cheque el borrar
void test_borrar() {
	//Completar este test para:
	//Verificar que al borrar una palabra, esta deja de estar definida en el diccionario
	//Chequear que si dos palabras comparten prefijos y una de ellas se borrar, la otra debe seguir estando definida
	//Analizar que el borrado funciona bien si el diccionario tiene definido una sola palabra y esta se borra.

	DiccString<int> d;
	d.Definir("hola",42);
	d.Definir("casa",22);
	d.Borrar("casa");
	d.Definir("casa",23);
	d.Definir("casona",48);
	ASSERT( d.Definido("hola") );
	ASSERT(d.Definido("casa") );
}
void tests_borrarUna(){
	DiccString<int> d;
	d.Definir("holamanola",42);
	d.Borrar("holamanola");
	ASSERT_EQ(d.Claves().cardinal(),0);
}
void tests_agregarmuchos() {
	DiccString<int> d;
	d.Definir("casa",1);
	d.Definir("casarse",2);
	d.Definir("hola",3);
	d.Definir("holanda",4);
	d.Definir("casamiento",5);
	d.Definir("caminar",6);
	d.Definir("cordobazoo",7);
	d.Borrar("casa");
	d.Borrar("hola");
	ASSERT(d.Definido("holanda"));
	ASSERT(!d.Definido("casa"));
}

void tests_copiar(){
	DiccString<int> d;
	d.Definir("casa",1);
	d.Definir("casarse",2);
	d.Definir("hola",3);
	d.Definir("holanda",4);
	d.Definir("casamiento",5);
	d.Definir("caminar",6);
	d.Definir("cordobazo",7);

	DiccString<int> e(d);

	ASSERT(e.Definido("holanda"));
	ASSERT(e.Definido("casa"));
	ASSERT_EQ(e.Claves().cardinal(),7);
	ASSERT_EQ(e.Obtener("hola"),3);
	ASSERT_EQ(e.Obtener("cordobazo"),7);
	ASSERT_EQ(e.Obtener("casarse"),2);
	ASSERT_EQ(e.Obtener("caminar"),6);
}

void tests_agregarmuchosborrandodivisiones() {
	DiccString<int> d;
	d.Definir("casa",1);
	d.Definir("casarse",2);
	d.Definir("hola",3);
	d.Definir("holanda",4);
	d.Definir("casamiento",5);
	d.Definir("caminar",6);
	d.Definir("cordobazoo",7);
	d.Borrar("casa");
	d.Borrar("hola");
	d.Borrar("casarse");
	ASSERT(d.Definido("holanda"));
	ASSERT(!d.Definido("casa"));
	ASSERT(d.Definido("casamiento"));
}

void test_pisar(){
	DiccString<int> d;
	d.Definir("casarse",2);
	d.Definir("casarse",192);
	ASSERT(d.Definido("casarse"));
	ASSERT_EQ(d.Obtener("casarse"),192);

}
void test_casa(){
DiccString<int> d;
d.Definir("casa",42);
d.Definir("c",40);
ASSERT(d.Definido("casa"));
d.Borrar("casa");
std::cout << "despues de d.borrar casa" << std::endl;
ASSERT(d.Definido("c"));
}

int main() {
	/*
	RUN_TEST(test_claves_dicc_vacio);
	RUN_TEST(test_definir_definido);
	RUN_TEST(test_obtener);
	RUN_TEST(test_borrar);
	RUN_TEST(tests_borrarUna);
	RUN_TEST(tests_agregarmuchos);
	RUN_TEST(tests_copiar);
	RUN_TEST(tests_agregarmuchosborrandodivisiones);
	RUN_TEST(test_pisar);
	*/
	RUN_TEST(test_casa);
	return 0;

}
