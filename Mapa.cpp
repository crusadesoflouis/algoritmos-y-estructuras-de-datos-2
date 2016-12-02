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
  std::cout << "la coordenada original es de lat: " << c.latitud()<< " de long: " << c.longitud()<< std::endl;
  std::cout << " real: la lontitud es: " << d.longitud() << " la latitud  es: "<< d.latitud()<< std::endl;
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
/*
  std::cout << "el valor de c_Der es: " << std::endl;
  std::cout << "c_Der(" << c_Der.latitud()<< ","<< c_Der.longitud()<<")"<< endl;
*/
  if (!mapa.FueraDeRango(c_Der)) {
    coordenada Derecha = PosicionReal(c_Der,lon);
    if (mapa.Definido(Derecha)) {
  //    std::cout << "agregue algo" << std::endl;
      Avisitar.Agregar(Derecha);
    }
  }

  coordenada c_Izq(c.latitud()-1,c.longitud());

/*
  std::cout << "el valor de c_Izq es: " << std::endl;
  std::cout << "c_Izq(" << c_Izq.latitud()<< ","<< c_Izq.longitud()<<")"<< endl;
*/
  if (!mapa.FueraDeRango(c_Izq)) {
    coordenada Izquierda = PosicionReal(c_Izq,lon);
    if (mapa.Definido(Izquierda)) {
  //          std::cout << "agregue algo" << std::endl;
      Avisitar.Agregar(Izquierda);
    }
  }

  coordenada c_Arr(c.latitud(),c.longitud()+1);
/*  std::cout << "el valor de c_Arr es: " << std::endl;
  std::cout << "c_Arr(" << c_Arr.latitud()<< ","<< c_Arr.longitud()<<")"<< endl;
*/
  if (!mapa.FueraDeRango(c_Arr)) {
    coordenada Arriba = PosicionReal(c_Arr,lon);
    if (mapa.Definido(Arriba)) {
  //          std::cout << "agregue algo" << std::endl;
      Avisitar.Agregar(Arriba);
    }
  }

  coordenada c_Abj(c.latitud(),c.longitud()-1);
  /*std::cout << "el valor de c_Abj es: " << std::endl;
  std::cout << "c_Abj(" << c_Abj.latitud()<< ","<< c_Abj.longitud()<<")"<< endl;
  */if (!mapa.FueraDeRango(c_Abj)) {
    coordenada Abajo = PosicionReal(c_Abj,lon);
    if (mapa.Definido(Abajo)) {
    //        std::cout << "agregue algo" << std::endl;
      Avisitar.Agregar(Abajo);
    }
  }



}




void Mapa::AgregarCoord(const coordenada &c){

  Nat lat = mapa.Longitud();

  coordenada d = PosicionReal(c,lat);
  mapa.Definir(d,true);
  std::cout << "la longitud del mapa es: " << mapa.Longitud() << std::endl;
  std::cout << "la latitud del mapa es: " << mapa.Latitud() << std::endl;
  Conj<coordenada> Visitadas;
  Conj<coordenada> Avisitar;
  Visitadas.Agregar(d);
  AgregarAdyacentes(Avisitar,c);
//std::cout << "sali de agregar adyacentes" << std::endl;
  Conj<coordenada>::Iterador IT = Avisitar.CrearIt();
//  std::cout << "el cardinal de Avisitar es: " << Avisitar.Cardinal() <<std::endl;
  while (IT.HaySiguiente()) {
  //  std::cout << "entre si hay siguientes a visitar" << std::endl;

    Visitadas.Agregar(IT.Siguiente());
    AgregarAdyacentes(Avisitar,IT.Siguiente());
  //  std::cout << "sali de agregar adyacentes" << std::endl;
    Conj<coordenada>::Iterador IT_Visitadas = Visitadas.CrearIt();
    while (IT_Visitadas.HaySiguiente()) {
    //  std::cout << "si hay visitadas las elimino de avisitar" << std::endl;
      Avisitar.Eliminar(IT_Visitadas.Siguiente());
  //    std::cout << "sali del eliminar" << std::endl;
      IT_Visitadas.Avanzar();
    }
    Conj<coordenada>::Iterador IT_Nuevo = Avisitar.CrearIt();
    IT=IT_Nuevo;
  }
//  std::cout << "llegue aca" << std::endl;
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
