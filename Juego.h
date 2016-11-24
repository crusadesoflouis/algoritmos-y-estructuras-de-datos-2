#include <iostream>
#include "aed2.h"
#include "TiposJuego.h"
#include "Mapa.h"
#include "MultiC.h"
#include "Cola.h"

using namespace std;
  class Juego{
    public:

      Juego();

      ~Juego();

      void AgregarPokemon(const Coordenada &c, const Pokemon &p);

      Jugador AgregarJugador();

      void Conectarse(const Coordenada &c,const Jugador j);

      void Desconectarse(const Jugador j);

      void Moverse(const Coordenada, const Jugador j);

      Mapa MAPA();

      Conj<Jugadores> Jugadores();

      bool EstaConectado(const Jugador j);

      Nat Sanciones(const Jugador j);

      Coordenada Posicion (const Jugador j);
      //revisar este iterador
      IteradorMulticonjunto<pokemon> Pokemons(const Jugador j);
      //revisar estos iteradores //it al conjunto de jugadores expulsados
      ItExpulsados<Jugadores> Expulsados();

      Conj<Coordenada> PosConPokemons();

      Pokemon PokemonEnPos(Const Coordenada &c);

      Nat CantMovimientosParaCaptura(const Coordenada &c);

      bool PuedoAgregarPokemon(const Coordenada &c);

      bool HayPokemonCercano(const Coordenada &c);

      Coordenada PosPokemonCercano(const Coordenada &c);

      Conj<Jugador> EntrenadoresPosibles<const Coordenada &c, const Conj<Jugador> &JugPosibeles);

      Nat IndiceRareza (const Pokemon p);

      Nat CantPokemonTotales();

      Nat CantidadMismaEspecie(const Pokemon p, Multicojunto<Pokemon>);

      IteradorJug;

      IteradorJug CrearIt();

      IteradorExp CrearIt();
        class IteradorJug{

          public:

            bool HaySiguiente();
            void Siguiente();
            void Avanzar();

          private:

          //***************//
          //***definirestr*//
          //***************//
      };

      class IteradorExp{

      public:

        bool HaySiguiente();
        void Siguiente();
        void Avanzar();
      private:

            //***************//
            //***definirestr*//
            //***************//
        };

      ///*****************estructura*******///

      Mapa Mundo;
      Vector<InfoJug*> Jugadores;
      Conj<Coordenada> PosSalvajes;
      //hay que hacer otra clase//
      MultiC Pokedex




  };
