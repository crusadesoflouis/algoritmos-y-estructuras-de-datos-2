#include <iostream>
#include "mini_test.h"
#include "Juego.h"

Coordenada c_0_0(0,0);
Coordenada c_0_1(0,1);
Coordenada c_0_2(0,2);
Coordenada c_0_3(0,3);
Coordenada c_1_0(1,0);
Coordenada c_1_1(1,1);
Coordenada c_1_2(1,2);
Coordenada c_1_3(1,3);
Coordenada c_2_0(2,0);
Coordenada c_2_1(2,1);
Coordenada c_2_2(2,2);
Coordenada c_2_3(2,3);
Coordenada c_3_0(3,0);
Coordenada c_3_1(3,1);
Coordenada c_3_2(3,2);
Coordenada c_3_3(3,3);
Coordenada c_4_4(4,4);
Coordenada c_6_6(6,6);
Coordenada c_6_7(6,7);
Coordenada c_7_2(7,2);
Coordenada c_8_8(8,8);
Coordenada c_10_10(10,10);
Coordenada c_11_11(11,11);
Coordenada c_12_12(12,12);
Coordenada c_15_15(15,15);
Coordenada c_20_20(20,20);
Coordenada c_50_50(50,50);

Pokemon Pikachu = "Pikachu";
Pokemon Abra = "Abra";
Pokemon Jolteon = "Jolteon";
Pokemon Zubat = "Zubat";

void testVacio(){
  Mapa m;
  ASSERT_EQ(m.Vacia(),true);
}



void testAgregarCoordenada(){
  Mapa m;
  ASSERT_EQ(m.Vacia(),true);
  m.AgregarCoord(c_10_10);
  m.AgregarCoord(c_1_1);
  m.AgregarCoord(c_2_2);
  m.AgregarCoord(c_1_0);
  m.AgregarCoord(c_3_3);
  m.AgregarCoord(c_6_6);
  m.AgregarCoord(c_8_8);
  ASSERT_EQ(m.Vacia(),false);
  ASSERT_EQ(m.PosExistente(c_1_1),true);
  Juego j(m);
  ASSERT_EQ(j.PosExistente(c_1_1),true);

//  ASSERT_EQ(m.HayCamino(c_1_1,c_3_3),false);
/*
Conj<Coordenada> a = j.ObtenerPosicionesCercanas(c_1_0);
ASSERT_EQ(a.Pertenece(c_1_0),true);
ASSERT_EQ(a.Pertenece(c_8_8),false);
ASSERT_EQ(a.Pertenece(c_1_1),true);
ASSERT_EQ(a.Pertenece(c_2_2),false);
*/
}

void testsAgregarBasico(){
  Mapa m;
  Pokemon Abra = "Abra";
  m.AgregarCoord(c_10_10);
  m.AgregarCoord(c_1_1);
  m.AgregarCoord(c_1_2);
  Juego j(m);
  j.AgregarPokemon(c_1_1,Abra);
  ASSERT_EQ(j.HayPokemonCercano(c_1_2),true);
  std::cout << "latitud: " <<j.PosPokemonCercano(c_1_2).latitud() <<std::endl;
  std::cout << "longitud: " <<j.PosPokemonCercano(c_1_2).longitud() <<std::endl;

}

void testAgregarPokemon(){
  Mapa m;
  m.AgregarCoord(c_11_11);
  m.AgregarCoord(c_1_1);
  m.AgregarCoord(c_6_6);
  m.AgregarCoord(c_3_3);
  m.AgregarCoord(c_2_2);
  m.AgregarCoord(c_3_1);
  m.AgregarCoord(c_2_2);
  m.AgregarCoord(c_4_4);
  m.AgregarCoord(c_1_2);
  m.AgregarCoord(c_2_2);
  m.AgregarCoord(c_3_0);
  m.AgregarCoord(c_10_10);

  Juego j(m);
//  std::cout << "agregar abra" << std::endl;
  j.AgregarPokemon(c_1_1,Abra);
//  std::cout << "puedo agregar 3 0 " << std::endl;
//  ASSERT_EQ(j.PuedoAgregarPokemon(c_3_0),false);
  ASSERT_EQ(j.PuedoAgregarPokemon(c_10_10),true);
  j.AgregarPokemon(c_10_10,Pikachu);
//  std::cout << "puedo agregar 50 50 " << std::endl;
//  ASSERT_EQ(j.PuedoAgregarPokemon(c_50_50),true);

  }

