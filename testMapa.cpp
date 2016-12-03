#include <iostream>
#include "mini_test.h"
#include "aed2.h"
#include "TiposJuego.h"
#include "Mapa.h"
using namespace ::std;

void diccmatriz(){
  //inicializacion de datos
  Mapa m;
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
  Coordenada c_7_2(7,2);
  Coordenada c_10_10(10,10);

  ASSERT_EQ(m.Vacia(),true);
  m.AgregarCoord(c_10_10);
  m.AgregarCoord(c_0_0);
  m.AgregarCoord(c_1_1);
  ASSERT_EQ(m.PosExistente(c_1_1),true);
  ASSERT_EQ(m.Vacia(),false);
  m.AgregarCoord(c_3_3);
  ASSERT_EQ(m.PosExistente(c_1_1),true);
  m.AgregarCoord(c_3_2);
  ASSERT_EQ(m.PosExistente(c_3_2),true);
  m.AgregarCoord(c_3_3);
  ASSERT_EQ(m.PosExistente(c_3_3),true);
  ASSERT_EQ(m.PosExistente(c_10_10),true);
  ASSERT_EQ(m.PosExistente(c_7_2),false);
//  ASSERT_EQ(m.HayCamino(c_1_1,c_1_1),true);
//  ASSERT_EQ(m.HayCamino(c_3_3,c_2_1),true);
//  ASSERT_EQ(m.HayCamino(c_2_1,c_3_3),true);
//  ASSERT_EQ(m.HayCamino(c_1_1,c_3_3),false);
  }

int main() {

RUN_TEST(diccmatriz);

  return 0;
}
