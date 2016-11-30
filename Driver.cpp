#include "Driver.h"

// Instanciar un mapa y un juego

Driver::Driver(const Conj< Coordenada > & cs){
  Conj::Iterador IT = cs.CrearIT();
  while (IT.HaySiguiente()) {
    map.AgregarCoord(IT.Siguiente());
    IT.Avanzar();
  }
  Juego* jueg = new Juego(map);
}

Driver::~Driver(){
delete Jueg;
}

void Driver::agregarPokemon(const Pokemon & p, const Coordenada & c){
  jueg.AgregarPokemon(c,p);
}
//
Jugador Driver::agregarJugador(){
  return jueg.AgregarJugador();
}
//
void conectarse(const Jugador &j const Coordenada &c){
  jueg.Conectarse(c,j);
}
//
void desconectarse(const Jugador &j){
  jueg.Desconectarse(j);
}

void moverse(const Jugador &j,const Coordenada &c){
  jueg.Moverse(c,j);
}
// que hacer con esto //
Conj < Coordenada > mapa() const{
    Conj<Coordenada> c;
    return c;
}

bool EstaConectado(const Jugador & j){
  return jueg.EstaConectado(j);
}

Nat sanciones(const Jugador &j)const{
  retunr jueg.Sanciones(j);
}

Coordenada posicion(const Jugador &j)const{
  return jueg.Posicion(j);
}

Dicc <Pokemon, Nat> pokemons(const Jugador & j)const{

  Dicc <Pokemon, Nat> a;
  a.Definir("pikachu",10);
}

////////////////////////////////////////////////////////////////////////////////
Conj <Jugador> expulsados()const{
  Conj<Jugadores> a;
  Jugador b = 10;
  a.AgregarAtras(b);
  return a;
}
////////////////////////////////////////////////////////////////////////////////
Pokemon pokemonEnPos(const Coordenada &c)const{
  return jueg.PokemonEnPos(c);
}

Nat cantMovimientosParaCaptura(const Coordenada &c)const{
  return jueg.CantMovimientosParaCaptura(c);
}

////////////////////////////////////////////////////////////////////////////////
bool puedoAgregarPokemon(const Coordenada & c)const{
  return true;
  //  return jueg.PuedoAgregarPokemon(c);
}
////////////////////////////////////////////////////////////////////////////////
bool hayPokemonCercano(const Coordenada & c)const{
  jueg.HayPokemonCercano(c);
}

Coordenada posPokemonCercano(const Coordenada &c)const{
  return jueg.PosPokemonCercano(c);
}
////////////////////////////////////////////////////////////////////////////////
Conj<Jugador> entrenadoresPosibles(const Coordenada &c)const{
  Conj<Jugadores> a;
  Jugador b = 10;
  a.AgregarAtras(b);
  return a;
  //return EntrenadoresPosibles(c);
}
////////////////////////////////////////////////////////////////////////////////
Nat indiceRareza(const Pokemon &p )const{
  return 10;
  //return juego.IndiceRareza(p);
}
////////////////////////////////////////////////////////////////////////////////
Nat cantPokemonsTotales()const{
  return juego.CantPokemonTotales();
}
////////////////////////////////////////////////////////////////////////////////
Nat cantMismaEspecie(const Pokemon &p)const{
  return 10;
  //return CantMismaEspecie(p);
}
////////////////////////////////////////////////////////////////////////////////
