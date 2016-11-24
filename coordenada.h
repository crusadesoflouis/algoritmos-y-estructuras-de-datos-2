class coordenada {


  public:

    coordenada(Nat lat, Nat lon);

    bool operator == (coordenada& c2);

    bool operator != (coordenada& c2);

    Nat cuadRestaLat (const coordenada& c1, const coordenada& c2);

    Nat cuadRestaLong (const coordenada& c1 , const coordenada& c2);

    Nat distEuclidea(const coordenada& c1 , const coordenada& c2 );

    Nat latitud()const;
    Nat longitud()const ;

  private:
    Nat latitu;
    Nat longitu;

};
