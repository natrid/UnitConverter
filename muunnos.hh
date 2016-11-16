#ifndef MUUNNOS_HH
#define MUUNNOS_HH

#include <string>
#include <set>
#include <map>
#include <iomanip>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "muutos.hh"

using namespace std;

//Nimenä muunnos on huono mutta se tarkoittaa muunnoslistaa
class Muunnos
{
public:
    Muunnos();
    bool lisaa_kaava(string mista, string mihin, double kerroin, double yleikkaus);
    bool lisaa_kaava(Muutos muutos);
    void yhdista_linkittyvat_kaavat();
    void tulosta_kaavat();
    bool loytyyko_muutos(string etsittavamuutos);
    bool loytyyko_muutos(Muutos etsittavamuutos);
    void laske_muunnos(string muunnos, double syote);

private:
    vector<Muutos> muunnokset_;
    //vector<string> muunnostyypit_;
    //set<Muutos> muunnokset2_;
};

#endif // MUUNNOS_HH
