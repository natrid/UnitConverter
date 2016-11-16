#ifndef MUUTOS_HH
#define MUUTOS_HH

#include <string>
#include <set>
#include <map>
#include <iomanip>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Muutos
{
public:
    Muutos();
    void kaanna_muutos();
    Muutos(string mista, string mihin, double kerroin, double yleikkaus);
    Muutos(const Muutos& muutos);
    void yhdista_muutos(Muutos yhdistettava);
    void laske_muunnos(double syotettyarvo) const;
    void tulosta();    
    bool linkittyyko(const Muutos& mihin);
    bool loytyyko_muutos_vektorista(vector<string> &vektori) const;
    bool onko_kyseinen_muutos(string muutos) const;
    bool onko_kyseinen_muutos(Muutos muutos) const;


private:
    string mista_;
    string mihin_;
    double kerroin_;
    double yleikkaus_;
    string muutosnimi_;
};

#endif // MUUTOS_HH
