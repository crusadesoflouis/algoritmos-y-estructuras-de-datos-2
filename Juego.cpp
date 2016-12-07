#include "Juego.h"

/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************FUNCIONES AUXILIARES****************************/
/**************************************************************************************************/
/**************************************************************************************************/


bool Juego::JugadorExistente(const Jugador j)const{
  return j<= Jugadores.Longitud();
}



Nat DistanciaEuclidea(const Coordenada c1, const Coordenada c2){
  Nat a = 0;
  Nat b = 0;
  if (c1.latitud() > c2.latitud()) {
    a = ( ( c1.latitud() - c2.latitud() ) * (c1.latitud() - c2.latitud() ) );
  }
  else
    a =  ( (c2.latitud() - c1.latitud()) * (c2.latitud() - c1.latitud()));

  if (c1.longitud() > c2.longitud())
    b =	 ( (c1.longitud() - c2.longitud()) * (c1.longitud() - c2.longitud()) );
  else
    b =  ( (c2.longitud() - c1.longitud()) * (c2.longitud() - c1.longitud()) );
  return a+b;
}

bool Juego::MovimientoInvalido(const Coordenada &c1,const Coordenada  &c2)const{
  //std::cout << "la distancia es : " <<DistanciaEuclidea(c1,c2) <<std::endl;
  return  !Mundo.HayCamino(c1,c2) || DistanciaEuclidea(c1,c2) > 100;
}

bool Juego::PuedeAtrapar (Coordenada c1,const Coordenada &c2){
  return DistanciaEuclidea(c1,c2) <= 4 &&  Mundo.HayCamino(c1,c2);
}

void Juego::ActualizarPosSalvajes(const Coordenada &c1,const Coordenada &c2, bool b,bool libre ){
//si b es verdadero, significa que no tengo que tocar ninguna de las dos coordenadas
//si no es verdadero, tengo que que usar solo la primer coordenada
Conj<Coordenada>::const_Iterador IT = PosSalvajes.CrearIt();
if (libre) {
    std::cout << "soy libre" << std::endl;

  while (IT.HaySiguiente()) {
    std::cout << "hay siguiente" << std::endl;
      FuturasCapturas.Obtener(IT.Siguiente())->Turnos ++;
      if (FuturasCapturas.Obtener(IT.Siguiente())->Turnos == 10) {
        std::cout << "entreo a capturar" << std::endl;
        Capturar(IT.Siguiente());
        std::cout << "salgo de capturar" << std::endl;
      }
      if (IT.HaySiguiente()) {
        IT.Avanzar();
      }
  }
}
else{
  if (b) {
    while (IT.HaySiguiente()) {
      if (IT.Siguiente() != c1 && IT.Siguiente() != c2) {
        FuturasCapturas.Obtener(IT.Siguiente())->Turnos ++;
      }
      if (FuturasCapturas.Obtener(IT.Siguiente())->Turnos == 10) {
        Capturar(IT.Siguiente());
      }
      IT.Avanzar();
    }
  }
  else{
    while (IT.HaySiguiente()) {
      if (IT.Siguiente()!=c1) {
        FuturasCapturas.Obtener(IT.Siguiente())->Turnos ++;
      }
      if (FuturasCapturas.Obtener(IT.Siguiente())->Turnos == 10) {
        Capturar(IT.Siguiente());
      }
      IT.Avanzar();
    }
  }

}
}



void Juego::Capturar(const Coordenada &c){
 //std::cout << "entre a capturar" << std::endl;
 InfoJug* aux = FuturasCapturas.Obtener(c)->PosiblesEntrenadores.Tope().Iter();
 //Jugador j = FuturasCapturas.Obtener(c)->PosiblesEntrenadores.Tope().Identificacion();
 aux->EstaCazando = false;
 Pokemon capturado = FuturasCapturas.Obtener(c)->Bicho;
 aux->Atrapados.Agregar(capturado);
 delete FuturasCapturas.Obtener(c);
 FuturasCapturas.Borrar(c);
 PosSalvajes.Eliminar(c);
}


void Juego::EliminarJugador(const Jugador &j){
Conj<String>::const_Iterador IT = Jugadores[j]->Atrapados.CrearIt();
  while (IT.HaySiguiente()) {
    Nat Cantidad = Jugadores[j]->Atrapados.Repeticiones(IT.Siguiente());
    Nat CanPok = Pokedex.Significado(IT.Siguiente());
    Pokedex.Borrar(IT.Siguiente());
    Nat Diferencia = CanPok - Cantidad;
    if (Diferencia != 0) {
      Pokedex.Definir(IT.Siguiente(),Diferencia);
    }
  }
}
/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************GENERADORES****************************/
/**************************************************************************************************/
/**************************************************************************************************/

