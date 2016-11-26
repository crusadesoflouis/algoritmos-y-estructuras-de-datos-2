#include "DiccString.h"
#include <iostream>

class MultiC{
  public:

    //constructor y destructor

    //no es necesario declararlos???
    MultiC();

    ~MultiC();

    //Generadores
    bool Vacia();

    void Agregar(const String k);

    bool Definido(const String k);
    //otras operaciones
    Nat Cardinal() const;

    Nat Repeticiones(const String k) const;

    typename Conj<String>::const_Iterador CrearIt() const;

    
/*


  	class Iterador;
    //operaciones del Iterador

    typename Conj<String>::const_Iterador CrearIt();

    bool HaySiguiente(const typename Conj<String>::const_Iterador)const;

    void Avanzar (typename Conj<String>::const_Iterador);

    String Siguiente(typename Conj<String>::const_Iterador);



    class Iterador{
      public:
        Iterador();

        bool HaySiguiente() const;

        Nat Siguiente() const;

      private:
        DiccS<Nat>* tree;


        //definir que el iterador es el iterador del diccS
        //typename Conj<String>::const_Iterador CrearIt() const;


      };
*/
  private:
    DiccS<Nat> trie;
    Nat cardinalidad;

};
