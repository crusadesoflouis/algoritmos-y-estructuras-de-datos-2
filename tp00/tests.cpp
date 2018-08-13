// g++ -g tests.cpp -o tests
// valgrind --leak-check=full -v ./tests

#include <algorithm>
#include "mini_test.h"
#include "PlanificadorRR.h"

using namespace std;

string remove_spaces(const string& s) {
  string out(s);
  out.erase(remove(out.begin(), out.end(), ' '), out.end());
  out.erase(remove(out.begin(), out.end(), '\n'), out.end());
  return out;
}

template<typename T>
string to_s(const T& m) {
 	ostringstream os;
	os << m;
	return os.str();
}

void planificadoresVaciosIguales()
{
  PlanificadorRR<int> planificadorA, planificadorB;
  ASSERT (planificadorA == planificadorB);
}

void planificadoresIguales()
{
  PlanificadorRR<int> planificadorA, planificadorB;
planificadorA.agregarProceso(20);
planificadorA.agregarProceso(25);
planificadorA.agregarProceso(22);
planificadorB.agregarProceso(21);
planificadorB.agregarProceso(22);
  ASSERT(planificadorA == planificadorB);
}
void planificadorVacio()
{
  PlanificadorRR<int> planificador;
  ASSERT_EQ(planificador.hayProcesos(), false);
  ASSERT_EQ(planificador.hayProcesosActivos(), false);
  ASSERT_EQ(to_s(planificador), "[]");
  ASSERT_EQ(planificador.detenido(), false);
  ASSERT_EQ(planificador.cantidadDeProcesos(),0);
  ASSERT_EQ(planificador.cantidadDeProcesosActivos(),0);

}

void planificadorConUnElemento()
{
  PlanificadorRR<int> planificador;
  planificador.agregarProceso(3);
  ASSERT_EQ(planificador.hayProcesos(), true);
  ASSERT_EQ(planificador.hayProcesosActivos(), true);
  ASSERT_EQ(to_s(planificador), "[3*]");
  ASSERT_EQ(planificador.detenido(), false);
  ASSERT_EQ(planificador.cantidadDeProcesos(),1);
  ASSERT_EQ(planificador.cantidadDeProcesosActivos(),1);
}

void Uno_solo_pausado_y_reactivado()
{
  PlanificadorRR<int> planificador;
  planificador.agregarProceso(3);
  planificador.pausarProceso(3);

  planificador.reanudarProceso(3);
  ASSERT_EQ(planificador.hayProcesos(), true);
  ASSERT_EQ(planificador.hayProcesosActivos(), true);
  ASSERT_EQ(to_s(planificador), "[3*]");
  ASSERT_EQ(planificador.detenido(), false);
  ASSERT_EQ(planificador.cantidadDeProcesos(),1);
  ASSERT_EQ(planificador.cantidadDeProcesosActivos(),1);
  ASSERT_EQ(planificador.procesoEjecutado(),3);

}

void planificadorConMuchosPausados()
{
  PlanificadorRR<int> planificador;
  planificador.agregarProceso(3);
  planificador.agregarProceso(4);
  planificador.agregarProceso(6);
  planificador.agregarProceso(7);
  planificador.agregarProceso(9);
  planificador.pausarProceso(3);
  planificador.pausarProceso(9);
  planificador.pausarProceso(7);
  planificador.pausarProceso(4);
  planificador.eliminarProceso(3);
  planificador.agregarProceso(15);
  planificador.pausarProceso(6);
  ASSERT_EQ(planificador.hayProcesos(), true);
  ASSERT_EQ(planificador.hayProcesosActivos(), true);
  ASSERT_EQ(to_s(planificador), "[15*, 6 (i), 7 (i), 9 (i), 4 (i)]");
  ASSERT_EQ(planificador.detenido(), false);

  ASSERT_EQ(planificador.cantidadDeProcesos(),5);
  ASSERT_EQ(planificador.cantidadDeProcesosActivos(),1);

  ASSERT_EQ(planificador.procesoEjecutado(),15);

}
void planificadorConMuchos()
{
  PlanificadorRR<int> planificador;
  planificador.agregarProceso(3);
  planificador.agregarProceso(4);
  planificador.agregarProceso(5);
  planificador.agregarProceso(6);
  planificador.agregarProceso(7);
  planificador.agregarProceso(8);
  planificador.pausarProceso(8);
  planificador.pausarProceso(4);
  planificador.pausarProceso(3);
  ASSERT_EQ(planificador.procesoEjecutado(),5);
  ASSERT_EQ(planificador.hayProcesos(), true);
  ASSERT_EQ(planificador.hayProcesosActivos(), true);
  ASSERT_EQ(to_s(planificador), "[5*, 6, 7, 8 (i), 3 (i), 4 (i)]");
//[p2*, p0 (i), p1]
  ASSERT_EQ(planificador.detenido(), false);
  ASSERT_EQ(planificador.cantidadDeProcesos(),6);
  ASSERT_EQ(planificador.cantidadDeProcesosActivos(),3);

}

