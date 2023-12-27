#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

// Globaalit vakiot:
const int HUONEIDEN_MAARA = 300;
const int VARAUSNUMERO_MAX = 99999;
const int VARAUSNUMERO_MIN = 10000;
const int YHDEN_HINTA = 100;
const int KAHDEN_HINTA = 150;

// Luodaan struct
struct Huone {
    int yot, varausnumero, huonenumero, loppusumma;
    string varaaja;
    bool varattu;
    char huonetyyppi;
};

// Tämä aliohjelma tarkistaa huonenumeron saatavuuden
bool onkoHuoneVapaana(bool varattu) {
    if (varattu == true) {
        return false;
    }
    else {
        return true;
    }
}

// Tämä aliohjelma tulostaa kaikki varauksen tiedot käyttäjälle
void tulostaVarauksenTiedot(Huone asiakas) {
    cout << "\n*********************************************************\n";
    cout << "Tässä kaikki varauksesi tiedot:\n";
    cout << "Varaajan nimi: " << asiakas.varaaja << endl;
    cout << "Huonetyyppi: " << asiakas.huonetyyppi << " hengen huone\n";
    cout << "Huoneesi numero: " << asiakas.huonenumero << endl;
    cout << "Yövyttävien öiden määrä: " << asiakas.yot << " yötä\n";
    cout << "Varausnumero: " << asiakas.varausnumero << endl;
    cout << "Loppusumma: " << asiakas.loppusumma << " euroa.\n";
    cout << "\n*********************************************************\n";

}


