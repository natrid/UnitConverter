#include "muutos.hh"
#include <string>
#include <set>
#include <map>
#include <iomanip>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

//oletusrakentaja
Muutos::Muutos(){

}

//Metodi muokkaa muutosta siten että se vastaa vastakkaista muutosta
void Muutos::kaanna_muutos(){
    string valiaikainen = this->mihin_;
    mihin_=this->mista_;
    mista_ =valiaikainen;
    double valiaikainenkerroin = this->kerroin_;
    kerroin_= (double)1/this->kerroin_;
    yleikkaus_=-(this->yleikkaus_/valiaikainenkerroin);
    muutosnimi_ = mista_+" "+mihin_;
}

//Rakentaja muutokselle
Muutos::Muutos(string mista, string mihin, double kerroin, double yleikkaus):
    mista_{mista},
    mihin_{mihin},
    kerroin_{kerroin},
    yleikkaus_{yleikkaus}
{
    string muutosnimi = mista + " "+ mihin;
    //cout << muutosnimi << endl;
    muutosnimi_ = muutosnimi;
}

//Kopiorakentaja ÄLÄ KOSKE
Muutos::Muutos(const Muutos &muutos){
    mista_ = muutos.mista_;
    mihin_ = muutos.mihin_;
    kerroin_ = muutos.kerroin_;
    yleikkaus_ = muutos.yleikkaus_;
    muutosnimi_ = muutos.muutosnimi_;
}


//Metodi yhdistää muutokseen toisen muutoksen
void Muutos::yhdista_muutos(Muutos yhdistettava){
    mihin_ = yhdistettava.mihin_;
    kerroin_ = kerroin_ * yhdistettava.kerroin_;
    yleikkaus_ = yleikkaus_ + yhdistettava.yleikkaus_;
    muutosnimi_ = mista_+" "+yhdistettava.mihin_;
}

//Funktio tulostaa muutetun arvon
void Muutos::laske_muunnos(double syotettyarvo) const{
    double tulos;
    tulos = (syotettyarvo * kerroin_) + yleikkaus_;
    cout << fixed << setprecision(3) << tulos << endl;
}

//Funktio tulostaa kaavan
void Muutos::tulosta(){
    cout << mista_ << "<=" << kerroin_  << "*" << mihin_<< yleikkaus_ << endl;
}

//Funktio tarkastelee muutosten linkkiytymistä
//Jos tosi niin muutokset voidaan yhdistää
bool Muutos::linkittyyko(const Muutos& mihin){
    if((mihin_ == mihin.mista_) && (mista_ != mihin.mihin_)) return true;
    return false;
}

//Metodi etsii muutosta annetusta vektorista ja palauttaa toden täydennetyn vektorin jos muutos löytyy
bool Muutos::loytyyko_muutos_vektorista(vector<string>& vektori) const{
    for (auto& iter : vektori){
        if(iter==muutosnimi_)return false;
    }
    vektori.push_back(muutosnimi_);
    return true;
}

//Metodi tarkistaa onko kyseinen muutos haluttu muutos
bool Muutos::onko_kyseinen_muutos(string muutos) const{
    if(muutosnimi_ == muutos)return true;
    return false;
}

//Metodi tarkistaa onko kyseinen muutos haluttu muutos
bool Muutos::onko_kyseinen_muutos(Muutos muutos) const{
    if(muutosnimi_ == muutos.muutosnimi_)return true;
    return false;
}
