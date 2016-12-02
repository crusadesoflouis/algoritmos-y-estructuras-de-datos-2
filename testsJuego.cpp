#include <iostream>
#include "mini_test.h"
#include "Juego.h"





void testVacio(){
}

int main(){

  Mapa m;
  Coordenada c_1_1(1,1);
  Coordenada c_3_3(3,3);
  ASSERT_EQ(m.Vacia(),true);
  m.AgregarCoord(c_1_1);
  m.AgregarCoord(c_3_3);
  ASSERT_EQ(m.Vacia(),false);
  ASSERT_EQ(m.PosExistente(c_1_1),true);


  Juego j(m);
  Jugador manolo = j.AgregarJugador();
  Jugador pepe = j.AgregarJugador();
  Pokemon Pikachu = "Pikachu";
  Pokemon Abra = "Abra";
  j.AgregarPokemon(c_1_1,Abra);
  j.Conectarse(c_1_1,manolo);
  std::cout << "voy a conectar a pepe" << std::endl;
  j.Conectarse(c_1_1,pepe);

}
