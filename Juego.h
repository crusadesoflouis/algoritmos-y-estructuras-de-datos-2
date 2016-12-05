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
      void AgregarPokemon(const Coordenada &c, const Pokemon &p);
      //
      Jugador AgregarJugador();
      //
      void Conectarse(const Coordenada &c,const Jugador j);
      //
      void Desconectarse(const Jugador j);
      //
      void Moverse(const Coordenada &c, const Jugador j);
      //
      Mapa MAPA();

      typename Conj<String>::const_Iterador Pokemons(const Jugador j);
      //
      bool HayCamino(const Coordenada &c1, const Coordenada &c2);
      //IteradorJug Jugadores();

      bool PosExistente(const Coordenada &c1);

      bool EstaConectado(const Jugador j);
      //
      Nat Sanciones(const Jugador j);
      //
      Coordenada Posicion (const Jugador j);
      //**********************************************************************************************************************
      //IteradorMulticonjunto<Pokemon> Pokemons(const Jugador j);
      //**********************************************************************************************************************
      //revisar estos iteradores //it al conjunto de jugadores expulsados
      //Conj<Jugador>::IteradorExp Expulsados();
      //

      Pokemon PokemonEnPos(const Coordenada &c);

      Nat CantMovimientosParaCaptura(const Coordenada &c);

      bool PuedoAgregarPokemon(const Coordenada &c);

      bool HayPokemonCercano(const Coordenada &c);

      Coordenada PosPokemonCercano(const Coordenada &c);

      Conj<Jugador> Expulsados();

	    Conj< Coordenada > posConPokemons() const;

      Conj<Jugador> EntrenadoresPosibles(const Coordenada &c, const Conj<Jugador> &muestra);

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

        bool PuedeAtrapar(Coordenada c1,const Coordenada &c2);
        void Capturar(const Coordenada &c);
        void EliminarJugador(const Jugador &j);
        Conj<Coordenada> ObtenerPosicionesCercanas(const Coordenada c);
        Conj<Coordenada> ObtenerPosicionesCercanas_25(const Coordenada c);
        Conj<Coordenada> PosicionesValidas()const;
        struct InfoJug{
          Nat Sanciones;
          bool Conectado;
          Coordenada Posicion;
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

        bool JugadorExistente(const Jugador j)const;
        bool MovimientoInvalido(const Coordenada &c1,const Coordenada &c2)const;
        void ActualizarPosSalvajes(const Coordenada &c1, const Coordenada &c2, bool b,bool libre);
        Mapa Mundo;
        //conjunto con todos los jugadores incluso los expulsados
        Vector<InfoJug*> Jugadores;
        //conjunto con todas las posiciones con pokemones
        Conj<Coordenada> PosSalvajes;

        Conj<Coordenada> Ayuda;
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
