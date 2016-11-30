#include "Mapa.h"

Mapa::Mapa(){
}

Mapa::~Mapa(){

}
bool Mapa::Vacia()const{
  return mapa.Vacio();
}
///////////////////////////////////// terminar de arreglar posicion real////////////////////////////////////////

Nat FDX(Nat x,Nat y,Nat z){
  return (z*(x-1) + y);
}

coordenada PosicionReal(const coordenada &c,Nat longitud){
Nat P = FDX (c.latitud() ,c.longitud(),longitud );
coordenada d(P,P);
return d;
}

bool Mapa::PosExistente(const coordenada &c)const{
  coordenada d = PosicionReal(c,mapa.Longitud());
  return mapa.Definido(d);
}


bool Mapa::HayCamino(const coordenada &c,const coordenada &d)const{
coordenada e = PosicionReal(c,mapa.Longitud());
coordenada f = PosicionReal(d,mapa.Longitud());
coordenada g(e.latitud(),f.longitud());
  return mapa.Definido(g);
}


void  Mapa::AgregarAdyacentes(Conj<coordenada> &Avisitar,const coordenada &c){
  Nat lon = mapa.Longitud();
  coordenada c_Der(c.latitud()+1,c.longitud());
  if (!mapa.FueraDeRango(c_Der)) {
    coordenada Derecha = PosicionReal(c_Der,lon);
    /*
    std::cout << "el valor de c_DER debe ser 2,1" << std::endl;
    std::cout << "c_Der(" << c_Der.latitud()<< ","<< c_Der.longitud()<<")"<< endl;
    */
    if (mapa.Definido(Derecha)) {
      Avisitar.Agregar(Derecha);
    }
  }

  coordenada c_Izq(c.latitud()-1,c.longitud());
  if (!mapa.FueraDeRango(c_Izq)) {
    coordenada Izquierda = PosicionReal(c_Izq,lon);
    if (mapa.Definido(Izquierda)) {
      Avisitar.Agregar(Izquierda);
    }
  }

  coordenada c_Arr(c.latitud(),c.longitud()+1);
  if (!mapa.FueraDeRango(c_Arr)) {
    coordenada Arriba = PosicionReal(c_Arr,lon);
    if (mapa.Definido(Arriba)) {
      Avisitar.Agregar(Arriba);
    }
  }

  coordenada c_Abj(c.latitud(),c.longitud()-1);
  if (!mapa.FueraDeRango(c_Abj)) {
    coordenada Abajo = PosicionReal(c_Abj,lon);
    if (mapa.Definido(Abajo)) {
      Avisitar.Agregar(Abajo);
    }
  }

}




void Mapa::AgregarCoord(const coordenada &c){

  Nat lat = mapa.Longitud();
  coordenada d = PosicionReal(c,lat);
  mapa.Definir(d,true);

  Conj<coordenada> Visitadas;
  Conj<coordenada> Avisitar;
  Visitadas.Agregar(d);
  AgregarAdyacentes(Avisitar,c);
std::cout << "sali de agregar adyacentes" << std::endl;
  Conj<coordenada>::Iterador IT = Avisitar.CrearIt();
  while (IT.HaySiguiente()) {
    Visitadas.Agregar(IT.Siguiente());
    AgregarAdyacentes(Avisitar,IT.Siguiente());
    Conj<coordenada>::Iterador IT_Visitadas = Visitadas.CrearIt();
    while (IT_Visitadas.HaySiguiente()) {
      Avisitar.Eliminar(IT_Visitadas.Siguiente());
      IT_Visitadas.Avanzar();
    }
    Conj<coordenada>::Iterador IT = Avisitar.CrearIt();
  }
  Conj<coordenada>::Iterador IT_Agregar = Visitadas.CrearIt();
  while (IT_Agregar.HaySiguiente()) {
    Conj<coordenada>::Iterador IT_Recorre = Visitadas.CrearIt();
    coordenada primero = PosicionReal(IT_Agregar.Siguiente(),lat);
    while (IT_Recorre.HaySiguiente()) {
      coordenada segundo = PosicionReal(IT_Recorre.Siguiente(),lat);
      coordenada a(primero.latitud(),segundo.longitud());
      coordenada b(segundo.latitud(),primero.longitud());
      mapa.Definir(a,true);
      mapa.Definir(b,true);
      IT_Recorre.Avanzar();
    }
    IT_Agregar.Avanzar();
  }
}
