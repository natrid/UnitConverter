#include "kayttoliittyma.hh"
#include "muunnos.hh"
#include "muunnoslista.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string>
#include <sstream>

using namespace std;

namespace {

//Funktio käsittelee syötetyn käskyn tulkinnan
void kasky(Muunnos muunnos, istringstream& loppurivi, double maara) {
    string mista;
    string mihin;

    loppurivi >> ws >> mista >> ws >> mihin >> ws;

    if ( not loppurivi ) {
        cout << "Virhe: puutteelinen käsky" << endl;
        return;
    }

    // cout << mista <<"   "<< mihin << endl;

    if(not muunnos.loytyyko_muutos(mista+" "+mihin)){
        cout << "Virhe: ei muunnosta" << endl;
        return;
    }
    muunnos.laske_muunnos(mista+" "+mihin,maara);
}

}
//Fuktio sisältää käyttöliittymän laskinohjelmalle
//Parametrina otetaan muunnoskaavat laskinohjelmalle
void kayttoliittyma(Muunnos& muunnos){
    string syoterivi;
    while ( true ) {
        cout << "muunnospyynto> ";
        getline(cin, syoterivi);

        //Lopetetaan ohjelman suoritus kun syötetään tyhjä rivi
        if ( not cin or syoterivi == "" ) {
            break;
        }

        istringstream rivivirta{syoterivi};

        string komento;
        rivivirta >> komento;
        if ( not rivivirta ) {
            cout << "Virhe: komennoksi ei saa syottaa pelkkia valeja." << endl;
            continue;
        }

        try {
            double maara = stod(komento);
            kasky(muunnos, rivivirta, maara);

        } catch (...) {
            cout << "Virhe: Syötä käsyky muodossa esim:\"1.23jaardi tuuma\"" << endl;
        }
    }
}