void testcompleto(){
  Mapa m;
  m.AgregarCoord(c_10_10);
  m.AgregarCoord(c_1_1);
  m.AgregarCoord(c_6_6);
  m.AgregarCoord(c_3_3);
  m.AgregarCoord(c_2_2);
  m.AgregarCoord(c_3_1);
  ASSERT_EQ(m.PosExistente(c_1_1),true);
  Juego j(m);
  Jugador manolo = j.AgregarJugador();
  Jugador pepe = j.AgregarJugador();
  j.AgregarPokemon(c_1_1,Abra);
  j.AgregarPokemon(c_6_6,Abra);
  ASSERT_EQ(j.EstaConectado(pepe),false);
  j.Conectarse(c_1_1,pepe);
  ASSERT_EQ(m.PosExistente(c_1_1),true);
  ASSERT_EQ(m.PosExistente(c_6_6),true);
  ASSERT_EQ(m.PosExistente(c_12_12),false);
  ASSERT_EQ(j.EstaConectado(manolo),false);
  ASSERT_EQ(j.EstaConectado(pepe),true);
  ASSERT_EQ(j.Sanciones(manolo),0);
  ASSERT_EQ(j.Sanciones(pepe),0);
  ASSERT_EQ(j.PokemonEnPos(c_1_1),Abra);
  ASSERT_EQ(j.cantMismaEspecie(Abra),2);
  ASSERT_EQ(j.IndiceRareza(Abra),100);
  ASSERT_EQ(j.CantMovimientosParaCaptura(c_1_1),10);
}


void testConectar() {
  Mapa m;
  m.AgregarCoord(c_20_20);
  m.AgregarCoord(c_1_2);
  m.AgregarCoord(c_1_1);
  m.AgregarCoord(c_6_6);
  Juego j(m);
  Jugador manolo = j.AgregarJugador();
  Jugador pepe = j.AgregarJugador();
  j.AgregarPokemon(c_1_1,Abra);
  j.Conectarse(c_1_1,manolo);
  j.Conectarse(c_6_6,pepe);
  ASSERT_EQ(j.EstaConectado(manolo),true);
  ASSERT_EQ(j.EstaConectado(pepe),true);
  ASSERT_EQ(j.CantMovimientosParaCaptura(c_1_1),10);
  ASSERT_EQ(j.Sanciones(manolo),0);
  j.Desconectarse(manolo);
  std::cout << "latitud: " <<j.PosPokemonCercano(c_1_2).latitud() <<std::endl;
  std::cout << "longitud: " <<j.PosPokemonCercano(c_1_2).longitud() <<std::endl;
  ASSERT_EQ(j.EstaConectado(manolo),false);
  ASSERT_EQ(j.CantMovimientosParaCaptura(c_1_1),10);
}

