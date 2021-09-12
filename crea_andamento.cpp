#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

/*              -- TO DO --
    - Metodo per lettura dei 4 file
    - Metodo per stampa risultati su file
    - Struttura per il risultato con tutti i mesi
    - Gestire scrittura risultati in append cancellando prima il contenuto

    - ---OK--- Struttura per le linee lette dai file divise per file -> struct inputData{}, inputDataLine{}  
    - ---OK--- Struttura per le informazioni estrapolate -> struct pagamento{}    
    - ---OK--- Metodo per dividere le righe lette estrapolando prezzo/from/to -> formattatore()

    --------------------------------------------------------------------------------------------
    g++ -o crea_andamento.exe crea_andamento.cpp && ./crea_andamento.exe && cat risultati.txt
    ./crea_andamento.exe && cat risultati.txt
    --------------------------------------------------------------------------------------------
*/

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

pagamento formattatore(string line)
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

    return elem;
}

int main()
{
    ifstream inFile;
    string line;
    string files[4] = {"acqua.txt", "tari.txt", "internet.txt", "lucegas.txt"};
    inputData inputRead;
    ofstream debug;

    debug.open("debug.txt", std::ios_base::app);
    debug << "======================================================" << endl;
    debug.seekp(0,ios::beg);

    for (int i = 0; i < 4; i++)
    {
        inFile.open(files[i]);

        //bool primaLettura = true;

        while (getline(inFile, line))
        {
            line.length() == 25 ? line.erase(line.length() - 1) : ""; //elimino il carattere \n
            inputDataLine dataRead;
            dataRead.info = line;
            dataRead.file = files[i];

            debug << dataRead.info << " " << dataRead.file << endl;

            cout << dataRead.info << endl;

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

        // pagamento elem = formattatore(line);

        inFile.close();
    }

    debug << "======================================================" << endl;
    debug.close();

    ofstream outFile("risultati.txt");
    outFile << "in costruzione....";

    return 0;
}