void planificadortest1()
{
  PlanificadorRR<int> planificador;
  planificador.agregarProceso(3);
  planificador.agregarProceso(4);
  planificador.agregarProceso(5);
  planificador.agregarProceso(6);
  planificador.detener();
  planificador.agregarProceso(7);
  planificador.agregarProceso(8);
  planificador.pausarProceso(4);
  planificador.pausarProceso(7);
  planificador.pausarProceso(3);
  planificador.eliminarProceso(8);
  planificador.eliminarProceso(4);
  planificador.ejecutarSiguienteProceso();
  planificador.ejecutarSiguienteProceso();
  ASSERT_EQ(planificador.procesoEjecutado(),5);
  ASSERT_EQ(planificador.hayProcesos(), true);
  ASSERT_EQ(planificador.hayProcesosActivos(), true);
  ASSERT_EQ(to_s(planificador), "[5*, 6, 7 (i), 3 (i)]");

//[p2*, p0 (i), p1]
  ASSERT_EQ(planificador.detenido(), true);
  ASSERT_EQ(planificador.cantidadDeProcesos(),4);
  ASSERT_EQ(planificador.cantidadDeProcesosActivos(),2);

}


void planificadortest2()
{
  PlanificadorRR<int> planificador;
  planificador.agregarProceso(3);
  planificador.agregarProceso(4);
  planificador.eliminarProceso(3);
  ASSERT_EQ(planificador.hayProcesos(), true);
  ASSERT_EQ(planificador.hayProcesosActivos(), true);
  ASSERT_EQ(to_s(planificador), "[4*]");
  ASSERT_EQ(planificador.detenido(), false);
  ASSERT_EQ(planificador.procesoEjecutado(),4);
  ASSERT_EQ(planificador.cantidadDeProcesos(),1);
  ASSERT_EQ(planificador.cantidadDeProcesosActivos(),1);
}

void planificadortest3()
{
  PlanificadorRR<int> planificador;
  planificador.agregarProceso(3);
  planificador.agregarProceso(4);
  planificador.agregarProceso(7);
  planificador.agregarProceso(0);
  planificador.agregarProceso(12);
  planificador.agregarProceso(44);
  planificador.pausarProceso(44);
  planificador.eliminarProceso(4);
  planificador.pausarProceso(3);
  ASSERT_EQ(planificador.hayProcesos(), true);
  ASSERT_EQ(planificador.hayProcesosActivos(), true);
  ASSERT_EQ(planificador.detenido(), false);
  ASSERT_EQ(planificador.procesoEjecutado(),7);
  ASSERT_EQ(planificador.cantidadDeProcesos(),5);
  ASSERT_EQ(planificador.cantidadDeProcesosActivos(),3);
}

void testDePlanificadoreSuperTurbioloco()
{

	PlanificadorRR< PlanificadorRR <int> > planificador;
	PlanificadorRR<int> planificadorA;
	PlanificadorRR<int> planificadorB;
	PlanificadorRR<int> planificadorC;
	planificador.agregarProceso(planificadorA);
 	 ASSERT_EQ(planificador.cantidadDeProcesosActivos(),1);
 	 ASSERT_EQ(planificador.cantidadDeProcesos(),1);
	planificador.agregarProceso(planificadorB);
 	 ASSERT_EQ(planificador.cantidadDeProcesos(),2);
	planificador.agregarProceso(planificadorC);
 	 ASSERT_EQ(planificador.cantidadDeProcesos(),3);
	ASSERT(planificadorA == planificadorB);
 	ASSERT_EQ(to_s(planificador), "[[]*, [], []]");

}