void testMoverYcapturar(){
  Mapa m;
  m.AgregarCoord(c_20_20);
  m.AgregarCoord(c_1_2);
  m.AgregarCoord(c_1_1);
  m.AgregarCoord(c_6_6);
  m.AgregarCoord(c_6_7);
  Juego j(m);
  Jugador manolo = j.AgregarJugador();
  Jugador pepe = j.AgregarJugador();
  Jugador pepita = j.AgregarJugador();
  std::cout << "primer abra" << std::endl;
  j.AgregarPokemon(c_1_1,Abra);
  std::cout << "despues de primer abra" << std::endl;
  j.Conectarse(c_1_1,manolo);
  j.Conectarse(c_6_6,pepe);
  ASSERT_EQ(j.CantMovimientosParaCaptura(c_1_1),10);
  j.Moverse(c_6_7,pepe);
  ASSERT_EQ(j.CantMovimientosParaCaptura(c_1_1),9);
  ASSERT_EQ(j.Sanciones(pepe),1);
  j.Moverse(c_20_20,pepe);
  ASSERT_EQ(j.CantMovimientosParaCaptura(c_1_1),8);
  ASSERT_EQ(j.Sanciones(pepe),2);
  j.Moverse(c_6_7,pepe);
  ASSERT_EQ(j.CantMovimientosParaCaptura(c_1_1),7);
  ASSERT_EQ(j.Sanciones(pepe),3);
  j.Moverse(c_20_20,pepe);
  ASSERT_EQ(j.CantMovimientosParaCaptura(c_1_1),6);
  j.Moverse(c_6_7,pepe);
  ASSERT_EQ(j.CantMovimientosParaCaptura(c_1_1),6);
  ASSERT_EQ(j.Sanciones(pepe),5);
  j.Conectarse(c_6_6,pepita);
  ASSERT_EQ(j.EstaConectado(pepita),true);
  ASSERT_EQ(j.Sanciones(pepe),5);
  j.Moverse(c_20_20,pepita);
  j.Moverse(c_6_7,pepita);
  j.Moverse(c_20_20,pepita);
  j.Moverse(c_6_7,pepita);
  j.Moverse(c_20_20,pepita);
  ASSERT_EQ(j.Sanciones(pepita),5);
  ASSERT_EQ(j.CantMovimientosParaCaptura(c_1_1),2);
  Jugador manola = j.AgregarJugador();
  j.Conectarse(c_6_6,manola);
  j.Moverse(c_20_20,manola);
  ASSERT_EQ(j.CantMovimientosParaCaptura(c_1_1),1);
  j.Moverse(c_6_7,manola);
  //Conj<String>::const_Iterador IT = j.Pokemons(manolo);
  //std::cout << "El pokemon es: " << IT.Siguiente() <<std::endl;
  //j.AgregarPokemon(c_1_1,Abra);
//  ASSERT_EQ(j.CantMovimientosParaCaptura(c_1_1),10);
  //j.Moverse(c_1_2,manolo);
//  ASSERT_EQ(j.CantMovimientosParaCaptura(c_1_1),10);
}

void testJugadores(){
  Mapa m;
  m.AgregarCoord(c_20_20);
  m.AgregarCoord(c_1_2);
  m.AgregarCoord(c_1_1);
  m.AgregarCoord(c_6_6);
  m.AgregarCoord(c_6_7);
  Juego j(m);
  Jugador manolo = j.AgregarJugador();
  Jugador pepe = j.AgregarJugador();
  Jugador pepita = j.AgregarJugador();
  Jugador manola = j.AgregarJugador();
  j.Conectarse(c_1_2,manolo);
  j.Conectarse(c_1_2,pepe);
  j.Conectarse(c_1_2,pepita);
  j.Conectarse(c_1_2,manola);
  j.Moverse(c_6_6,manolo);
  j.Moverse(c_20_20,manolo);
  j.Moverse(c_6_6,manolo);
  j.Moverse(c_20_20,manolo);
  j.Moverse(c_6_6,manolo);
  j.Moverse(c_6_6,pepe);
  j.Moverse(c_20_20,pepe);
  j.Moverse(c_6_6,pepe);
  j.Moverse(c_20_20,pepe);
  j.Moverse(c_6_6,pepe);
  ASSERT_EQ(j.Sanciones(manolo),5);
  ASSERT_EQ(j.Sanciones(pepe),5);
  Juego::Iterador IT = j.CrearIt();
  while (IT.HaySiguiente()) {
  std::cout << "siguiente: " <<IT.Siguiente() <<std::endl;
  IT.Avanzar();
  }
}

