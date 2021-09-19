#include "util.h"

using namespace std;

void stampaRisultato(inputDataList inputDatas)
{
    for (int i = 0; i < inputDatas.acqua.size(); i++)
    {
        inputDatas.acqua[i].lineStringSplit = formatta(inputDatas.acqua[i].lineRead);        //prendo prezzo, from e to
        inputDatas.acqua[i].lineIntSplit = formattaInt(inputDatas.acqua[i].lineStringSplit); //prendo g1,g2,m2,m1 interi
    }
    for (int i = 0; i < inputDatas.tari.size(); i++)
    {
        inputDatas.acqua[i].lineStringSplit = formatta(inputDatas.acqua[i].lineRead);        //prendo prezzo, from e to
        inputDatas.acqua[i].lineIntSplit = formattaInt(inputDatas.acqua[i].lineStringSplit); //prendo g1,g2,m2,m1 interi
    }
    for (int i = 0; i < inputDatas.internet.size(); i++)
    {
        inputDatas.acqua[i].lineStringSplit = formatta(inputDatas.acqua[i].lineRead);        //prendo prezzo, from e to
        inputDatas.acqua[i].lineIntSplit = formattaInt(inputDatas.acqua[i].lineStringSplit); //prendo g1,g2,m2,m1 interi
    }
    for (int i = 0; i < inputDatas.lucegas.size(); i++)
    {
        inputDatas.acqua[i].lineStringSplit = formatta(inputDatas.acqua[i].lineRead);        //prendo prezzo, from e to
        inputDatas.acqua[i].lineIntSplit = formattaInt(inputDatas.acqua[i].lineStringSplit); //prendo g1,g2,m2,m1 interi
    }






    /*    //inizializzazione strutture
    risultatoMensile anno[12];
    string mesi[12] = {"GEN", "FEB", "MAR", "APR", "MAG", "GIU", "LUG", "AGO", "SET", "OTT", "NOV", "DIC"};
    for (int i = 0; i < 12; i++)
    {
        anno[i].importo = '0';
        anno[i].mese = mesi[i];
    }
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
    out.close(); */

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

competenza trovaMesiCompetenza(inputDataLine elem) {

    competenza outElem;

    


    return outElem;    
}