Juego::Juego(Mapa &map):Mundo(map){
  TotalPokemones = 0;
  DiccMatriz < InfoPos* > mapa0(NULL);
  FuturasCapturas = mapa0;
}

Juego::~Juego(){
  for (Nat i = 0; i < Jugadores.Longitud(); i++) {
    delete Jugadores[i];
  }
  Conj<Coordenada> C = FuturasCapturas.Claves();
  Conj<Coordenada>::Iterador IT = C.CrearIt();
  while (IT.HaySiguiente()) {
     delete FuturasCapturas.Obtener(IT.Siguiente());
     IT.Avanzar();
  }

}



Jugador Juego::AgregarJugador(){
  Juego::InfoJug* nuevo = new InfoJug;
  Jugadores.AgregarAtras(nuevo);
  unsigned int ID = Jugadores.Longitud() - 1;
  return  ID;
}

void Juego::AgregarPokemon(const Coordenada &c, const Pokemon &p){
  assert(PosExistente(c));
  assert(PuedoAgregarPokemon(c));
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
  FuturasCapturas.Definir(c,info);
  Vector<InfoJug*>::const_Iterador IT = Jugadores.CrearIt();
  Nat pos = 0;
  while (IT.HaySiguiente()) {
    online = IT.Siguiente()->Conectado;
    if (online && PuedeAtrapar(c,IT.Siguiente()->Posicion)) {
      Tupla<InfoJug*> t(Jugadores[pos],IT.Siguiente()->Atrapados.Cardinal(),pos);
      FuturasCapturas.Obtener(c)->PosiblesEntrenadores.Encolar(t);
    }
    pos++;
    IT.Avanzar();
  }
  TotalPokemones ++;

}

void Juego::Conectarse(const Coordenada &c,const Jugador j){
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
  if (Jugadores[j]->EstaCazando) {
    Jugadores[j]->CazaActual.EliminarSiguiente();
  }
    if (HayPokemonCercano(Jugadores[j]->Posicion)) {
      if (FuturasCapturas.Obtener(PosPokemonCercano(Jugadores[j]->Posicion))->PosiblesEntrenadores.esVacia()) {
        FuturasCapturas.Obtener(PosPokemonCercano(Jugadores[j]->Posicion))->Turnos = 0;
       }
    }
}


void Juego::Moverse(const Coordenada &c,const Jugador j){
  assert(Sanciones(j) < 5 );
  assert(EstaConectado(j));
  std::cout << "entre moverse " << j <<std::endl;
  bool HayPokemonAlmoverme = false;
  bool HayPokemonAlEntrar = false;
  Coordenada vieja(0,0);
  Coordenada nueva(0,0);

  if (MovimientoInvalido(c,Jugadores[j]->Posicion)) {
    Jugadores[j]->Sanciones++;
    bool b = false;
    bool libre = true;
    ActualizarPosSalvajes(vieja,nueva,b,libre);
    return;
  }
if (Jugadores[j]->Sanciones < 5) {
  std::cout << "sanciones de jugador menor a 5" << std::endl;
    if (HayPokemonCercano(Jugadores[j]->Posicion)) {
    HayPokemonAlmoverme = true;
    Coordenada e(PosPokemonCercano(Jugadores[j]->Posicion).latitud(),PosPokemonCercano(Jugadores[j]->Posicion).longitud());
    vieja = e;
    }
    if (HayPokemonCercano(c)) {
      std::cout << "hay pokemon cercano en la poscion" << std::endl;
      HayPokemonAlEntrar = true;
      nueva = PosPokemonCercano(c);
    }
  //  std::cout << "pase haypokemoncercano(c)" << std::endl;
    if (HayPokemonAlEntrar && HayPokemonAlmoverme && vieja == nueva) {
    //  std::cout << "si me muevo dentro de una posicion cercana a un pokemon" << std::endl;
        bool b = false;
        bool libre = false;
        ActualizarPosSalvajes(vieja,nueva,b,libre);
    }
    else{
      std::cout << "no entre al casode que me muevo dentro del rango del pokemon" << std::endl;
      //esto implica que en la posicion nueva y vieja son distintas
      //osea puede ser que ambas sean vacias
      //o que salgo de una cola y entro a otra
      //o que de no estar en nada voy a una nueva capturas
      if (HayPokemonAlmoverme && HayPokemonAlEntrar) {
          std::cout << "si salgo de una cola y entro en otra" << std::endl;

        // caso en el que salgo de una cola y entro a otra
        Jugadores[j]->CazaActual.EliminarSiguiente();
        FuturasCapturas.Obtener(vieja)->Turnos++;
        if (FuturasCapturas.Obtener(vieja)->Turnos == 10) {
           Capturar(vieja);
        }
        FuturasCapturas.Obtener(nueva)->Turnos = 0;
        Tupla<InfoJug*> t(Jugadores[j],Jugadores[j]->Atrapados.Cardinal(),j);
        FuturasCapturas.Obtener(nueva)->PosiblesEntrenadores.Encolar(t);
        bool b = true;
        bool libre = false;
        ActualizarPosSalvajes(nueva,vieja,b,libre);
      }
      else{
          std::cout << "salgo de una cola a una posicion libre o vole libre" << std::endl;
          //salgo de una posicion con pokemon a un lugar donde no hay pokemon
          if (HayPokemonAlmoverme) {
        //    std::cout << "salgo de una cola " << std::endl;
            Jugadores[j]->CazaActual.EliminarSiguiente();
        //    std::cout << "se rompio" << std::endl;
            bool b = true;
            bool libre = true;
            ActualizarPosSalvajes(nueva,vieja,b,libre);
          }
          else{
            if (HayPokemonAlEntrar) {
              std::cout << "entro a una posición con un pokemon y lo encolado" << std::endl;              FuturasCapturas.Obtener(nueva)->Turnos = 0;
              Tupla<InfoJug*> t(Jugadores[j],Jugadores[j]->Atrapados.Cardinal(),j);
              FuturasCapturas.Obtener(nueva)->PosiblesEntrenadores.Encolar(t);
              bool b = false;
              bool libre = false;
              ActualizarPosSalvajes(nueva,vieja,b,libre);
            }
            else{
              std::cout << "vole libre" << std::endl;
              Jugadores[j]->Posicion = c;
              bool b = false;
              bool libre = true;
              std::cout << "antes de actualizar pos salvajes" << std::endl;
              ActualizarPosSalvajes(nueva,vieja,b,libre);
            }
          }
      }
    }
  }
  else{
    EliminarJugador(j);
  }
}


