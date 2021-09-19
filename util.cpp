#include "util.h"

using namespace std;

void stampaRisultato(inputDataList inputDatas)
{
    for (int i = 0; i < inputDatas.acqua.size(); i++)
    {
        inputDatas.acqua[i].lineStringSplit = formatta(inputDatas.acqua[i].lineRead);                               //prendo prezzo, from e to
        inputDatas.acqua[i].lineIntSplit = formattaInt(inputDatas.acqua[i].lineStringSplit);                        //prendo g1,g2,m2,m1 interi
        inputDatas.acqua[i].infoCompentenza.mesiCompetenza = trovaMesiCompetenza(inputDatas.acqua[i].lineIntSplit); //trovo i mesi di competenza
        inputDatas.acqua[i].infoCompentenza.prezzoMensile = prezzoMensile(inputDatas.acqua[i]);                     // trovo il prezzo mensile
    }
    for (int i = 0; i < inputDatas.tari.size(); i++)
    {
        inputDatas.tari[i].lineStringSplit = formatta(inputDatas.tari[i].lineRead);                               //prendo prezzo, from e to
        inputDatas.tari[i].lineIntSplit = formattaInt(inputDatas.tari[i].lineStringSplit);                        //prendo g1,g2,m2,m1 interi
        inputDatas.tari[i].infoCompentenza.mesiCompetenza = trovaMesiCompetenza(inputDatas.tari[i].lineIntSplit); //trovo i mesi di competenza
        inputDatas.tari[i].infoCompentenza.prezzoMensile = prezzoMensile(inputDatas.tari[i]);                     // trovo il prezzo mensile
    }
    for (int i = 0; i < inputDatas.internet.size(); i++)
    {
        inputDatas.internet[i].lineStringSplit = formatta(inputDatas.internet[i].lineRead);                               //prendo prezzo, from e to
        inputDatas.internet[i].lineIntSplit = formattaInt(inputDatas.internet[i].lineStringSplit);                        //prendo g1,g2,m2,m1 interi
        inputDatas.internet[i].infoCompentenza.mesiCompetenza = trovaMesiCompetenza(inputDatas.internet[i].lineIntSplit); //trovo i mesi di competenza
        inputDatas.internet[i].infoCompentenza.prezzoMensile = prezzoMensile(inputDatas.internet[i]);                     // trovo il prezzo mensile
    }
    for (int i = 0; i < inputDatas.lucegas.size(); i++)
    {
        inputDatas.lucegas[i].lineStringSplit = formatta(inputDatas.lucegas[i].lineRead);                               //prendo prezzo, from e to
        inputDatas.lucegas[i].lineIntSplit = formattaInt(inputDatas.lucegas[i].lineStringSplit);                        //prendo g1,g2,m2,m1 interi
        inputDatas.lucegas[i].infoCompentenza.mesiCompetenza = trovaMesiCompetenza(inputDatas.lucegas[i].lineIntSplit); //trovo i mesi di competenza
        inputDatas.lucegas[i].infoCompentenza.prezzoMensile = prezzoMensile(inputDatas.lucegas[i]);                     // trovo il prezzo mensile
    }

    //inizializzazione strutture
    risultatoMensile anno[12];
    string mesi[12] = {"GEN", "FEB", "MAR", "APR", "MAG", "GIU", "LUG", "AGO", "SET", "OTT", "NOV", "DIC"};
    for (int i = 0; i < 12; i++)
    {
        anno[i].importo = 0;
        anno[i].mese = mesi[i];
    }

    for (int i = 0; i < inputDatas.acqua.size(); i++)
    {
        for (int j = 0; j < inputDatas.acqua[i].infoCompentenza.mesiCompetenza.size(); j++)
        {
            int k = inputDatas.acqua[i].infoCompentenza.mesiCompetenza[j];
            anno[k - 1].importo += inputDatas.acqua[i].infoCompentenza.prezzoMensile;
        };
    };
    for (int i = 0; i < inputDatas.tari.size(); i++)
    {
        for (int j = 0; j < inputDatas.tari[i].infoCompentenza.mesiCompetenza.size(); j++)
        {
            int k = inputDatas.tari[i].infoCompentenza.mesiCompetenza[j];
            anno[k - 1].importo += inputDatas.tari[i].infoCompentenza.prezzoMensile;
        };
    };
    for (int i = 0; i < inputDatas.internet.size(); i++)
    {
        for (int j = 0; j < inputDatas.internet[i].infoCompentenza.mesiCompetenza.size(); j++)
        {
            int k = inputDatas.internet[i].infoCompentenza.mesiCompetenza[j];
            anno[k - 1].importo += inputDatas.internet[i].infoCompentenza.prezzoMensile;
        };
    };
    for (int i = 0; i < inputDatas.lucegas.size(); i++)
    {
        for (int j = 0; j < inputDatas.lucegas[i].infoCompentenza.mesiCompetenza.size(); j++)
        {
            int k = inputDatas.lucegas[i].infoCompentenza.mesiCompetenza[j];
            anno[k - 1].importo += inputDatas.lucegas[i].infoCompentenza.prezzoMensile;
        };
    };

    //prendo la data odierna
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%d/%m/%Y %X");

    ofstream out;
    out.open("output/risultati.txt", std::ios_base::out);
    out << "================ " << ss.str() << " =================" << endl;

    for (int i = 0; i < 12; i++)
    {
        out << anno[i].mese << " " << anno[i].importo << endl;
    }

    out << "======================================================" << endl;
    out.close();

    return;
};

