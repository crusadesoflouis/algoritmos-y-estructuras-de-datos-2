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
  Nat CantidadAtrapados = 0;
  bool online = false;
  /*
  //creo un iterador al vector donde estan todos los jugadores
  Vector<InfoJug*>::const_Iterador IT = Jugadores.CrearIt();
  while (IT.HaySiguiente()) {
    online = IT.Siguiente().Conectado;
    if (online && PuedeAtrapar(c,IT.Siguiente().Posicion)) {

      IT.Siguiente().CazaActual = InfoPos.PosiblesEntrenadores.Encolar(IT.Siguiente(),)
    }
  }*/
}
