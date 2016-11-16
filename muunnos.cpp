#include "muunnos.hh"
#include <string>
#include <set>
#include <map>
#include <vector>
#include <iomanip>
#include <algorithm>


//Oletusrakentaja
Muunnos::Muunnos()
{
}

//Metodi lisää muunnoksen stl säiliöön
//palautuva totuusarvo kertoo onnistuiko lisäys
bool Muunnos::lisaa_kaava(string mista, string mihin, double kerroin, double yleikkaus){
    Muutos uusimuutos = Muutos(mista,mihin,kerroin,yleikkaus);
    Muutos toinensuunta = Muutos(mihin,mista,((double)1/kerroin),-(yleikkaus/kerroin));

    //if(not uusimuutos.loytyyko_muutos_vektorista(muunnostyypit_)) return false;
    if(loytyyko_muutos(uusimuutos)) return false;
    muunnokset_.push_back(uusimuutos);
    //if(not toinensuunta.loytyyko_muutos_vektorista(muunnostyypit_)) return false;
    if(loytyyko_muutos(toinensuunta)) return false;
    muunnokset_.push_back(toinensuunta);
    return true;
}

//Metodi lisää muutos-kaavan muunnos olioon
bool Muunnos::lisaa_kaava(Muutos muutos){    
    if(loytyyko_muutos(muutos)) return false;
    muunnokset_.push_back(muutos);

    Muutos toinensuunta{muutos};
    toinensuunta.kaanna_muutos();
    if(loytyyko_muutos(toinensuunta)) return false;
    muunnokset_.push_back(toinensuunta);
    return true;
}

//Metodi yhdistelee kaavat
void Muunnos::yhdista_linkittyvat_kaavat(){
    int edellinenkoko = 0;
    while(muunnokset_.size() > edellinenkoko){
        edellinenkoko = muunnokset_.size();
        vector<Muutos> kopio = muunnokset_;
        vector<Muutos>::iterator iter;
        iter = kopio.begin();
        while(iter != kopio.end()){
            //        iter->tulosta();
            vector<Muutos>::iterator iter2;
            iter2 = kopio.begin();
            while(iter2 != kopio.end()){
                if(iter->linkittyyko(*iter2)){
                    Muutos mista{*iter};
                    Muutos mihin{*iter2};
                    mista.yhdista_muutos(mihin);
                    this->lisaa_kaava(mista);
                }
                ++iter2;
            }
            ++iter;
        }
    }
}

//Funktio tulostaa kaavat
void Muunnos::tulosta_kaavat(){
    vector<Muutos>::iterator iter;
    iter = muunnokset_.begin();
    while(iter != muunnokset_.end()){
        iter->tulosta();
        ++iter;
    }
}

//Funktio tarkistaa muutoksen löytyvyyden ja palauttaa toden jos muutos on olemassa.
bool Muunnos::loytyyko_muutos(string etsittavamuutos){
    vector<Muutos>::iterator veciter;
    veciter = muunnokset_.begin();
    while ( veciter != muunnokset_.end() ) {
        if (veciter->onko_kyseinen_muutos(etsittavamuutos)){
            return true;
        }
        ++veciter;
    }
    return false;
}

//Funktio tarkistaa muutoksen löytyvyyden ja palauttaa toden jos muutos on olemassa.
bool Muunnos::loytyyko_muutos(Muutos etsittavamuutos){
    vector<Muutos>::iterator veciter;
    veciter = muunnokset_.begin();
    while ( veciter != muunnokset_.end() ) {
        if (veciter->onko_kyseinen_muutos(etsittavamuutos)){
            return true;
        }
        ++veciter;
    }
    return false;
}
//Metodi laskee muunnoslaskun
void Muunnos::laske_muunnos(string muunnos, double syote){
    vector<Muutos>::iterator veciter;
    veciter = muunnokset_.begin();
    while ( veciter != muunnokset_.end() ) {
        if (veciter->onko_kyseinen_muutos(muunnos)){
            veciter->laske_muunnos(syote);
            return;
        }
        ++veciter;
    }
}
