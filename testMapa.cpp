#include <iostream>
#include "mini_test.h"
#include "Mapa.h"
using namespace ::std;

void diccmatriz(){
  //inicializacion de datos
  Mapa m;
  coordenada c_1_1(1,1);
  coordenada c_3_3(3,3);
  coordenada c_3_1(3,1);
  coordenada c_3_2(3,2);
  coordenada c_7_2(7,2);
  coordenada c_2_2(2,2);
  coordenada c_2_1(2,1);

  ASSERT_EQ(m.Vacia(),true);
  m.AgregarCoord(c_1_1);
  ASSERT_EQ(m.Vacia(),false);
  ASSERT_EQ(m.PosExistente(c_3_3),false);
  ASSERT_EQ(m.PosExistente(c_1_1),true);
  m.AgregarCoord(c_3_3);
    /*
  m.AgregarCoord(c_3_2);
  ASSERT_EQ(m.HayCamino(c_3_3,c_3_2),true);

std::cout << "agregue c_3_3" << std::endl;
  m.AgregarCoord(c_3_1);
std::cout << "agregue c_3_1" << std::endl;

  std::cout << "agregue:c_3_2" << std::endl;

  m.AgregarCoord(c_7_2);
  m.AgregarCoord(c_2_2);
  ASSERT_EQ(m.HayCamino(c_1_1,c_1_1),true);
  ASSERT_EQ(m.HayCamino(c_3_3,c_2_1),true);
  ASSERT_EQ(m.HayCamino(c_2_1,c_3_3),true);
  ASSERT_EQ(m.HayCamino(c_1_1,c_3_3),false);
*/
  }

int main() {

RUN_TEST(diccmatriz);

  return 0;
}
