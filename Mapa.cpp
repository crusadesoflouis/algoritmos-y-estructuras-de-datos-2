#include "aed2.h"
#include "TiposJuego.h"
#include "Mapa.h"


Mapa::Mapa(){
}

bool Mapa::Vacia()const{
  return mapa.Vacio();
}

Coordenada PosicionReal(const Coordenada &c,const Coordenada &d, const Nat latitudTotal){
Nat PosicionX = c.latitud*(latitudTotal - 1) + c.longitud;
Nat PosicionY = d.latitud*(latitudTotal - 1) + d.longitud;
Coordenada e(PosicionX,PosicionY);
return e;
}

void Mapa::AgregarAdyacentes(Conj<Coordenada> &Avisitar,const Coordenada &c){
Coordenada e(c);
Nat lat = mapa.Latitud();
Coordenada c_Der(c.latitud+1,c.longitud);
Coordenada Derecha = PosicionReal(c_Der,c_Der,lat);
Coordenada c_Izq(c.latitud-1,c.longitud);
Coordenada Izquierda = PosicionReal(c_Izq,c_Izq,lat);
Coordenada c_Arr(c.latitud,c.longitud+1);
Coordenada Arriba = PosicionReal(c_Arr,c_Arr,lat);
Coordenada c_Abj(c.latitud,c.longitud-1);
Coordenada Abajo = PosicionReal(c_Abj,c_Abj,lat);

  if (mapa.Definido(Arriba)) {
    Avisitar.Agregar(Arriba);
  }

  if (mapa.Definido(Abajo)) {
    Avisitar.Agregar(Abajo);
  }

  if (mapa.Definido(Derecha)) {
    Avisitar.Agregar(Derecha);
  }

  if (mapa.Definido(Izquierda)) {
    Avisitar.Agregar(Izquierda);
  }



}


void Mapa::AgregarCoord(const Coordenada &c){
  Nat lat = mapa.Latitud();
  Coordenada d = PosicionReal(c,c,lat);
  mapa.Definir(d,true);
  Conj<Coordenada> Visitadas;
  Conj<Coordenada> Avisitar;
  Visitadas.Agregar(d);
  AgregarAdyacentes(Avisitar,c);

  Conj<Coordenada>::Iterador IT = Avisitar.CrearIt();
  while (IT.HaySiguiente()) {
    Visitadas.Agregar(IT.Siguiente());
    AgregarAdyacentes(Avisitar,IT.Siguiente());
    Conj<Coordenada>::Iterador IT_Visitadas = Visitadas.CrearIt();
    while (IT_Visitadas.HaySiguiente()) {
      Avisitar.Eliminar(IT_Visitadas.Siguiente());
      IT_Visitadas.Avanzar();
    }
    Conj<Coordenada>::Iterador IT_Agregar = Visitadas.CrearIt();
    while (IT_Agregar.HaySiguiente()) {
      Coordenada LaVisitada = IT_Agregar.Siguiente();
      Coordenada Cord_Agregada_1 = PosicionReal(c,LaVisitada,lat);
      Coordenada Cord_Agregada_2 = PosicionReal(LaVisitada,c,lat);
      mapa.Definir(Cord_Agregada_1,true);
      mapa.Definir(Cord_Agregada_2,true);
      IT_Agregar.EliminarSiguiente();
      Conj<Coordenada>::Iterador IT_Agregar = Visitadas.CrearIt();
//definir las dos posiciones de la coordenada
    }
  }
}

bool Mapa::PosExistente(const Coordenada &c)const{
  Coordenada d = PosicionReal(c,c,mapa.Latitud());
  return mapa.Definido(d);
}

bool Mapa::HayCamino(const Coordenada &c,const Coordenada &d)const{
Coordenada e = PosicionReal(c,d,mapa.Latitud());
  return mapa.Definido(e);
}
