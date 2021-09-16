#include "util.h"

using namespace std;

void stampaRisultato(inputData output)
{
    //inizializzazione strutture
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

    formattatore(*anno, output);

    for (int i = 0; i < 12; i++)
    {
        out << anno[i].mese << " " << anno[i].importo << endl;
    }

    out << "======================================================" << endl;
    out.close();

    return;
};

diffMesi estraiPeriodo(pagamento elem)
{
    //conversione string to char[] per usare la strtok
    int n = elem.from.length();
    char fromline[n + 1];
    strcpy(fromline, elem.from.c_str());
    //conversione string to char[] per usare la strtok
    int m = elem.to.length();
    char toline[m + 1];
    strcpy(toline, elem.to.c_str());
    char *mese1, *mese2, *gg1, *gg2;
    gg1 = strtok(fromline, "/");
    mese1 = strtok(NULL, "/");
    gg2 = strtok(toline, "/");
    mese2 = strtok(NULL, "/");

    diffMesi elem;
    elem.m1 = atoi(mese1);
    elem.g1 = atoi(gg1);
    elem.m2 = atoi(mese2);
    elem.g2 = atoi(gg2);

    cout << m1 << " " << g1 << " " << m2 << " " << g2 << " " << endl;

    return elem;
}

pagamento formatta(string line, string file)
{
    pagamento elem;
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
    elem.file = file;

    diffMesi estrazione = estraiPeriodo(elem);


    return elem;
}

void formattatore(risultatoMensile output, inputData data)
{

    /* 
        per ogni data
            chiamo la formatta
                mi ritorna un elem
            chiamo la assegnaMese
                mi torna un elem
                assegno questo elem in output.mese corrispondente
     */

    string line = "60-06/06/2021-30/08/2021";
    string file = "txzt";
    formatta(line, file);

    return;
}
