#include <iostream>
#include <cassert>
#include "aed2.h"
#include "TiposJuego.h"
#include "MultiC.h"
#include "Mapa.h"
#include "Cola.h"
#include "Tupla.h"

using namespace std;
  class Juego{
    public:
      class Iterador;

      class Iterador_Exp;

      Iterador CrearIt();

      Iterador_Exp CrearIt_Exp();

      Juego();
      Juego(Mapa &map);
      ~Juego();
      //
      void AgregarPokemon(coordenada c, const Pokemon &p);
      //
      Jugador AgregarJugador();
      //
      void Conectarse(const coordenada &c,const Jugador j);
      //
      void Desconectarse(const Jugador j);
      //
      void Moverse(const coordenada &c, const Jugador j);
      //
      Mapa MAPA();

      typename Conj<String>::const_Iterador Pokemons(const Jugador j);

      bool HayCamino(const coordenada &c1, const coordenada &c2);
      //IteradorJug Jugadores();

      bool PosExistente(const coordenada &c1);

      bool EstaConectado(const Jugador j);
      //
      Nat Sanciones(const Jugador j);
      //
      coordenada Posicion (const Jugador j);
      //**********************************************************************************************************************
      //IteradorMulticonjunto<Pokemon> Pokemons(const Jugador j);
      //**********************************************************************************************************************
      //revisar estos iteradores //it al conjunto de jugadores expulsados
      //Conj<Jugador>::IteradorExp Expulsados();
      //

      Pokemon PokemonEnPos(const coordenada &c);

      Nat CantMovimientosParaCaptura(const coordenada &c);

      bool PuedoAgregarPokemon(const coordenada &c);

      bool HayPokemonCercano(const coordenada &c);

      coordenada PosPokemonCercano(const coordenada &c);

      Conj<Jugador> Expulsados();

      Conj<coordenada> posConPokemons()const;

      Conj<Jugador> EntrenadoresPosibles(const coordenada &c, const Conj<Jugador> &JugPosibeles);

      Nat IndiceRareza (const Pokemon &p);

      Nat CantPokemonTotales();

      Nat cantMismaEspecie(const Pokemon &p)const;

        class Iterador{

          public:

            Iterador();
            bool HaySiguiente();
            Jugador Siguiente();
            void Avanzar();
          private:
            Juego* juego;
            unsigned int Posicion;
            Iterador(Juego* j,Nat p = 0):juego(j),Posicion(p){}
            friend typename Juego::Iterador Juego::CrearIt();
      };
      class Iterador_Exp{

        public:

          Iterador_Exp();
          bool HaySiguiente();
          Jugador Siguiente();
          void Avanzar();
        private:
          Juego* juego;
          unsigned int Posicion;
          Iterador_Exp(Juego * j,Nat p = 0):juego(j),Posicion(p){}
          friend typename Juego::Iterador_Exp Juego::CrearIt_Exp();
    };

        //iterador expulsados idem a Iterador pero con los expulsados//

        ///*****************estructura*******///
      private:

        bool PuedeAtrapar(coordenada c1,const coordenada &c2);
        void Capturar(const coordenada &c);
        Conj<coordenada> ObtenerPosicionesCercanas(const coordenada c);
        void EliminarJugador(const Jugador &j);
        struct InfoJug{
          Nat Sanciones;
          bool Conectado;
          coordenada Posicion;
          MultiC Atrapados;
          bool EstaCazando;
          Cola<Jugador>::Iterador CazaActual;
          InfoJug():Sanciones(0),Conectado(false),Posicion(0,0){}

        };

        struct InfoPos{
          Nat Turnos;
          Cola< Tupla <InfoJug*> > PosiblesEntrenadores;
          Pokemon Bicho;

          InfoPos(const Pokemon &p):Turnos(0){
            Bicho = p;}
        };


        Mapa Mundo;
        //conjunto con todos los jugadores incluso los expulsados
        Vector<InfoJug*> Jugadores;
        //conjunto con todas las posiciones con pokemones
        Conj<coordenada> PosSalvajes;
        // capaz que hay que hacer otra clase
        // especializando el template diccS en Nat
        //diccionario clave pokemon significado cantidad de dicha especie
        //este diccionario  debe poder eliminar creo
        DiccS<Nat> Pokedex;
        //"cardinal" de la cantidad de pokemones
        Nat TotalPokemones;
        //futuras capturas "mapa" con punteros a los heaps
        //donde estan los jugadores esperando
        DiccMatriz<InfoPos*> FuturasCapturas;
};
