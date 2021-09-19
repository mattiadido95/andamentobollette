#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <vector>
#include <chrono>

using namespace std;

struct competenza
{
    vector<int> mesiCompetenza;
    int prezzoMensile;
};
struct spltInteger
{
    int mese1;
    int giorno1;
    int mese2;
    int giorno2;
};
struct split
{
    string prezzo;
    string from;
    string to;
};
struct inputDataLine
{
    string lineRead;
    string fileSource;
    split lineStringSplit;
    spltInteger lineIntSplit;
    competenza infoCompentenza;
};
struct inputDataList
{
    vector<inputDataLine> acqua;
    vector<inputDataLine> tari;
    vector<inputDataLine> internet;
    vector<inputDataLine> lucegas;
};

void stampaRisultato(inputDataList);
split formatta(string);
spltInteger formattaInt(split);