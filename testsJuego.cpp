#include <iostream>
#include "mini_test.h"
#include "Juego.h"





void testVacio(){
  Mapa m;
  ASSERT_EQ(m.Vacia(),true);
}



void testAgregarCoordenada(){
  Mapa m;
  Coordenada c_1_1(1,1);
  Coordenada c_3_3(3,3);
  ASSERT_EQ(m.Vacia(),true);
  m.AgregarCoord(c_1_1);
  m.AgregarCoord(c_3_3);
  ASSERT_EQ(m.Vacia(),false);
  ASSERT_EQ(m.PosExistente(c_1_1),true);
  ASSERT_EQ(m.HayCamino(c_1_1,c_3_3),false);
}


void testAgregarPokemon(){
  Mapa m;
  Coordenada c_1_1(1,1);
  Coordenada c_6_6(6,6);
  Coordenada c_12_12(12,12);
  Pokemon Pikachu = "Pikachu";
  Pokemon Abra = "Abra";
  m.AgregarCoord(c_1_1);

  //m.AgregarCoord(c_6_6);
  //m.AgregarCoord(c_12_12);

  ASSERT_EQ(m.PosExistente(c_1_1),true);
  Juego j(m);
  Jugador manolo = j.AgregarJugador();
  Jugador pepe = j.AgregarJugador();
  j.AgregarPokemon(c_1_1,Abra);
  //j.AgregarPokemon(c_6_6,Abra);
  //j.AgregarPokemon(c_12_12,Abra);
  ASSERT_EQ(j.EstaConectado(pepe),false);
  j.Conectarse(c_1_1,pepe);
  ASSERT_EQ(m.PosExistente(c_1_1),true);
  ASSERT_EQ(m.PosExistente(c_6_6),false);
  ASSERT_EQ(m.PosExistente(c_12_12),false);
  ASSERT_EQ(j.EstaConectado(manolo),false);
  ASSERT_EQ(j.EstaConectado(pepe),true);
  ASSERT_EQ(j.Sanciones(manolo),0);
  ASSERT_EQ(j.Sanciones(pepe),0);
  //porque no me lo reconoce?
  //ASSERT_EQ(j.Posicion(pepe),c_1_1);
  ASSERT_EQ(j.PokemonEnPos(c_1_1),Abra);
  //ASSERT_EQ(j.HayPokemonCercano(c_1_1),true);
  ASSERT_EQ(j.cantMismaEspecie(Abra),1);

  ASSERT_EQ(j.IndiceRareza(Abra),1);
    std::cout << "/* message */" << std::endl;
  ASSERT_EQ(j.CantMovimientosParaCaptura(c_1_1),10);
}
/*



  j.AgregarPokemon(c_1_1,Abra);
  j.Conectarse(c_1_1,manolo);
  std::cout << "voy a conectar a pepe" << std::endl;
  j.Conectarse(c_1_1,pepe);
*/


int main(){
  RUN_TEST(testVacio);
  RUN_TEST(testAgregarCoordenada);
  RUN_TEST(testAgregarPokemon);
}