split formatta(string line)
{
    // estrae giorno mese per il periodo di riferimento del pagamento
    // viene chiamata dalla funzione Formattatore()
    // restituisce un oggetto diffMesi

    split elem;

    //conversione string to char[] per usare la strtok
    int n = line.length();
    char charLine[n + 1];
    strcpy(charLine, line.c_str());

    //splitto line in prezz, from e to
    char *p, *fr, *t;
    p = strtok(charLine, "-");
    fr = strtok(NULL, "-");
    t = strtok(NULL, "-");

    //compilo elem
    elem.prezzo = p;
    elem.from = fr;
    elem.to = t;

    return elem;
}

spltInteger formattaInt(split elem)
{
    char *mese1, *mese2, *gg1, *gg2;

    //spezzo from
    int n = elem.from.length();
    char fromline[n + 1];
    strcpy(fromline, elem.from.c_str());
    gg1 = strtok(fromline, "/");
    mese1 = strtok(NULL, "/");
    //spezzo to
    int m = elem.to.length();
    char toline[m + 1];
    strcpy(toline, elem.to.c_str());
    gg2 = strtok(toline, "/");
    mese2 = strtok(NULL, "/");

    //converto tutto in interi
    spltInteger splitInt;
    splitInt.mese1 = atoi(mese1);
    splitInt.giorno1 = atoi(gg1);
    splitInt.mese2 = atoi(mese2);
    splitInt.giorno2 = atoi(gg2);
    //cout << m1 << " " << g1 << " " << m2 << " " << g2 << " " << endl;

    return splitInt;
}

vector<int> trovaMesiCompetenza(spltInteger elem)
{
    int mese1 = elem.mese1;
    int mese2 = elem.mese2;

    int differenza = mese2 - mese1 + 1; // mese1 e mese2 inclusi
    if (elem.giorno1 > 15)
    {
        differenza -= 1;
        mese1 += 1; // tolgo il mese1
    }
    if (elem.giorno2 < 15)
    {
        differenza -= 1;
        mese2 -= 1; // tolgo il mese2
    }
    vector<int> mesiCompetenza;
    for (int i = mese1; i <= mese2; i++)
    {
        mesiCompetenza.push_back(i);
    }

    // cout << "differenza:" << differenza << " mese1: " << mese1 << " mese2: " << mese2 << endl;

    return mesiCompetenza;
}

int prezzoMensile(inputDataLine inputLine)
{
    int quantiMesi = inputLine.infoCompentenza.mesiCompetenza.size();
    int prezzoMensile = stoi(inputLine.lineStringSplit.prezzo) / quantiMesi;
    return prezzoMensile;
}