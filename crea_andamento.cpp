#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <vector>
#include <chrono>

using namespace std;

/*              -- TO DO --
    - Metodo per stampa risultati su file
    - Metodo per calcolare costi su ogni mese
    - Gestire scrittura risultati in append cancellando prima il contenuto
    - Ottimizzare lettura da file con un metodo a parte

    - ---OK--- Struttura per il risultato con tutti i mesi -> array anno fatto di struct risultatoMensile{}
    - ---OK--- Metodo per lettura dei 4 file -> fatto all'inizio del main
    - ---OK--- Struttura per le linee lette dai file divise per file -> struct inputData{}, inputDataLine{}  
    - ---OK--- Struttura per le informazioni estrapolate -> struct pagamento{}    
    - ---OK--- Metodo per dividere le righe lette estrapolando prezzo/from/to -> formattatore()

    --------------------------------------------------------------------------------------------
    g++ -o crea_andamento.exe crea_andamento.cpp && ./crea_andamento.exe && cat risultati.txt
    ./crea_andamento.exe && cat risultati.txt
    --------------------------------------------------------------------------------------------
*/
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
    out.open("risultati.txt", std::ios_base::out);
    out << "================ " << ss.str() << " =================" << endl;

    for (int i = 0; i < 12; i++)
    {
        out << anno[i].mese << " " << anno[i].importo << endl;
    }

    out << "======================================================" << endl;
    out.close();

    return;
}

void formattatore(string line)
{
    vector<pagamento> outLineFormat;
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

    outLineFormat.push_back(elem);

    return;
}

int main()
{
    // ESTRAZIONE DATI DAI FILE
    ifstream inFile;
    string line;
    string files[4] = {"acqua.txt", "tari.txt", "internet.txt", "lucegas.txt"};
    inputData inputRead;
    ofstream debug;

    //prendo la data odierna
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%d/%m/%Y %X");

    debug.open("debug.txt", std::ios_base::app);
    debug << "================ " << ss.str() << " =================" << endl;

    for (int i = 0; i < 4; i++)
    {
        inFile.open(files[i]);

        while (getline(inFile, line))
        {
            line.length() == 25 ? line.erase(line.length() - 1) : ""; //elimino il carattere \n
            inputDataLine dataRead;
            dataRead.info = line;
            dataRead.file = files[i];

            debug << dataRead.info << " " << dataRead.file << endl; //debug

            switch (i)
            {
            case 0:
                inputRead.acqua.push_back(dataRead);
                break;
            case 1:
                inputRead.tari.push_back(dataRead);
                break;
            case 2:
                inputRead.internet.push_back(dataRead);
                break;
            case 3:
                inputRead.lucegas.push_back(dataRead);
                break;
            default:
                break;
            }
        }

        inFile.close();
    }

    debug << "======================================================" << endl;
    debug.close();
    //DATI ESTRATTI E INSERITI IN inputRead{}

    //------------------------------------------------------------------------

    stampaRisultato(inputRead);

    formattatore(line);

    return 0;
}