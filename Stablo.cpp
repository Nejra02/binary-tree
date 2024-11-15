#ifndef STABLO_CPP
#define STABLO_CPP
#include "stablo.h"
#include <iostream>
#include<utility>
using namespace std;

template <typename Tip>
Stablo<Tip>::Stablo() {
  korijen = nullptr;
  br_elem= 0;
}

template <typename Tip>
Stablo<Tip>::Stablo(Cvor *korijen) : korijen(korijen), br_elem(0) {
    if(this->korijen!=nullptr) this->korijen->rod=nullptr;
}


template <typename Tip>
void Stablo<Tip>::obrisiStablo(Cvor *korijen) {
    if(korijen == nullptr)
        return;

    if(korijen->ld != nullptr)
        obrisiStablo(korijen->ld);
    if(korijen->dd != nullptr)
        obrisiStablo(korijen->dd);

    if(korijen->rod != nullptr) {
        if(korijen->rod->ld == korijen)
            korijen->rod->ld = nullptr;
        else
            korijen->rod->dd = nullptr;
    }
    else
        this->korijen = nullptr;

    delete korijen;
    br_elem--;
}

template <typename Tip>
Stablo<Tip>::~Stablo() {
    obrisiStablo(korijen);
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::kopirajStablo(Cvor *korijen, Cvor *rod_korijena, int &broj_elemenata) {
    if(korijen == nullptr)
        return nullptr;

    Cvor *noviCvor = new Cvor(korijen->element);
    noviCvor->rod=rod_korijena;
    noviCvor->prioritet=korijen->prioritet;
    br_elem++;

    noviCvor->ld = kopirajStablo(korijen->ld, noviCvor, br_elem);
    noviCvor->dd = kopirajStablo(korijen->dd, noviCvor, br_elem);

    return noviCvor;
}

template <typename Tip>
Stablo<Tip>::Stablo(const Stablo<Tip> &stablo) : Stablo() {
    korijen = kopirajStablo(stablo.korijen, nullptr, br_elem);
}

template <typename Tip>
Stablo<Tip>::Stablo(Stablo<Tip> &&stablo) : korijen(stablo.korijen), br_elem(stablo.br_elem) {
    stablo.korijen = nullptr;
    stablo.br_elem = 0;
}

template <typename Tip>
Stablo<Tip>& Stablo<Tip>::operator=(const Stablo<Tip> &rhs) {
    if(this == &rhs)
        return *this;

    obrisiStablo(korijen);
    korijen = kopirajStablo(rhs.korijen, nullptr, br_elem);

    return *this;
}

template <typename Tip>
Stablo<Tip>& Stablo<Tip>::operator=(Stablo<Tip> &&rhs) {
    Cvor *tempKorijen = korijen;
    korijen = rhs.korijen;
    rhs.korijen = tempKorijen;

    int tempBrojElemenata = br_elem;
    br_elem = rhs.br_elem;
    rhs.br_elem = tempBrojElemenata;

    return *this;
}

template <typename Tip>
bool Stablo<Tip>:: Find(Tip el) {
    Cvor* trenutni = korijen;
    while(trenutni != nullptr) {
        if(el == trenutni->element) return true;
        if(el < trenutni->element) trenutni = trenutni->ld;
        else trenutni = trenutni->dd;
    }
    return false;
}

template <typename Tip>
void Stablo<Tip>::rotiraj(Cvor *cvor){
    if(cvor->rod==nullptr) return;
    if(cvor->rod->ld==cvor) desnoRotiraj(cvor, cvor->rod);
    else if(cvor->rod->dd==cvor) lijevoRotiraj(cvor, cvor->rod);
}

template <typename Tip>
void Stablo<Tip>::desnoRotiraj(Cvor *dijete, Cvor *roditelj){
    if(roditelj == korijen) korijen=dijete;
    else if(roditelj->rod->ld == roditelj) roditelj->rod->ld=dijete;
    else roditelj->rod->dd=dijete;
    dijete->rod=roditelj->rod;
    roditelj->rod=dijete;
    roditelj->ld=dijete->dd;
    dijete->dd=roditelj;
    if(roditelj->ld != nullptr) roditelj->ld->rod=roditelj;

}

template <typename Tip>
void Stablo<Tip>::lijevoRotiraj(Cvor *dijete, Cvor *roditelj){
    if(roditelj == korijen) korijen=dijete;
    else if(roditelj->rod->ld == roditelj) roditelj->rod->ld=dijete;
    else roditelj->rod->dd=dijete;
    dijete->rod=roditelj->rod;
    roditelj->rod=dijete;
    roditelj->dd=dijete->ld;
    dijete->ld=roditelj;
    if(roditelj->dd != nullptr) roditelj->dd->rod=roditelj;
}

template <typename Tip>
void Stablo<Tip>::Insert(const Tip &element,const bool& kljuc){
    if(korijen==nullptr){
        korijen=new Cvor(element);
        br_elem=1;

        return;
    }
    Cvor *trenutni=korijen;
    while(trenutni!=nullptr){
        if(Find(element)) return;
        else if(trenutni->element > element){
            //lijevo dijete
            if(trenutni->ld != nullptr) trenutni=trenutni->ld;
            else{
                trenutni->ld=new Cvor(element, trenutni);
                Cvor *novi=trenutni->ld;
                br_elem++;
                if(kljuc){
                    novi->prioritet=(novi->prioritet)*2;
                    while(novi != korijen) rotiraj(novi);
                }
                else while(novi != korijen && novi->prioritet > novi->rod->prioritet) rotiraj(novi);
                return;
            }
        }
        else{
            //desno dijete
            if(trenutni->dd != nullptr) trenutni=trenutni->dd;
            else{
                trenutni->dd=new Cvor(element, trenutni);
                Cvor *novi=trenutni->dd;
                br_elem++;
                if(kljuc){
                    novi->prioritet=(novi->prioritet)*2;
                    while(novi != korijen) rotiraj(novi);
                }
                else while(novi != korijen && novi->prioritet > novi->rod->prioritet) rotiraj(novi);
                return;
            }
        }
    }

}

template<typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::nadjiCvor(const Tip &el){
    Cvor* trenutni = korijen;
    while(trenutni != nullptr) {
        if(el == trenutni->element)
            return trenutni;
        if(el < trenutni->element)
            trenutni = trenutni->ld;
        else trenutni = trenutni->dd;
  }
  return nullptr;
}


template<typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::nadjiSljedbenika(Cvor *trenutni){
    Cvor* sljedbenik= trenutni->dd;
    while(sljedbenik->ld != nullptr) sljedbenik = sljedbenik->ld;
    //cout<<"SLJEDBENIK JE: "<<sljedbenik->element<<endl;
    return sljedbenik;
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::proslijediDijete(Cvor *trenutni){
    if(trenutni->ld==nullptr) return trenutni->dd;
    if(trenutni->dd==nullptr) return trenutni->ld;
    if(trenutni->ld->prioritet > trenutni->dd->prioritet) return trenutni->ld;
    else return trenutni->dd;
}

template <typename Tip>
void Stablo<Tip>::Delete(const Tip &el){
    Cvor *izbrisati = nadjiCvor(el);

    //ako nema tog elementa
    if(izbrisati==nullptr) return;
    //nema nijedno dijete
    if(izbrisati->ld == nullptr && izbrisati->dd == nullptr){
        if(izbrisati == korijen) korijen = nullptr;
        else{
            if(izbrisati->rod->ld == izbrisati) izbrisati->rod->ld = nullptr;
            if(izbrisati->rod->dd == izbrisati) izbrisati->rod->dd = nullptr;
        }
    }
    // ima jedno dijete
    //ima lijevo dijete
    else if(izbrisati->ld != nullptr && izbrisati->dd == nullptr){
        if(izbrisati == korijen){ korijen = izbrisati->ld; korijen->rod = nullptr;}
        else{
            izbrisati->ld->rod=izbrisati->rod;
            if(izbrisati->rod->ld == izbrisati) izbrisati->rod->ld = izbrisati->ld;
            else izbrisati->rod->dd = izbrisati->ld;

            if(izbrisati->ld == nullptr) izbrisati->rod->ld = nullptr;
            else if(izbrisati->dd == nullptr)izbrisati->rod->dd = nullptr;
        }

    }
    //ima desno dijete
    else if(izbrisati->ld == nullptr && izbrisati->dd != nullptr){
        if(izbrisati == korijen){ korijen = izbrisati->dd; korijen->rod = nullptr;}
        else{
            izbrisati->dd->rod=izbrisati->rod;
            if(izbrisati->rod->ld == izbrisati) izbrisati->rod->ld = izbrisati->dd;
            else izbrisati->rod->dd = izbrisati->dd;
            if(izbrisati->ld == nullptr) izbrisati->rod->ld = nullptr;
            else if(izbrisati->dd == nullptr)izbrisati->rod->dd = nullptr;
        }

    }
    //ako ima oba djeteta
    else{
        Cvor *sljedbenik=nadjiSljedbenika(izbrisati);
        //ako mijenjamo sa desnim djetetom jer desno dijete nema lijeve djece
        if(sljedbenik->rod == izbrisati){
            if(izbrisati->rod->ld == izbrisati) izbrisati->rod->ld = sljedbenik;
            else izbrisati->rod->dd = sljedbenik;

            sljedbenik->rod=izbrisati->rod;
            sljedbenik->ld = izbrisati->ld;
            izbrisati->ld->rod=sljedbenik;
        }

        //ako mijenjamo sa zadnjim lijevim koje nema djece
        else{
            if(izbrisati == korijen) korijen=sljedbenik;
            else{
                if(izbrisati->rod->ld == izbrisati) izbrisati->rod->ld = sljedbenik;
                else izbrisati->rod->dd = sljedbenik;
            }
            if(sljedbenik->dd != nullptr) sljedbenik->rod->ld = sljedbenik->dd;
            else sljedbenik->rod->ld==nullptr;
            sljedbenik->rod = izbrisati->rod;
            sljedbenik->ld = izbrisati->ld;
            sljedbenik->dd = izbrisati->dd;
            izbrisati->ld->rod=sljedbenik;
            izbrisati->dd->rod=sljedbenik;
        }
        //while(sljedbenik->ld != nullptr && sljedbenik->dd != nullptr && proslijediDijete(sljedbenik)->prioritet > sljedbenik->prioritet) rotiraj(proslijediDijete(sljedbenik));
    }
    delete izbrisati;
    br_elem--;
}


template<typename Tip>
pair<Stablo<Tip>, Stablo<Tip>> Separate(Stablo<Tip> &s,const Tip& k){
    s.Insert(k,true);
    Stablo<Tip> manji_od_k=Stablo<Tip>(s.korijen->ld);
    Stablo<Tip> veci_od_k=Stablo<Tip>(s.korijen->dd);

    s.korijen=nullptr;
    s.br_elem=0;

    return {manji_od_k,veci_od_k};


}



//COUT


template <typename Tip>
void Stablo<Tip>::obradiElementeRekurzivno(Cvor* korijen, void (f)(Tip)) const {
    if(korijen->ld!=nullptr) obradiElementeRekurzivno(korijen->ld, f);
    f(korijen->element);
    cout << "prioritet: " << korijen->prioritet << endl;
    cout<<"roditelj: ";
    if(korijen->rod != nullptr) f(korijen->rod->element);
    else cout<<endl;
    cout<<"LD: ";
    if(korijen->ld != nullptr) f(korijen->ld->element);
    else cout<<endl;
    cout<<"DD: ";
    if(korijen->dd != nullptr)f(korijen->dd->element);
    else cout<<endl;
    cout<<endl;
    if(korijen->dd!=nullptr) obradiElementeRekurzivno(korijen->dd, f);

}

template <typename Tip>
void Stablo<Tip>::obradiElemente(void (f)(Tip)) const {
    if(korijen!=nullptr){
        cout<<"Korijen je: "<<korijen->element<<endl<<endl;
        obradiElementeRekurzivno(korijen, f);
    }
}

template<typename Tip>
void ispisi(Tip e){
    cout << e << endl;
}

template <typename Tip>
ostream& operator<<(ostream &ispis, const Stablo<Tip> &s){
    s.obradiElemente(ispisi);

    return ispis;
}

#endif // STABLO_CPP

