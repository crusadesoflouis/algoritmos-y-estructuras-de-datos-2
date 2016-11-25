

//generadores
Juego::Juego():TotalPokemones(0){}

Juego::~Juego(){}
//puede ser que no tenga que pasar por lista de inicializacion
//a turnos porque reconoce a 10 como integer y turnos es Nat
//quizas el compilador no entiende como convertir de int to nat
Juego::InfoJug::InfoPos(const Pokemon &p):Turnos(10){
  Bicho = p;}


Juego::AgregarPokemon(const Coordenada &c, const Pokemon &p){
//agrego el pokemon en el mc donde estan las pos de pokemones salvajes
PosSalvajes.AgregarRapido(c);
// si estaba definido aumento en 1 su "cardinal" sino lo defino
  if (Pokedex.Definido(p)) {
      Nat valorAnterio = Pokedex.Significado(p);
      valorAnterio++;
      Pokedex.Eliminar(p);
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
  Infopos* info = new InfoJug(p);
  Nat CantidadAtrapados = 0;
  bool online = false;
  //creo un iterador al vector donde estan todos los jugadores
  Vector<InfoJug*>::Iterador IT = Jugadores.CrearIt();


}
