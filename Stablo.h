#ifndef STABLO_H
#define STABLO_H
#include <utility>
#include<cstdlib>

using namespace std;

template <typename Tip>

class Stablo {
  public:
  struct Cvor {
      Tip element;
      int prioritet;
      Cvor *ld, *dd, *rod;
      Cvor(Tip el, Cvor* rod = nullptr, Cvor* ld = nullptr, Cvor* dd = nullptr):
          element(el), rod(rod), ld(ld), dd(dd) {prioritet=rand();}

    };
  private:
    int br_elem;
    Cvor* korijen;

    void obrisiStablo(Cvor* korijen);
    Cvor* kopirajStablo(Cvor* korijen, Cvor* rod_korijena, int &broj_elemenata);
    void obradiElementeRekurzivno(Cvor* korijen, void (f)(Tip)) const;
    void desnoRotiraj(Cvor* dijete,Cvor* roditelj);
    void lijevoRotiraj(Cvor* dijete,Cvor* roditelj);
    Stablo(Cvor *korijen);

  public:
    Stablo(); //konstruktor
    Stablo(const Stablo<Tip>& s); //konstruktor kopije
    Stablo(Stablo<Tip>&& s); //pomjerajuci konstruktor
    Stablo<Tip>& operator=(const Stablo<Tip>& rhs); //operator dodjele
    Stablo<Tip>& operator=(Stablo<Tip>&& rhs); //pomjerajuci operator dodjele
    ~Stablo(); //desktruktor
    bool Find(Tip el);
    void rotiraj(Cvor* cvor);
    void Insert(const Tip& element,const bool& kljuc=false);
    Cvor* nadjiCvor(const Tip& el);
    Cvor* nadjiSljedbenika(Cvor* trenutni);
    Cvor* proslijediDijete(Cvor* trenutni);
    void Delete(const Tip& element);
    void obradiElemente(void (f)(Tip)) const;

    template<typename tip>
    friend pair<Stablo<tip>,Stablo<tip>> Separate(Stablo<tip>& s,const tip& k);

};

#include "stablo.cpp"

#endif