void testExpulsados(){
  Mapa m;
  m.AgregarCoord(c_20_20);
  m.AgregarCoord(c_1_2);
  m.AgregarCoord(c_1_1);
  m.AgregarCoord(c_6_6);
  m.AgregarCoord(c_6_7);
  Juego j(m);
  Jugador manolo = j.AgregarJugador();
  Jugador pepe = j.AgregarJugador();
  Jugador pepita = j.AgregarJugador();
  Jugador manola = j.AgregarJugador();
  j.Conectarse(c_1_2,manolo);
  j.Conectarse(c_1_2,pepe);
  j.Conectarse(c_1_2,pepita);
  j.Conectarse(c_1_2,manola);
  j.Moverse(c_6_6,manolo);
  j.Moverse(c_20_20,manolo);
  j.Moverse(c_6_6,manolo);
  j.Moverse(c_20_20,manolo);
  j.Moverse(c_6_6,manolo);
  j.Moverse(c_6_6,pepe);
  j.Moverse(c_20_20,pepe);
  j.Moverse(c_6_6,pepe);
  j.Moverse(c_20_20,pepe);
  j.Moverse(c_6_6,pepe);
  ASSERT_EQ(j.Sanciones(manolo),5);
  ASSERT_EQ(j.Sanciones(pepe),5);
  Juego::Iterador_Exp IT = j.CrearIt_Exp();
  while (IT.HaySiguiente()) {
    std::cout << "el jugador expulsado es: " <<IT.Siguiente() <<std::endl;
    IT.Avanzar();
  }
}

void pokemones() {
  Mapa m;
  m.AgregarCoord(c_20_20);
  m.AgregarCoord(c_1_2);
  m.AgregarCoord(c_1_1);
  m.AgregarCoord(c_6_6);
  m.AgregarCoord(c_6_7);
  m.AgregarCoord(c_10_10);
  m.AgregarCoord(c_15_15);
  Juego j(m);
  j.AgregarPokemon(c_1_2,Abra);
  ASSERT_EQ(j.PuedoAgregarPokemon(c_1_1),false);
  ASSERT_EQ(j.PuedoAgregarPokemon(c_6_6),true);
  ASSERT_EQ(j.CantPokemonTotales(),1);
  ASSERT_EQ(j.cantMismaEspecie(Abra),1);
  ASSERT_EQ(j.PokemonEnPos(c_1_2),Abra);
  j.AgregarPokemon(c_6_6,Zubat);
  j.AgregarPokemon(c_20_20,Pikachu);
  Conj < Coordenada > a(j.posConPokemons());
  Conj < Coordenada >::const_Iterador IT = a.CrearIt();
  while (IT.HaySiguiente()) {
    std::cout << "lat: " << IT.Siguiente().latitud()<< "long: " << IT.Siguiente().longitud() <<std::endl;
    IT.Avanzar();
  }

}

void testEntrePosibles(){
  Mapa m;
  m.AgregarCoord(c_1_1);
  Juego j(m);
  Jugador manolo = j.AgregarJugador();
  Jugador pepe = j.AgregarJugador();
  Jugador pepita = j.AgregarJugador();
  Jugador manola = j.AgregarJugador();
  Jugador Pepito = j.AgregarJugador();
  j.Conectarse(c_1_1,manolo);
  j.Conectarse(c_1_1,pepe);
  j.Conectarse(c_1_1,pepita);
  j.Conectarse(c_1_1,manola);
  j.Conectarse(c_1_1,Pepito);
  j.AgregarPokemon(c_1_1,Abra);
  Conj < Jugador > b;
  b.Agregar(manolo);
  b.Agregar(pepe);
  b.Agregar(pepita);
//Conj< Jugador > a(j.EntrenadoresPosibles(c_1_1,b));
}



int main(){
/*
  RUN_TEST(testVacio);
  RUN_TEST(testAgregarCoordenada);
  RUN_TEST(testAgregarPokemon);
  RUN_TEST(testsAgregarBasico);
  RUN_TEST(testcompleto);
  RUN_TEST(testConectar);
  RUN_TEST(testJugadores);
  RUN_TEST(testExpulsados);
  RUN_TEST(testMoverYcapturar);
  RUN_TEST(testEntrePosibles);
  */
    RUN_TEST(pokemones);
}
