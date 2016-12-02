#include "Driver.h"

// Instanciar un mapa y un juego

Driver::Driver(const Conj< Coordenada > & cs){
  Conj< Coordenada >::const_Iterador IT = cs.CrearIt();
  while (IT.HaySiguiente()) {
    map.AgregarCoord(IT.Siguiente());
    IT.Avanzar();
  }
  jueg = new Juego(map);
}

Driver::~Driver(){
delete jueg;
}

void Driver::agregarPokemon(const Pokemon & p, const Coordenada & c){
  jueg->AgregarPokemon(c,p);
}
//
Jugador Driver::agregarJugador(){
  return jueg->AgregarJugador();
}
//
void Driver::conectarse(const Jugador &j, const Coordenada &c){
  jueg->Conectarse(c,j);
}
//
void Driver::desconectarse(const Jugador &j){
  jueg->Desconectarse(j);
}

void Driver::moverse(const Jugador &j,const Coordenada &c){
  jueg->Moverse(c,j);
}
// que hacer con esto //
Conj < Coordenada > Driver::mapa() const{
    Conj<Coordenada> c;
    return c;
}

bool Driver::hayCamino(const Coordenada &c1, const Coordenada &c2)const{
  return jueg->HayCamino(c1,c2);
}

bool Driver::posExistente(const Coordenada &c)const{
  return jueg->PosExistente(c);
}

bool Driver::estaConectado(const Jugador & j)const {
  return jueg->EstaConectado(j);
}

Nat Driver::sanciones(const Jugador &j)const{
  return jueg->Sanciones(j);
}

Coordenada Driver::posicion(const Jugador &j)const{
  return jueg->Posicion(j);
}

Dicc <Pokemon, Nat> Driver::pokemons(const Jugador & j)const{

  Dicc <Pokemon, Nat> a;
  a.Definir("pikachu",10);
  return a;
}

////////////////////////////////////////////////////////////////////////////////
Conj <Jugador> Driver::expulsados()const{
  Conj<Jugador> a;
  return a;
}
////////////////////////////////////////////////////////////////////////////////
Pokemon Driver::pokemonEnPos(const Coordenada &c)const{
  return jueg->PokemonEnPos(c);
}

Nat Driver::cantMovimientosParaCaptura(const Coordenada &c)const{
  return jueg->CantMovimientosParaCaptura(c);
}

////////////////////////////////////////////////////////////////////////////////
bool Driver::puedoAgregarPokemon(const Coordenada & c)const{
  return true;
  //  return jueg->PuedoAgregarPokemon(c);
}
////////////////////////////////////////////////////////////////////////////////
bool Driver::hayPokemonCercano(const Coordenada & c)const{
  return jueg->HayPokemonCercano(c);
}

Coordenada Driver::posPokemonCercano(const Coordenada &c)const{
  return jueg->PosPokemonCercano(c);
}
////////////////////////////////////////////////////////////////////////////////
Conj<Jugador> Driver::entrenadoresPosibles(const Coordenada &c)const{
  Conj<Jugador> a;
  Jugador b = 10;
  a.AgregarRapido(b);
  return a;
  //return EntrenadoresPosibles(c);
}
////////////////////////////////////////////////////////////////////////////////
Nat Driver::indiceRareza(const Pokemon &p )const{
  return 0;
  //return juego.IndiceRareza(p);
}
////////////////////////////////////////////////////////////////////////////////
Nat Driver::cantPokemonsTotales()const{
  return jueg->CantPokemonTotales();
}
////////////////////////////////////////////////////////////////////////////////
Nat Driver::cantMismaEspecie(const Pokemon &p)const{
  return 10;
  //return CantMismaEspecie(p);
}
////////////////////////////////////////////////////////////////////////////////