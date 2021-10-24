/*              -- TO DO --
    - Gestire scrittura risultati in append cancellando prima il contenuto
    - Ottimizzare lettura da file con un metodo a parte
    - Inserire andamento per benzina e spesa cibo

    - ---OK--- Struttura per il risultato con tutti i mesi -> array anno fatto di struct risultatoMensile{}
    - ---OK--- Metodo per lettura dei 4 file -> fatto all'inizio del main
    - ---OK--- Struttura per le linee lette dai file divise per file -> struct inputData{}, inputDataLine{}  
    - ---OK--- Struttura per le informazioni estrapolate -> struct pagamento{}    
    - ---OK--- Metodo per dividere le righe lette estrapolando prezzo/from/to -> formattatore()

    --------------------------------------------------------------------------------------------
    g++ -o crea_andamento.exe crea_andamento.cpp util.cpp && ./crea_andamento.exe && cat risultati.txt
    ./crea_andamento && cat risultati.txt
    --------------------------------------------------------------------------------------------
*/

#include "util.h"
using namespace std;

int main()
{
    // ESTRAZIONE DATI DAI FILE
    ifstream inFile;
    string line;
    string files[4] = {"acqua.txt", "tari.txt", "internet.txt", "lucegas.txt"};
    inputDataList inputListRead;
    ofstream debug;

    //prendo la data odierna
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%d/%m/%Y %X");

    debug.open("output/debug.txt", std::ios_base::app);
    debug << "================ " << ss.str() << " =================" << endl;

    for (int i = 0; i < 4; i++)
    {
        inFile.open("input/" + files[i]);

        while (getline(inFile, line))
        {
            line.length() == 25 ? line.erase(line.length() - 1) : ""; //elimino il carattere \n
            inputDataLine dataRead;
            dataRead.lineRead = line;
            dataRead.fileSource = files[i];

            debug << dataRead.lineRead << " " << dataRead.fileSource << endl; //debug

            switch (i)
            {
            case 0:
                inputListRead.acqua.push_back(dataRead);
                break;
            case 1:
                inputListRead.tari.push_back(dataRead);
                break;
            case 2:
                inputListRead.internet.push_back(dataRead);
                break;
            case 3:
                inputListRead.lucegas.push_back(dataRead);
                break;
            default:
                break;
            };
        };

        inFile.close();
    };

    debug << "======================================================" << endl;
    debug.close();
    //DATI ESTRATTI E INSERITI IN inputRead{}

    //------------------------------------------------------------------------

    stampaRisultato(inputListRead);

    return 0;
}