void testeliminar()
{
  PlanificadorRR<int> planificador;
  planificador.agregarProceso(3);
  planificador.agregarProceso(4);
  planificador.agregarProceso(6);
  planificador.pausarProceso(3);
  planificador.pausarProceso(6);
  planificador.pausarProceso(4);
  planificador.eliminarProceso(3);
  planificador.agregarProceso(15);
  planificador.agregarProceso(7);
  planificador.eliminarProceso(15);

  ASSERT_EQ(planificador.hayProcesos(), true);
  ASSERT_EQ(planificador.hayProcesosActivos(), true);
  ASSERT_EQ(to_s(planificador), "[7*, 4 (i), 6 (i)]");
  ASSERT_EQ(planificador.detenido(), false);
  ASSERT_EQ(planificador.cantidadDeProcesosActivos(),1);

  ASSERT_EQ(planificador.procesoEjecutado(),7);
  ASSERT_EQ(planificador.cantidadDeProcesos(),3);

}

void testigual()
{
  PlanificadorRR<int> planificadorA;
  planificadorA.agregarProceso(3);
  planificadorA.agregarProceso(4);
  planificadorA.agregarProceso(6);
  PlanificadorRR<int> planificadorB;
  planificadorB.agregarProceso(3);
  planificadorB.agregarProceso(4);
  planificadorB.agregarProceso(6);
  ASSERT(planificadorA == planificadorB);
}
void CopiarElPlanificador()
{
  PlanificadorRR<int> planificador;
  planificador.agregarProceso(3);
  planificador.pausarProceso(3);
  planificador.agregarProceso(5);
  ASSERT_EQ(planificador.hayProcesos(), true);
  ASSERT_EQ(planificador.hayProcesosActivos(), true);
  ASSERT_EQ(to_s(planificador), "[5*, 3 (i)]");
  ASSERT_EQ(planificador.detenido(), false);
  PlanificadorRR<int> planificadorB(planificador);
  ASSERT_EQ(to_s(planificador), "[5*, 3 (i)]");
  ASSERT_EQ(to_s(planificadorB), "[5*, 3 (i)]");
  to_s(planificadorB);
  to_s(planificador);
  planificadorB.agregarProceso(7);
}
void agregarTres(){
  PlanificadorRR<int> planificador;
  planificador.agregarProceso(3);
  ASSERT_EQ(planificador.hayProcesos(), true);
  ASSERT_EQ(planificador.hayProcesosActivos(), true);
  ASSERT_EQ(to_s(planificador), "[3*]");
  ASSERT_EQ(planificador.detenido(), false);
  ASSERT_EQ(planificador.cantidadDeProcesosActivos(),1);
  ASSERT_EQ(planificador.procesoEjecutado(),3);
  ASSERT_EQ(planificador.esPlanificado(33),false);
  ASSERT_EQ(planificador.esPlanificado(3),true);

}
int main()
{

 // RUN_TEST( planificadoresIguales )
  RUN_TEST( planificadoresVaciosIguales );
  RUN_TEST( planificadorVacio );
  RUN_TEST( planificadorConUnElemento );
  RUN_TEST( Uno_solo_pausado_y_reactivado );
  RUN_TEST( planificadorConMuchos);
  RUN_TEST( planificadortest2);
  RUN_TEST( planificadortest3);
  RUN_TEST( planificadortest1);
  RUN_TEST( testDePlanificadoreSuperTurbioloco );
  RUN_TEST( testeliminar);
  RUN_TEST( planificadorConMuchosPausados);
  RUN_TEST( testigual);
  RUN_TEST( CopiarElPlanificador );

  RUN_TEST (agregarTres);
return 0;

}
