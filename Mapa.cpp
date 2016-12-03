#include "Mapa.h"

Mapa::Mapa(){
    DiccMatriz < bool > mapa0(false);
    mapa = mapa0;
}
/*
Mapa::Mapa():mapa(DiccMatriz<bool> mapa0(false)){}
*/
Mapa::~Mapa(){

}
bool Mapa::Vacia()const{
  return mapa.Vacio();
}
///////////////////////////////////// terminar de arreglar posicion real////////////////////////////////////////

Nat FDX(Nat x,Nat y,Nat z){
  return (z*(x-1) + y);
}

Coordenada PosicionReal(const Coordenada &c,Nat longitud){
Nat P = FDX (c.latitud() ,c.longitud(),longitud );
Coordenada d(P,P);
return d;
}

bool Mapa::PosExistente(const Coordenada &c)const{
  Coordenada d = PosicionReal(c,mapa.Longitud());
  return mapa.Definido(d);
}


bool Mapa::HayCamino(const Coordenada &c,const Coordenada &d)const{
Coordenada e = PosicionReal(c,mapa.Longitud());
Coordenada f = PosicionReal(d,mapa.Longitud());
Coordenada g(e.latitud(),f.longitud());
  return mapa.Definido(g);
}


void  Mapa::AgregarAdyacentes(Conj<Coordenada> &Avisitar,const Coordenada &c){
  Nat lon = mapa.Longitud();
  Coordenada c_Der(c.latitud()+1,c.longitud());
/*
  std::cout << "el valor de c_Der es: " << std::endl;
  std::cout << "c_Der(" << c_Der.latitud()<< ","<< c_Der.longitud()<<")"<< endl;
*/
  if (!mapa.FueraDeRango(c_Der)) {
    Coordenada Derecha = PosicionReal(c_Der,lon);
    if (mapa.Definido(Derecha)) {
  //    std::cout << "agregue algo" << std::endl;
      Avisitar.Agregar(Derecha);
    }
  }

  Coordenada c_Izq(c.latitud()-1,c.longitud());

/*
  std::cout << "el valor de c_Izq es: " << std::endl;
  std::cout << "c_Izq(" << c_Izq.latitud()<< ","<< c_Izq.longitud()<<")"<< endl;
*/
  if (!mapa.FueraDeRango(c_Izq)) {
    Coordenada Izquierda = PosicionReal(c_Izq,lon);
    if (mapa.Definido(Izquierda)) {
  //          std::cout << "agregue algo" << std::endl;
      Avisitar.Agregar(Izquierda);
    }
  }

  Coordenada c_Arr(c.latitud(),c.longitud()+1);
/*  std::cout << "el valor de c_Arr es: " << std::endl;
  std::cout << "c_Arr(" << c_Arr.latitud()<< ","<< c_Arr.longitud()<<")"<< endl;
*/
  if (!mapa.FueraDeRango(c_Arr)) {
    Coordenada Arriba = PosicionReal(c_Arr,lon);
    if (mapa.Definido(Arriba)) {
  //          std::cout << "agregue algo" << std::endl;
      Avisitar.Agregar(Arriba);
    }
  }

  Coordenada c_Abj(c.latitud(),c.longitud()-1);
  /*std::cout << "el valor de c_Abj es: " << std::endl;
  std::cout << "c_Abj(" << c_Abj.latitud()<< ","<< c_Abj.longitud()<<")"<< endl;
  */if (!mapa.FueraDeRango(c_Abj)) {
    Coordenada Abajo = PosicionReal(c_Abj,lon);
    if (mapa.Definido(Abajo)) {
    //        std::cout << "agregue algo" << std::endl;
      Avisitar.Agregar(Abajo);
    }
  }



}




void Mapa::AgregarCoord(const Coordenada &c){

  Nat lat = mapa.Longitud();
  Coordenada d = PosicionReal(c,lat);
  mapa.Definir(d,true);
  std::cout << "la longitud del mapa es: " << mapa.Longitud() << std::endl;
std::cout << "la latitud del mapa es: " << mapa.Latitud() << std::endl;
  Conj<Coordenada> Visitadas;
  Conj<Coordenada> Avisitar;
  Visitadas.Agregar(d);
  AgregarAdyacentes(Avisitar,c);
  Conj<Coordenada>::Iterador IT = Avisitar.CrearIt();
  while (IT.HaySiguiente()) {
std::cout << "entre" << std::endl;
    Visitadas.Agregar(IT.Siguiente());
    AgregarAdyacentes(Avisitar,IT.Siguiente());
    Conj<Coordenada>::Iterador IT_Visitadas = Visitadas.CrearIt();
    while (IT_Visitadas.HaySiguiente()) {
      Avisitar.Eliminar(IT_Visitadas.Siguiente());
      IT_Visitadas.Avanzar();
    }
    Conj<Coordenada>::Iterador IT_Nuevo = Avisitar.CrearIt();
    IT=IT_Nuevo;
  }
  Conj<Coordenada>::Iterador IT_Agregar = Visitadas.CrearIt();
  while (IT_Agregar.HaySiguiente()) {
    Conj<Coordenada>::Iterador IT_Recorre = Visitadas.CrearIt();
    Coordenada primero = PosicionReal(IT_Agregar.Siguiente(),lat);
    while (IT_Recorre.HaySiguiente()) {
      Coordenada segundo = PosicionReal(IT_Recorre.Siguiente(),lat);
      Coordenada a(primero.latitud(),segundo.longitud());
      Coordenada b(segundo.latitud(),primero.longitud());
      mapa.Definir(a,true);
      mapa.Definir(b,true);
      IT_Recorre.Avanzar();
    }
    IT_Agregar.Avanzar();
  }
}
