class coordenada {


  public:

    coordenada(Nat lat, Nat lon);

    bool operator == (const coordenada& c2)const;

    bool operator != (const coordenada& c2) const;

    coordenada operator = (const coordenada& c2);

    Nat cuadRestaLat (const coordenada& c1, const coordenada& c2);

    Nat cuadRestaLong (const coordenada& c1 , const coordenada& c2);

    Nat distEuclidea(const coordenada& c1 , const coordenada& c2 );

    Nat latitud()const;
    Nat longitud()const ;

  private:
    Nat latitu;
    Nat longitu;

};
