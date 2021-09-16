#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <vector>
#include <chrono>

using namespace std;

struct risultatoMensile
{
    string mese;
    string importo;
};

struct pagamento
{
    string prezzo;
    string from;
    string to;
    string file;
};

struct inputDataLine
{
    string info;
    string file;
};

struct inputData
{
    vector<inputDataLine> acqua;
    vector<inputDataLine> tari;
    vector<inputDataLine> internet;
    vector<inputDataLine> lucegas;
};

struct diffMesi {
    int m1,m2,g1,g2;
}

void stampaRisultato(inputData);
void formattatore(risultatoMensile, inputData);

