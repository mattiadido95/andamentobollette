/*              -- TO DO --

    --------------------------------------------------------------------------------------------
    g++ -o crea_andamento.exe crea_andamento.cpp util.cpp && ./crea_andamento.exe && cat output/risultati.txt
    ./crea_andamento.exe && cat output/risultati.txt
    --------------------------------------------------------------------------------------------
*/

#include "util.h"
using namespace std;

int callInitialMenu() {
    int initialMenuChoice;
    int choiceYear = 0;
    cout << "--- BENVENUTO ---" << endl;
    cout << "Selezionare anno:" << endl;
    cout << "1) 2021" << endl;
    cout << "2) 2022" << endl;
    cin >> initialMenuChoice;
    switch (initialMenuChoice) {
        case 1:
            cout << "Andamento 2021" << endl;
            choiceYear = 2021;
            break;
        case 2:
            cout << "Andamento 2022" << endl;
            choiceYear = 2022;
            break;
        default:
            cout << "Andamento non disponibile" << endl;            
            break;
    }
    return choiceYear;
}


int main()
{
    int year = callInitialMenu();
    if (year == 0) {
        return 0;
    }

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

    // convert int to string
    stringstream ssYear;
    ssYear << year;
    string yearString = ssYear.str();    

    for (int i = 0; i < 4; i++)
    {
        inFile.open("input/"+ yearString + "/" + files[i]);

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