/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************OBSERVADORES****************************/
/**************************************************************************************************/
/**************************************************************************************************/

Mapa Juego::MAPA(){
  return Mundo;
}

bool Juego::HayCamino(const Coordenada &c1,const Coordenada &c2){
  return Mundo.HayCamino(c1,c2);
}

bool Juego::PosExistente(const Coordenada &c1){
  return Mundo.PosExistente(c1);
}


bool Juego::EstaConectado(const Jugador j){
  assert(JugadorExistente(j));
  return Jugadores[j]->Conectado;
}

Nat Juego::Sanciones(const Jugador j){
  return Jugadores[j]->Sanciones;
}

Coordenada Juego::Posicion(const Jugador j){
  return Jugadores[j]->Posicion;
}


Coordenada Juego::PosPokemonCercano(const Coordenada &c){
  Conj<Coordenada>::Iterador IT = PosSalvajes.CrearIt();
  while (IT.HaySiguiente() && DistanciaEuclidea(c,IT.Siguiente()) > 4) {
      IT.Avanzar();
  }
  return IT.Siguiente();

}

Conj <Jugador> Juego::EntrenadoresPosibles(const Coordenada &c, const Conj<Jugador> &muestra){
  Conj <Jugador> ConjDeJugadores;

//  Lista < Tupla <InfoJug*> > entrenadores = FuturasCapturas.Obtener(c)->PosiblesEntrenadores.Elementos();
/*
  Lista < Tupla <InfoJug*> >::Iterador IT = entrenadores.CrearIt();

  while (IT.HaySiguiente()) {
    std::cout << "El jugador es: " <<IT.Siguiente().Identificacion() <<std::endl;
    IT.Avanzar();
  }
  */
  return ConjDeJugadores;
}

Conj< Coordenada > Juego::posConPokemons() const{
  return PosSalvajes;
}


//falta iterador a Posiciones salvajes

//falta iterador a Expulsados

/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************OTRAS OPERACIONES****************************/
/**************************************************************************************************/
/**************************************************************************************************/

Conj<Coordenada> Juego::ObtenerPosicionesCercanas(const Coordenada c){
  Conj<Coordenada> Posiciones;
  /*
  Conj<Coordenada>::const_Iterador IT = PosicionesValidas();
  while (IT.HaySiguiente()) {
    //std::cout << "la distancia a : " << IT.Siguiente().latitud() <<"," << IT.Siguiente().longitud()<< ")"<< "es:"<<DistanciaEuclidea(c,IT.Siguiente()) <<std::endl;
    if (DistanciaEuclidea(c,IT.Siguiente()) <= 4) {
      Posiciones.AgregarRapido(IT.Siguiente());
    }
    IT.Avanzar();
  }*/
   return Posiciones;
}

