#ifndef MUUNNOSLISTA_HH
#define MUUNNOSLISTA_HH
#include <memory>

using namespace std;

class Muunnoslista
{
public:
    Muunnoslista();
    int pituus() const;
    bool onko_arvo_listassa(string yksikko) const;
    void lisaa(const string& yksikko, int kerroin_suurempaan, int kerroin_pienempaan);
    void tulosta() const;
    void tulosta_takaperin() const;
    //bool poista_arvo(string yksikko);

private:
    struct Solu {
        string yksikko;
        int kerroin_suurempaan;
        int kerroin_pienempaan;
        shared_ptr<Solu>  seuraava_osoite;
        Solu* edellinn_osoite;
    };

    shared_ptr<Solu> ensimmaisen_osoite_;
    Solu* viimeisen_osoite_;
    int alkioiden_maara_;
};

#endif // MUUNNOSLISTA_HH
