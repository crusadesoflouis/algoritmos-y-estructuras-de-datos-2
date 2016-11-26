#include "Mapa.h"

Mapa::Mapa(){
}

Mapa::~Mapa(){

}
bool Mapa::Vacia()const{
  return mapa.Vacio();
}
///////////////////////////////////// terminar de arreglar posicion real////////////////////////////////////////
coordenada PosicionReal(const coordenada &c,const coordenada &d, const Nat latitudTotal){

  if (c==d) {
     Nat PosicionX = c.latitud()*c.latitud();
     Nat PosicionY = c.longitud()*c.longitud();
     coordenada e(PosicionX,PosicionY);
     return e;
  }
  else{
    Nat PosicionX = c.latitud()*(latitudTotal - 1) + c.longitud();
    Nat PosicionY = d.latitud()*(latitudTotal - 1) + d.longitud();
    coordenada e(PosicionX,PosicionY);
    return e;
  }

}

bool Mapa::PosExistente(const coordenada &c)const{
  coordenada d = PosicionReal(c,c,mapa.Latitud());
  return mapa.Definido(d);
}


bool Mapa::HayCamino(const coordenada &c,const coordenada &d)const{
coordenada e = PosicionReal(c,d,mapa.Latitud());
  return mapa.Definido(e);
}


void Mapa::AgregarAdyacentes(Conj<coordenada> &Avisitar,const coordenada &c){
coordenada e(c);

Nat lat = mapa.Latitud();
coordenada c_Der(c.latitud()+1,c.longitud());
coordenada Derecha = PosicionReal(c_Der,c_Der,lat);
coordenada c_Izq(c.latitud()-1,c.longitud());
coordenada Izquierda = PosicionReal(c_Izq,c_Izq,lat);
coordenada c_Arr(c.latitud(),c.longitud()+1);
coordenada Arriba = PosicionReal(c_Arr,c_Arr,lat);
coordenada c_Abj(c.latitud(),c.longitud()-1);
coordenada Abajo = PosicionReal(c_Abj,c_Abj,lat);

coordenada c_1_1(1,1);
coordenada C_1_1 = PosicionReal(c_1_1,c_1_1,0);
std::cout << "c lat c long C lat C long " << std::endl;
cout << c_1_1.latitud() << endl;
cout << c_1_1.longitud() << endl;
cout << C_1_1.latitud() << endl;
cout << C_1_1.longitud() << endl;
std::cout << "pase el assert" << std::endl;

/*

  if (mapa.Definido(Arriba)) {
    Avisitar.Agregar(Arriba);
  }

    if (mapa.Definido(Izquierda)) {
      std::cout << "entre" << std::endl;
        Avisitar.Agregar(Izquierda);
    }

if (mapa.Definido(Derecha)) {
  Avisitar.Agregar(Derecha);
}
  if (mapa.Definido(Abajo)) {
    Avisitar.Agregar(Abajo);
  }


*/
}




void Mapa::AgregarCoord(const coordenada &c){

  Nat lat = mapa.Latitud();
  coordenada d = PosicionReal(c,c,lat);
  mapa.Definir(d,true);
  Conj<coordenada> Visitadas;
  Conj<coordenada> Avisitar;

  Visitadas.Agregar(d);
                  std::cout << "voy a entrar a agregar adyacentes" << std::endl;
  AgregarAdyacentes(Avisitar,c);
  std::cout << "sali agregar adyacentes" << std::endl;
    Conj<coordenada>::Iterador IT = Avisitar.CrearIt();

  while (IT.HaySiguiente()) {
    Visitadas.Agregar(IT.Siguiente());
    AgregarAdyacentes(Avisitar,IT.Siguiente());
    Conj<coordenada>::Iterador IT_Visitadas = Visitadas.CrearIt();
    while (IT_Visitadas.HaySiguiente()) {
      Avisitar.Eliminar(IT_Visitadas.Siguiente());
      IT_Visitadas.Avanzar();
    }
    Conj<coordenada>::Iterador IT_Agregar = Visitadas.CrearIt();

    while (IT_Agregar.HaySiguiente()) {
      coordenada LaVisitada = IT_Agregar.Siguiente();
      coordenada Cord_Agregada_1 = PosicionReal(c,LaVisitada,lat);
      coordenada Cord_Agregada_2 = PosicionReal(LaVisitada,c,lat);
      mapa.Definir(Cord_Agregada_1,true);
      mapa.Definir(Cord_Agregada_2,true);
      IT_Agregar.EliminarSiguiente();
      Conj<coordenada>::Iterador IT_Agregar = Visitadas.CrearIt();

    }
  }

}