Conj<Coordenada> Juego::ObtenerPosicionesCercanas_25(const Coordenada c){
  Conj<Coordenada> Posiciones;

  Conj<Coordenada>::const_Iterador IT = PosSalvajes.CrearIt();
  while (IT.HaySiguiente()) {
    //std::cout << "la distancia a : " << IT.Siguiente().latitud() <<"," << IT.Siguiente().longitud()<< ")"<< "es:"<<DistanciaEuclidea(c,IT.Siguiente()) <<std::endl;
    if (DistanciaEuclidea(c,IT.Siguiente()) <= 25) {
      Posiciones.AgregarRapido(IT.Siguiente());
    }
    IT.Avanzar();
  }
   return Posiciones;
}

Conj <Jugador> Juego::Expulsados(){
  Conj <Jugador> expulsados;
  Juego::Iterador_Exp IT = CrearIt_Exp();
  while (IT.HaySiguiente()) {
    std::cout << "el jugador expulsado es: " <<IT.Siguiente() <<std::endl;
    expulsados.Agregar(IT.Siguiente());
    IT.Avanzar();
  }

return expulsados;
}

Conj <Jugador> Juego::jugadores(){
  Conj <Jugador> jugadores;
  Juego::Iterador IT = CrearIt();
  while (IT.HaySiguiente()) {
    jugadores.Agregar(IT.Siguiente());
    IT.Avanzar();
  }
  return jugadores;
}


bool Juego::HayPokemonCercano(const Coordenada &c){
Conj<Coordenada>::const_Iterador IT = PosSalvajes.CrearIt();
while (IT.HaySiguiente()) {
  if (DistanciaEuclidea(c,IT.Siguiente()) <= 4  ) {
    return true;
  }
  IT.Avanzar();
}
  return false;
}



bool Juego::PuedoAgregarPokemon(const Coordenada &c){
  Conj<Coordenada>::const_Iterador IT = PosSalvajes.CrearIt();
  while (IT.HaySiguiente()) {
  //  std::cout << IT.Siguiente().longitud() <<"," <<IT.Siguiente().latitud()<<std::endl;
  //  std::cout << "la distancia es " << DistanciaEuclidea(c,IT.Siguiente()) <<std::endl;
    if (DistanciaEuclidea(c,IT.Siguiente()) <= 24) {
      return false;
    }
    IT.Avanzar();
  }
  return PosExistente(c);
}


Nat Juego::IndiceRareza(const Pokemon &p){
  Nat TipoPokemon = Pokedex.Significado(p);
  Nat Total = TotalPokemones;
  return TipoPokemon* 100 / Total;
}


Nat Juego::CantPokemonTotales(){
  return TotalPokemones;
}



Dicc< Pokemon , Nat > Juego::Pokemons(const Jugador j){
  Conj<String>::const_Iterador IT = Jugadores[j]->Atrapados.CrearIt();
  Dicc <Pokemon, Nat> a;
  while (IT.HaySiguiente()) {
    Nat cantidad = Jugadores[j]->Atrapados.Repeticiones(IT.Siguiente());
    a.Definir(IT.Siguiente(),cantidad);
    IT.Avanzar();
  }
  return a;
}

Nat Juego::cantMismaEspecie(const Pokemon &p)const{
  return Pokedex.Significado(p);
}

Pokemon Juego::PokemonEnPos (const Coordenada &c){
  return FuturasCapturas.Obtener(c)->Bicho;
}

Nat Juego::CantMovimientosParaCaptura(const Coordenada &c){
  return  FuturasCapturas.Obtener(c)->Turnos ;
}


/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************ITERADOR****************************/
/**************************************************************************************************/
/**************************************************************************************************/


typename Juego::Iterador Juego::CrearIt() {
  return Iterador(this);
}

bool Juego::Iterador::HaySiguiente(){
  unsigned int guarda = juego->Jugadores.Longitud();
  if (Posicion > guarda) {
    return false;
  }
  else{
    while (Posicion < guarda && juego->Jugadores[Posicion]->Sanciones > 4) {
      Posicion++;
    }
    if (Posicion < guarda) {
      return true;
    }
    return false;
}
}

void Juego::Iterador::Avanzar(){
  assert(HaySiguiente());
  Posicion++;
}

Jugador Juego::Iterador::Siguiente(){
  assert(HaySiguiente());
  return Posicion;
}


//*******************************Iterador expulsados*************************/
typename Juego::Iterador_Exp Juego::CrearIt_Exp(){
  return Iterador_Exp(this);
}

bool Juego::Iterador_Exp::HaySiguiente(){
  unsigned int guarda = juego->Jugadores.Longitud();
  if (Posicion > guarda) {
    return false;
  }
  else{
    while (Posicion < guarda && juego->Jugadores[Posicion]->Sanciones < 4) {
      Posicion++;
    }
    if (Posicion < guarda) {
      return true;
    }
    return false;
}
}

void Juego::Iterador_Exp::Avanzar(){
  assert(HaySiguiente());
  Posicion++;
}

Jugador Juego::Iterador_Exp::Siguiente(){
  assert(HaySiguiente());
  return Posicion;
}
