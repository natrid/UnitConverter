#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "muunnos.hh"
#include <algorithm>
#include "kayttoliittyma.hh"

using namespace std;

//Funktio lukee muunnostiedot tiedoston ja lisää siitä kaavat muunnokseen
bool lue_muunnostiedosto(const string& muunnostiedoston_nimi, Muunnos& muunnos) {
    ifstream tiedosto_olio{muunnostiedoston_nimi};
    if ( not tiedosto_olio ) {
        cout << "Virhe: muunnostiedostoa ei saanut avattua." << endl;
        return false;
    }

    string rivi;
    while ( getline(tiedosto_olio, rivi) ) {
        string::size_type yksikkoerottimen_paikka;
        string::size_type kommentoinnin_paikka;
        string::size_type kerroinerottimen_paikka;
        string::size_type miinuserottimen_paikka;
        string::size_type pluserottimen_paikka;

        string rivin_data;
        double pituuskertoimelle;
        double mistayksikonpituus;
        double yleikkaus = 0;

        string mista;
        string mihin;
        double kerroinnumerona;
        string kerroin;

        kommentoinnin_paikka = rivi.find_first_of('#');

        if ( kommentoinnin_paikka != string::npos ) {
            rivin_data = rivi.substr(0, kommentoinnin_paikka);
            rivin_data.erase(remove_if(rivin_data.begin(), rivin_data.end(), ::isspace), rivin_data.end());
            if (rivin_data.empty()) continue;
        }
        else {
            rivin_data = rivi;
        }

        //poistetaan välilyönnit rivin_data:sta
        rivin_data.erase(remove_if(rivin_data.begin(), rivin_data.end(), ::isspace), rivin_data.end());
        if (rivin_data.empty()) continue;
        miinuserottimen_paikka = rivin_data.find('-');
        pluserottimen_paikka = rivin_data.find('+');
        yksikkoerottimen_paikka = rivin_data.find("<=");
        kerroinerottimen_paikka = rivin_data.find('*');
        pituuskertoimelle = kerroinerottimen_paikka - yksikkoerottimen_paikka-2;

        //käsitellään tapaus jolloin haluttu muutos sisältää miinusmerkin
        if ( miinuserottimen_paikka != string::npos) {

            mistayksikonpituus = miinuserottimen_paikka - kerroinerottimen_paikka-1;

            string plusvaimiinus;

            mihin = rivin_data.substr(0, yksikkoerottimen_paikka);
            kerroin = rivin_data.substr(yksikkoerottimen_paikka + 2, pituuskertoimelle);
            kerroinnumerona = stod(kerroin);
            mista = rivin_data.substr(kerroinerottimen_paikka + 1, mistayksikonpituus);
            plusvaimiinus = rivin_data.substr(miinuserottimen_paikka+1);

            yleikkaus = 0-stod(plusvaimiinus);

            if ( not muunnos.lisaa_kaava(mista,mihin,kerroinnumerona,yleikkaus) ) {
                cout << "Virhe: Muunnos oli jo olemassa." << endl;
                return false;
            }
            continue;
        }

        //Käsitellään tapaus jolloin haluttu muutos sisältää plusmerkin
        if ( pluserottimen_paikka != string::npos) {

            mistayksikonpituus = pluserottimen_paikka - kerroinerottimen_paikka-1;

            string plusvaimiinus;

            mihin = rivin_data.substr(0, yksikkoerottimen_paikka);
            kerroin = rivin_data.substr(yksikkoerottimen_paikka + 2, pituuskertoimelle);
            kerroinnumerona = stod(kerroin);
            mista = rivin_data.substr(kerroinerottimen_paikka + 1, mistayksikonpituus);
            plusvaimiinus = rivin_data.substr(pluserottimen_paikka+1);

            yleikkaus = stod(plusvaimiinus);


            if ( not muunnos.lisaa_kaava(mista,mihin,kerroinnumerona,yleikkaus) ) {
                cout << "Virhe: Muunnos oli jo olemassa." << endl;
                return false;
            }
            continue;
        }

        //simppeli keissi kun ei ole plussaa taikka miinusta
        mihin = rivin_data.substr(0, yksikkoerottimen_paikka);
        kerroin = rivin_data.substr(yksikkoerottimen_paikka + 2, pituuskertoimelle);
        kerroinnumerona = stod(kerroin);
        mista = rivin_data.substr(kerroinerottimen_paikka + 1);

        if ( not muunnos.lisaa_kaava(mista,mihin,kerroinnumerona,yleikkaus) ) {
            cout << "Virhe: Muunnos oli jo olemassa." << endl;
            return false;
        }
    }

    tiedosto_olio.close();
    return true;
}


int main() {
    string muunnostiedoston_nimi;
    cout << "Syota saantotiedoston nimi: ";
    getline(cin, muunnostiedoston_nimi);

    Muunnos kaavat;
    try {
        if ( not lue_muunnostiedosto(muunnostiedoston_nimi, kaavat) ) {
            return 1;
        }
    } catch (...) {
        cout << "Virhe: Sääntötiedosto on virheellinen." << endl;
        return 1;
    }

    kaavat.yhdista_linkittyvat_kaavat();
    //kaavat.tulosta_kaavat();
    kayttoliittyma(kaavat);
}