int main() {
    setlocale(LC_ALL, "fi_FI");

    // Muuttujien määrittäminen
    Huone huoneet[HUONEIDEN_MAARA];
    bool jatkuuko = true, onko_vapaana = true, onko_numero = true, onko_varattu = true;
    char valinta1, huonevalinta, huonenumvalinta, jatkovalinta, hakuvalinta;
    char muutosvalinta, arvonta;
    int huonenum, alennus, hakuvarausnum, indeksi = 500;
    char mahdollinen_ale[3] = {'0', '1', '2'};
    int ale_mahdollisuudet = sizeof(mahdollinen_ale);
    string hakunimi;

    // Koska kaikki huoneet ovat alussa vapaita, määritellää jokaisessa huoneessa varattu falseksi
    // Merkitään samalla kaikki huonenumerot oikeiksi
    for (int i = 0; i < 300; i++) {
        huoneet[i].varattu = false;
        huoneet[i].huonenumero = i + 1;
    }

    while (jatkuuko != false) {
        // Päävalikko, menu:
        cout << "\n*********************************************************\n";
        cout << "\nHei ja tervetuloa hotelli Bulgarian huonevarauspalveluun!\n";
        cout << "Mitä haluaisit tehdä? (Syötä numero 1 - 3)\n";
        cout << "1. Tee uusi huonevaraus\n";
        cout << "2. Tarkastele omaa varaustasi\n";
        cout << "3. Lopeta palvelun käyttö\n";
        cin >> valinta1;

        // Käytetään switch eri tilanteiden toteuttamiseen:
        switch (valinta1) {
            case '1':
                // Yhden vai kahden hengen huone
                do {
                    cout << "\nKumman vaihtoehdon haluaisit varata? (Syötä 1 tai 2)\n";
                    cout << "1. Yhden hengen huone (100 euroa / yö)\n";
                    cout << "2. Kahden hengen huone (150 euroa / yö)\n";
                    cin >> huonevalinta;
                } while (!((huonevalinta == '1') || (huonevalinta == '2')));

                // Jos yhden hengen, tarkistetaan onko vapaana
                for (int i = 0; i < 150; i++) {
                    if (onkoHuoneVapaana(huoneet[i].varattu) == true) {
                        onko_varattu = false;
                    }
                }

                // Jos kahden hengen, tarkistetaan onko vapaana
                for (int i = 150; i < 300; i++) {
                    if (onkoHuoneVapaana(huoneet[i].varattu) == true) {
                        onko_varattu = false;
                    }
                }

                // Jos kaikki yhden/kahden hengen huoneet varattuja:
                if (onko_varattu == true) {
                    cout << "\nValitettavasti kaikki " << huonevalinta << " hengen huoneemme ovat varattuja.\n";
                    break;
                }

                // Jos on vapaana, jatketaan huonenumeron valintaan:
                do {
                    cout << "\nMiten haluat määrittää huoneesi numeron? (Syötä 1 tai 2)\n";
                    cout << "1. Valitse huoneesi numero itse\n";
                    cout << "2. Järjestelmä arpoo huoneesi numeron\n";
                    cin >> huonenumvalinta;
                } while (!((huonenumvalinta == '1') || (huonenumvalinta == '2')));

                // Jos käyttäjä valitsee numeron:
                if (huonenumvalinta == '1') {
                    do {
                        do {
                            cout << "\nValitse huonenumero seuraavista: (Syötä haluttu numero)\n";
                            cout << "Yhden hengen huoneet: huoneet 1 - 150\n";
                            cout << "Kahden hengen huoneet: huoneet 151 - 300\n";
                            cin >> huonenum;
                        } while (huonenum > 300 || huonenum < 1);

                        // Tarkistetaan numeron saatavuus:
                        onko_vapaana = onkoHuoneVapaana(huoneet[huonenum - 1].varattu);

                        if (onko_vapaana == false) {
                            cout << "\nValitettavasti tämä huone on varattu. Syötä uusi numero.";
                        }
                    } while (onko_vapaana != true); 
                }

                // Jos arvotaan numero:
                if (huonenumvalinta == '2') {
                    do {
                        if (huonevalinta == '1') {
                            huonenum = 1 + (rand() % 150);
                        }
                        else if (huonevalinta == '2') {
                            huonenum = 151 + (rand() % 300);
                        }

                        // Tarkistetaan numeron saatavuus:
                        onko_vapaana = onkoHuoneVapaana(huoneet[huonenum - 1].varattu);
                    } while (onko_vapaana != true);
                }

                cout << "\nHuonenumerosi on " << huonenum << endl;

                // Merkitään huonenumero varatuksi:
                huoneet[huonenum - 1].varattu = true;

                // Ilmoitetaan tieto huonetyypistä asiakkaan structiin
                huoneet[huonenum - 1].huonetyyppi = huonevalinta;

                // Kysytään käyttäjältä loput tiedot:
                cout << "\nSyötä koko nimesi: ";
                cin.ignore();
                getline (cin, huoneet[huonenum - 1].varaaja);

                do {
                    cout << "\nMonta yötä aiot yöpyä? Syötä öiden määrä: ";
                    cin >> huoneet[huonenum - 1].yot;

                    if (cin.fail()) {
                        cout << "\nSyöttämäsi arvo oli virheellinen. Syötä uusi arvo.";
                        onko_numero = false;
                        cin.clear();
                        cin.ignore();
                    }
                    else {
                        onko_numero = true;
                    }
                } while (onko_numero == false);
                

                // Arvotaan käyttäjälle varausnumero
                huoneet[huonenum - 1].varausnumero = VARAUSNUMERO_MIN + (rand() % VARAUSNUMERO_MAX);
                cout << "\nVarausnumerosi on " << huoneet[huonenum - 1].varausnumero << endl;

                // Loppusumman laskeminen:
                if (huonevalinta == '1') {
                    huoneet[huonenum - 1].loppusumma = huoneet[huonenum - 1].yot * YHDEN_HINTA;
                }
                else if (huonevalinta == '2') {
                    huoneet[huonenum - 1].loppusumma = huoneet[huonenum - 1].yot * KAHDEN_HINTA;
                }

                cout << "\nLoppusummasi on " << huoneet[huonenum - 1].loppusumma << " euroa\n";

                // Mahdollinen alennus:
                srand(time(NULL));
                alennus = rand() % ale_mahdollisuudet;

                cout << "\nMeidän hotellissamme jokaisella asiakkaalla on mahdollisuus voittaa 10 % tai 20 % alennus\n";
                do {
                    cout << "Syötä A nähdäksesi osuiko arpaonni kohdallesi: ";
                    cin >> arvonta;
                } while (arvonta != 'A');

                if (alennus == 1) {
                    cout << "\nOnneksi olkoon! Olet saanut 10 % alennuksen koko loppusummastasi!\n";
                    huoneet[huonenum - 1].loppusumma *= 0.9;
                    cout << "Uusi loppusummasi on " << huoneet[huonenum - 1].loppusumma << " euroa.\n";
                }
                else if (alennus == 2) {
                    cout << "\nOnneksi olkoon! Olet saanut 20 % alennuksen koko loppusummastasi!\n";
                    huoneet[huonenum - 1].loppusumma *= 0.8;
                    cout << "Uusi loppusummasi on " << huoneet[huonenum - 1].loppusumma << " euroa.\n";
                }
                else {
                    cout << "\nValitettavasti tällä kertaa arpaonni ei osunut kohdallesi.\n";
                    cout << "Loppusummasi on edelleen: " << huoneet[huonenum - 1].loppusumma << endl;
                }

                // Varauksen vahvistus:
                do {
                    cout << "\nVahvistetaanko varaus? (Syötä K tai E)\n";
                    cin >> jatkovalinta;
                } while (!((jatkovalinta == 'K') || (jatkovalinta == 'E')));

                // Jos varausta ei vahvisteta
                if (jatkovalinta == 'E') {
                    cout << "\nVarausta ei vahvistettu.\n";
                    // Muistetaan merkitä huone vapaaksi:
                    huoneet[huonenum - 1].varattu = false;
                    break;
                }
                
                // Varaus on nyt tehty, näytetään käyttäjälle kaikki varauksen tiedot:
                cout << "\nVarauksesi on nyt valmis!\n";
                tulostaVarauksenTiedot(huoneet[huonenum - 1]);
                
                // Jatketaanko palvelun käyttöä?
                do {
                    cout << "\nHaluatko jatkaa palvelun käyttöä? (Syötä K tai E)\n";
                    cin >> jatkovalinta;
                } while (!((jatkovalinta == 'K') || (jatkovalinta == 'E')));

                if (jatkovalinta == 'E') {
                    cout << "\nNäkemiin.\n";
                    cout << "\n*********************************************************\n";
                    jatkuuko = false;
                }

            break;

            case '2':
                // Jos halutaan tarkastella omaa varausta
                // Haetaanko varaus nimellä vai varausnumerolla?
                do {
                    cout << "\nHaluatko hakea varaustasi nimellä vai varausnumerolla? (Syötä 1 tai 2)\n";
                    cout << "1. Nimi\n";
                    cout << "2. Varausnumero\n";
                    cin >> hakuvalinta;
                } while (!((hakuvalinta == '1') || (hakuvalinta == '2')));

                // Jos haetaan nimellä
                if (hakuvalinta == '1') {
                    cout << "\nSyötä koko nimesi: ";
                    cin.ignore();
                    getline(cin, hakunimi);

                    for (int j = 0; j < 300; j++) {
                        if (huoneet[j].varaaja == hakunimi) {
                            indeksi = j;
                        }
                    }
                    // Jos nimeä ei löydy järjestelmästä
                    if (indeksi == 500) {
                        cout << "\nValitettavasti nimeä ei löytynyt järjestelmästämme.\n";
                        break;
                    }
                }
                // Jos haetaan varausnumerolla
                else if (hakuvalinta == '2') {
                    do {
                        cout << "\nSyötä varausnumerosi: ";
                        cin >> hakuvarausnum;

                        if (cin.fail()) {
                            onko_numero = false;
                            cin.clear();
                            cin.ignore();
                        }
                        else {
                            onko_numero = true;
                        }
                    } while (onko_numero == false);

                    for (int j = 0; j < 300; j++) {
                        if (huoneet[j].varausnumero == hakuvarausnum) {
                            indeksi = j;
                        }
                    }
                    // Jos varausnumeroa ei löydy järjestelmästä
                    if (indeksi == 500) {
                        cout << "\nValitettavasti varausnumeroa ei löytynyt järjestelmästämme.\n";
                        break;
                    }
                }

                // Tulostetaan nyt varauksen tiedot käyttäjälle
                tulostaVarauksenTiedot(huoneet[indeksi]);

                // Palautetaan indeksi = 500, jotta hakutoiminto toimii jatkossakin
                indeksi = 500;

                // Jatketaanko palvelun käyttöä?
                do {
                    cout << "\nHaluatko jatkaa palvelun käyttöä? (Syötä K tai E)\n";
                    cin >> jatkovalinta;
                } while (!((jatkovalinta == 'K') || (jatkovalinta == 'E')));

                if (jatkovalinta == 'E') {
                    cout << "\nNäkemiin.\n";
                    cout << "\n*********************************************************\n";
                    jatkuuko = false;
                }

            break;

            case '3':
                // Jos halutaan lopettaa ohjelman käyttö
                cout << "\nNäkemiin.\n";
                cout << "\n*********************************************************\n";
                jatkuuko = false;
            break;
            
        }
    }

    return 0;
}
