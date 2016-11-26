#include <iostream>
#include "aed2.h"
#include "TiposJuego.h"
#include "MultiC.h"
#include "Mapa.h"
#include "DiccMatriz.h"
#include "Cola.h"

using namespace std;
  class Juego{
    public:

      Juego();

      ~Juego();

      void AgregarPokemon(const coordenada &c, const Pokemon &p);

      Jugador AgregarJugador();

      void Conectarse(const coordenada &c,const Jugador j);

      void Desconectarse(const Jugador j);

      void Moverse(const coordenada, const Jugador j);

      Conj<coordenada> MAPA();

      Conj<Jugador> Jugadores();

      bool EstaConectado(const Jugador j);

      Nat Sanciones(const Jugador j);

      coordenada Posicion (const Jugador j);
      //**********************************************************************************************************************
      //IteradorMulticonjunto<Pokemon> Pokemons(const Jugador j);
      //**********************************************************************************************************************
      //revisar estos iteradores //it al conjunto de jugadores expulsados
      //Conj<Jugador>::IteradorExp Expulsados();

      Conj<coordenada> PosConPokemons();

      Pokemon PokemonEnPos(const coordenada &c);

      Nat CantMovimientosParaCaptura(const coordenada &c);

      bool PuedoAgregarPokemon(const coordenada &c);

      bool HayPokemonCercano(const coordenada &c);

      coordenada PosPokemonCercano(const coordenada &c);

      Conj<Jugador> EntrenadoresPosibles(const coordenada &c, const Conj<Jugador> &JugPosibeles);

      Nat IndiceRareza (const Pokemon p);

      Nat CantPokemonTotales();
//revisar funcion
      //Nat CantidadMismaEspecie(const Pokemon p, MultiC<Pokemon>);


      // no me reconoce el nombre del iterador, será porque le falta la estructura?
      /*
       Juego::IteradorJug CrearIt();

       Juego::IteradorExp CrearIt();
*/
        //******************** Los iteradores van a ser renombres por ahora***************************//
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
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///*****************estructura*******///
      private:

        struct InfoJug{
          Nat Sanciones;
          bool Conectado;
          coordenada Posicion;
          MultiC Atrapados;
          
        };

        struct InfoPos{
          Nat Turnos;
          Cola<Jugador> PosiblesEntrenadores;
          Pokemon Bicho;

          InfoPos(const Pokemon &p):Turnos(10){
            Bicho = p;}
        };


        Mapa Mundo;
        //conjunto con todos los jugadores incluso los expulsados
        Vector<InfoJug*> Jugadores_Totales;
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



        //*************************************************************************************************//
      //******************Estructura provisoria*****//
      /*
        Conj<coordenada> Mundo;
        Vector<InfoJug*> Jugadores;
        Conj<coordenada> PosSalvajes;
        Conj<InfoPos*> FuturasCapturas;

        struct InfoJug{

          Nat Sanciones;
          bool conectado;
          coordenada Ubicacion;
          Lista<Pokemon> Atrapados;
          Lista<Jugador> CazaActual;
        };

        struct InfoPos{

          Nat Turnos;
          Lista<jugador> PosiblesEntrenadores;
          Pokemon Bicho;
        };


*/


};
