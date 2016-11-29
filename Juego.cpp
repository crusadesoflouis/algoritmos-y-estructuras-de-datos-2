#include "Juego.h"

//generadores
Juego::Juego():TotalPokemones(0){}

Juego::~Juego(){}

Jugador Juego::AgregarJugador(){
  Juego::InfoJug* nuevo = new InfoJug;
  Jugadores.AgregarAtras(nuevo);
  unsigned int ID = Jugadores.Longitud();
  return  ID;
}

coordenada Juego::PosPokemonCercano(const coordenada &c){
  Conj<coordenada>::Iterador IT = PosSalvajes.CrearIt();
  while (IT.HaySiguiente() && FuturasCapturas.Obtener(IT.Siguiente()) == NULL) {
      IT.Avanzar();
  }

  return IT.Siguiente();
}

bool Juego::HayPokemonCercano( const coordenada &c){

  //TODO

  return true;
}


bool Juego::PuedeAtrapar (const coordenada &c1,const coordenada &c2){
  //return distEuclidea(c1,c2) <= 4 &&  Mundo.HayCamino(c1,c2);
  //modificar class coordenada asi c1.distEuclidea(c2) de un Nat
  return true;
}

void Juego::AgregarPokemon(const coordenada &c, const Pokemon &p){
//agrego el pokemon en el mc donde estan las pos de pokemones salvajes
PosSalvajes.AgregarRapido(c);
// si estaba definido aumento en 1 su "cardinal" sino lo defino
  if (Pokedex.Definido(p)) {
      Nat valorAnterio = Pokedex.Significado(p);
      valorAnterio++;
      Pokedex.Borrar(p);
      Pokedex.Definir(p,valorAnterio);
      //tengo que eliminarlo y redefinirlo porque no tengo funciones
      //que me permita redefinirlo...
  }
  else{
    Pokedex.Definir(p,1);
  }
// creo un puntero a InfoPos que es donde hay que gener
//un heap con todos los jugadores cercanos a donde agregue
//dicho pokemon
  InfoPos* info = new InfoPos(p);
  bool online = false;

  //creo un iterador al vector donde estan todos los jugadores
  Vector<InfoJug*>::const_Iterador IT = Jugadores.CrearIt();
  Nat pos = 1;
  while (IT.HaySiguiente()) {
    online = IT.Siguiente()->Conectado;
    if (online && PuedeAtrapar(c,IT.Siguiente()->Posicion)) {
    //  Tupla<InfoJug*> t(Jugadores[pos],IT.Siguiente()->Atrapados.Cardinal(),pos);
    //  Jugadores[pos]->CazaActual() = info->PosiblesEntrenadores.Encolar(t);
    // o Jugadores[pos]->CazaActual()(info->PosiblesEntrenadores.Encolar(t));
    }
    pos++;
    IT.Avanzar();
  }
//////////////****************** revisar operator = del iterador

}

void Juego::Conectarse(const coordenada &c,const Jugador j){
  //assert(Jugadores[j]->Sanciones < 5);
  Jugadores[j]->Conectado = true;
  Jugadores[j]->Posicion = c;
  if (HayPokemonCercano(c)) {
      Tupla<InfoJug*> t(Jugadores[j],Jugadores[j]->Atrapados.Cardinal(),j);
    FuturasCapturas.Obtener(PosPokemonCercano(c))->PosiblesEntrenadores.Encolar(t);
  }
}


void Juego::Desconectarse(const Jugador j){
  Jugadores[j]->Conectado = false;
  // deberia haber un bool en la estructura InfoJug que diga si CazaActual tiene algo
  // o si no esta definido aun
  if (Jugadores[j]->EstaCazando) {
    Jugadores[j]->CazaActual.EliminarSiguiente();
  }
 if (FuturasCapturas.Obtener(PosPokemonCercano(Jugadores[j]->Posicion))->PosiblesEntrenadores.esVacia()) {
   FuturasCapturas.Obtener(PosPokemonCercano(Jugadores[j]->Posicion))->Turnos = 0;
  }
}


void Juego::Moverse(const coordenada &c,const Jugador j){

  //assert(Jugadores[j]->Sanciones < 5);
  bool HayPokemon = false;
  bool HayPokemonNuevo = false;
  coordenada vieja(0,0);
  coordenada nueva(0,0);

  if (HayPokemonCercano(Jugadores[j]->Posicion)) {
  HayPokemon = true;
  coordenada e(PosPokemonCercano(Jugadores[j]->Posicion).latitud(),PosPokemonCercano(Jugadores[j]->Posicion).longitud());
  vieja = e;
  }

  if (HayPokemonCercano(c)) {
    HayPokemonNuevo = true;
    nueva = PosPokemonCercano(c);
  }

  if (HayPokemonNuevo && HayPokemon && vieja == nueva) {
    Conj<coordenada>::Iterador IT = PosSalvajes.CrearIt();
    while (IT.HaySiguiente()) {
      FuturasCapturas.Obtener(IT.Siguiente())->Turnos++;
      if (FuturasCapturas.Obtener(IT.Siguiente())->Turnos == 10 && IT.Siguiente() != vieja) {
      //  Capturar(IT.Siguiente());
      }
      IT.Avanzar();
    }
  }
  else{
    //esto implica que en la posicion nueva y vieja son distintas
    //osea puede ser que ambas sean vacias
    //o que salgo de una cola y entro a otra
    //o que de no estar en nada voy a una nueva capturas


    if (HayPokemon && HayPokemonNuevo) {
      // caso en el que salgo de una cola y entro a otra
      Jugadores[j]->CazaActual.EliminarSiguiente();
      FuturasCapturas.Obtener(vieja)->Turnos++;
      FuturasCapturas.Obtener(nueva)->Turnos = 0;
      //FuturasCapturas.Significado(nueva)->PosiblesEntrenadores.Encolar( tupla);

    }
    else{

    }
  }



/*
  if (debeSancionarse(j)) {
    //arrastrar errores??
    Jugadores[j]->Sanciones == 4 ? Jugadores[j]->Sanciones = 1000: Jugadores[j]->Sanciones++;
      Jugadores[j]->PosiblesEntrenadores.EliminarSiguiente();
  }
  if (Jugadores[j]->Sanciones < 4 ) {
    Jugadores[j]->Posicion = c;
    FuturasCapturas.Significado(posPokemon)->Turnos++;
    if (HayPokemon && c.distEuclidea(posPokemon)>= 4) {
      Jugadores[j]->CazaActual.EliminarSiguiente();
    }
    if (c.distEuclidea(posPokemon) >= 4 && HayPokemonCercano(c)) {
      //encolo al jugador en la cola y devuelvo un iterador que se lo agrego
      //a CazaActual que es donde esta el iterador en la Tupla
      //  Tupla<InfoJug*> t(Jugadores[j],IT.Siguiente()->Atrapados.Cardinal(),pos);
      //jugadores[j]->CazaActual = FuturasCapturas.Significado(PosPokemonCercano(c))->PosiblesEntrenadores.Encolar(IT.Siguiente,cardinal,algomas);
      FuturasCapturas.Significado(PosPokemonCercano(c))->Turnos = 0;
    }
    if (FuturasCapturas.Significado(PosPokemonCercano(c))->Turnos == 10) {
      Jugador  Capturador = FuturasCapturas.Significado(PosPokemonCercano(c))->Posiblesentrenadores.Tope().Identificacion();
      Jugadores [Capturador]->Atrapados.Definir(FuturasCapturas.Significado(pospok)->Bicho);
      FuturasCapturas.Eliminar(pospok)
    }
  }
*/
}
