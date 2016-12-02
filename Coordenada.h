class Coordenada {


  public:

    Coordenada(Nat lat, Nat lon);

    bool operator == (const Coordenada& c2)const;

    bool operator != (const Coordenada& c2) const;

    Coordenada operator = (const Coordenada& c2);

    Nat cuadRestaLat (const Coordenada& c2);

    Nat cuadRestaLong (const Coordenada& c2);

    Nat distEuclidea(const Coordenada& c2);

    Nat latitud()const;
    Nat longitud()const;

  private:
    Nat latitu;
    Nat longitu;

};
