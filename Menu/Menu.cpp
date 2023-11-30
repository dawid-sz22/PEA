#include "Menu.h"
#include "../Graphs/AdjacencyMatrix.h"
#include "../Tools/FileClass.h"
#include "../Tools/Timer.h"
#include "../Algorithms/BranchAndBound.h"
#include "../Algorithms/BruteForce.h"
#include "../Algorithms/DynamicPrograming.h"
#include "../Metaheuristics/TabuSearch.h"
#include <iostream>
#include <fstream>
#include <thread>

using namespace std;

void Menu::showMenu()
{
    int choose;
    do {
        cout << "Asymetryczny problem komiwojazera (ATSP)\n";
        cout << "1. Testy manualne (Algorytmy dokladne)\n";
        cout << "2. Testy manualne (Metaheurystyki)\n";
        cout << "3. Testy automatyczne\n";
        cout << "0. Zakoncz program\n";
        cout << "Wybierz opcje: ";

        cin >> choose; //wybrana opcja

        switch (choose)
        {
            case 1:
                Menu::showMenuManual();
                break;
            case 2:
                Menu::showMenuManualM();
                break;
            case 3:
                Menu::showMenuAutomatic();
                break;
            case 0:
                break;
            default:
                cout << endl << "Podano nieprawidlowa opcje!" << endl;
                break;
        }
    } while (choose);
}

void Menu::showMenuAutomatic() {
    int chooseOption = 0;
    int dataCount = 0;

    do
    {
        cout << "1. Brute Force\n";
        cout << "2. Branch&Bound\n";
        cout << "3. DynamicPrograming\n";
        cout << "4. All\n";
        cout << "5. Tabu Search\n";
        cout << "0. Wroc\n";
        cout << "Wybierz opcje: ";
        cin >> chooseOption; //wybrana opcje

        switch (chooseOption)
        {
            case 1: //Brute Force
            {
                cout << "Podaj rozmiar problemu (X problemow po 100 losowych reprezentacji) : ";
                cin >> dataCount;
                int* data = new int [dataCount];

                for (int i = 0; i < dataCount; ++i) {
                    cout << i+1 << ": ";
                    cin >> data[i];
                }
                autoBF(data,dataCount);
            }
                break;
            case 2: //Branch&Bound
            {
                cout << "Podaj rozmiar problemu (X problemow po 100 losowych reprezentacji) : ";
                cin >> dataCount;
                int* data = new int [dataCount];

                for (int i = 0; i < dataCount; ++i) {
                    cout << i+1 << ": ";
                    cin >> data[i];
                }
                autoBB(data,dataCount);
            }
                break;
            case 3: //DP
            {
                cout << "Podaj rozmiar problemu (X problemow po 100 losowych reprezentacji) : ";
                cin >> dataCount;
                int* data = new int [dataCount];

                for (int i = 0; i < dataCount; ++i) {
                    cout << i+1 << ": ";
                    cin >> data[i];
                }
                autoDP(data,dataCount);
            }
            case 4: //all
            {
                int dataCountBF = 0;
                int dataCountBB = 0;
                int dataCountDP = 0;


                cout << "Podaj rozmiar problemu (X problemow po 100 losowych reprezentacji) dla BruteForce: ";
                cin >> dataCountBF;
                int* dataBF = new int [dataCountBF];

                for (int i = 0; i < dataCountBF; ++i) {
                    cout << i+1 << ": ";
                    cin >> dataBF[i];
                }

                cout << "Podaj rozmiar problemu (X problemow po 100 losowych reprezentacji) dla DynamicPrograming: ";
                cin >> dataCountDP;
                int* dataDP = new int [dataCountDP];

                for (int i = 0; i < dataCountDP; ++i) {
                    cout << i+1 << ": ";
                    cin >> dataDP[i];
                }

                cout << "Podaj rozmiar problemu (X problemow po 100 losowych reprezentacji) dla Branch&Bound: ";
                cin >> dataCountBB;
                int* dataBB = new int [dataCountBB];


                for (int i = 0; i < dataCountBB; ++i) {
                    cout << i+1 << ": ";
                    cin >> dataBB[i];
                }


                autoBF(dataBF,dataCountBF);
                autoDP(dataDP,dataCountDP);
                autoBB(dataBB,dataCountBB);
            }
            case 5:
            {
                int typeNeighborhood = 1;
                string fileNames[] = {"../Files/ftv55.atsp","../Files/ftv170.atsp","../Files/rbg358.atsp"};
                int timeData[] = {120,240,360};
                cout << "\nPodaj typ sąsiedztwa (1-SWAP,2-INSERT,3-INVERT,0-ALL): ";
                cin >> typeNeighborhood;
                if (typeNeighborhood<0 || typeNeighborhood>3)
                {
                    typeNeighborhood = 1;
                    cout << endl << "Podano niepoprawna opcje!" << endl;
                    break;
                }
                autoTS(fileNames,timeData,100,1,typeNeighborhood);
            }
                break;
            case 0:
                system("cls");
                break;
            default:
                cout << endl << "Podano niepoprawna opcje!" << endl;
                break;
        }
        cout << endl;
    } while (chooseOption);
}

void Menu::showMenuManual() {
    AdjacencyMatrix* matrix = nullptr;
    Timer timer;
    int chooseOption = 0;
    int help = 0;

    do
    {
        cout << "1. Wczytaj graf z pliku\n";
        cout << "2. Wygeneruj graf losowo\n";
        cout << "3. Wyswietl graf\n";
        cout << "4. Algorytm Brute force - Przeglad zupelny\n";
        cout << "5. Algorytm Branch&Bound\n";
        cout << "6. Algorytm Branch&Bound z limitem czasowym\n";
        cout << "7. Algorytm DynamicPrograming\n";
        cout << "0. Wroc\n";
        cout << "Wybierz opcje: ";
        cin >> chooseOption; //wybrana opcje

        switch (chooseOption)
        {
            case 1:
                cout << "Pobieranie grafu z pliku tekstowego. Podaj nazwe pliku: ";
                {
                    string filename;
                    cin >> filename;
                    AdjacencyMatrix* newMatrix;
                    newMatrix = FileClass::matrixFromFile(filename);
                    if (newMatrix != nullptr)   // jeśli nie wystąpił błąd, usuń macierz i zastąp ją nową
                    {
                        delete matrix;
                        matrix = newMatrix;
                    }
                    else
                        cout<< "ERROR IN READ"<<endl;
                }
                break;
            case 2:
                cout << "Podaj liczbe wierzcholkow: ";
                cin >> help;
                delete matrix;
                matrix = new AdjacencyMatrix(help,0,true);
                break;
            case 3:	//WYŚWIETL GRAF
                if (matrix == nullptr) {
                    cout << "NIE WCZYTANO GRAFU!\n";
                } else matrix->printMatrix();
                break;
            case 4: //Brute force
            {
                if (matrix == nullptr) {
                    cout << "NIE WCZYTANO GRAFU!\n";
                } else {
                    BruteForce* bf = new BruteForce(matrix);
                    timer.run();
                    int *heap = bf->main();
                    timer.stop();
                    int cost = 0;
                    cout << endl << "Czas (Brute Force):" << timer.getTimeMs() << " ms" << endl;
                    cout << "Optymalna sciezka:" << endl;
                    for (int i = 0; i < matrix->getNodesCount(); ++i) {
                        cout << heap[i] << " -> ";
                    }
                    cout << matrix->getStartNode() << "\nKoszt: ";
                    for (int i = 0; i < matrix->getNodesCount() - 1; ++i) {
                        cost += matrix->getWsk()[heap[i]][heap[i+1]];
                    }
                    cost += matrix->getWsk()[heap[matrix->getNodesCount()-1]][matrix->getStartNode()];
                    cout << cost;
                    delete[] heap;
                    delete bf;
                }
            }
                break;
            case 5: //Branch&Bound
            {
                if (matrix == nullptr) {
                    cout << "NIE WCZYTANO GRAFU!\n";
                } else {
                    BranchAndBound* bb = new BranchAndBound(matrix);

                    timer.run();
                    list<NodeBB*> listEnd = bb->main();
                    timer.stop();

                    int* pathTable = new int[matrix->getNodesCount()];
                    NodeBB* helpNode = listEnd.back();
                    cout << endl << "Czas (BB):" << timer.getTimeMs() << " ms" << endl;
                    cout << "Optymalna sciezka:" << endl;
                    for (int i = matrix->getNodesCount() - 1; i >= 0; --i) {
                        pathTable[i] = helpNode->numberOfNode;
                        helpNode = helpNode->father;
                    }
                    for (int i = 0; i < matrix->getNodesCount(); ++i) {
                        cout << pathTable[i] << " -> ";
                    }

                    cout << matrix->getStartNode() << "\nKoszt: ";
                    cout << listEnd.back()->lowerBound <<endl;

                    bb->clear();
                    delete bb;
                    delete [] pathTable;
                }
            }
                break;
            case 6: //B&B z limitem czasowym
            {
                if (matrix == nullptr) {
                    cout << "NIE WCZYTANO GRAFU!\n";
                } else {
                    BranchAndBound* bb = new BranchAndBound(matrix);

                    timer.run();

                    list<NodeBB*> listEnd = bb->mainStop();

                    timer.stop();
                    if (listEnd.empty())
                    {
                        cout <<"Przekroczono ustalony limit czasu! "<<endl;
                    } else
                    {
                        int * pathTable = new int[matrix->getNodesCount()];
                        NodeBB* helpNode = listEnd.back();
                        cout << endl << "Czas (BB):" << timer.getTimeMs() << " ms" << endl;
                        cout << "Optymalna sciezka:" << endl;
                        for (int i = matrix->getNodesCount() - 1; i >= 0; --i) {
                            pathTable[i] = helpNode->numberOfNode;
                            helpNode = helpNode->father;
                        }
                        for (int i = 0; i < matrix->getNodesCount(); ++i) {
                            cout << pathTable[i] << " -> ";
                        }

                        cout << matrix->getStartNode() << "\nKoszt: ";
                        cout << listEnd.back()->lowerBound <<endl;

                        delete [] pathTable;
                    }

                    bb->clear();
                    delete bb;
                }
            }
                break;
            case 7:
            {
                if (matrix == nullptr) {
                    cout << "NIE WCZYTANO GRAFU!\n";
                } else {
                    DynamicPrograming* dp = new DynamicPrograming(matrix);

                    timer.run();
                    dp->main();
                    timer.stop();

                    cout << endl << "Czas (DP):" << timer.getTimeMs() << " ms" << endl;
                    dp->printResults();
                    delete dp;
                }
            }
                break;
            case 0:
                system("cls");
                break;
            default:
                cout << endl << "Podano niepoprawna opcje!" << endl;
                break;
        }
        cout << endl << endl;
    } while (chooseOption);

    //usuń tablice po zakonczeniu
    delete matrix;
}
void Menu::showMenuManualM() {
    AdjacencyMatrix* matrix = nullptr;
    Timer timer;
    int chooseOption = 0;
    double stop = 5.0;
    int iterationsWithNoChange = 100;
    int term = 5;
    int typeNeigh = 1;
    string typeN = "SWAP";

    vector<int> path;
    int help = 0;
    string filename;

    do
    {
        cout << "1. Wczytaj graf z pliku\n";
        cout << "2. Wprowadz kryteria (TS: "<< stop <<"s Stop, MAXIterationsNoChange = "<<iterationsWithNoChange<<", Term = "<<term <<")\n";
        cout << "3. Wybor sasiedztwa ("<<typeN<<")\n";
        cout << "4. Tabu Search\n";
        cout << "6. Wczytaj sciezke z .txt i podaj koszt\n";
        cout << "0. Wroc\n";
        cout << "Wybierz opcje: ";
        cin >> chooseOption; //wybrana opcje

        switch (chooseOption)
        {
            case 1:
                cout << "Pobieranie grafu z pliku tekstowego. Podaj nazwe pliku: ";
                {
                    cin >> filename;
                    AdjacencyMatrix* newMatrix;
                    newMatrix = FileClass::matrixFromFile(filename);
                    if (newMatrix != nullptr)   // jeśli nie wystąpił błąd, usuń macierz i zastąp ją nową
                    {
                        delete matrix;
                        matrix = newMatrix;
                    }
                    else
                        cout<< "ERROR IN READ"<<endl;
                }
                break;
            case 2: //Kryterium stopu
            {
                cout << "1. Dla Tabu Search\n";
                cout << "2. Dla Symulowanego wyzarzania\n";
                cout << "Wybierz opcje: ";
                cin >> chooseOption; //wybrana opcje
                switch (chooseOption) {
                    case 1:
                        cout << "\nPodaj czas w sekundach: ";
                        cin >> stop;
                        cout << "\nPodaj maksymalna ilosc iteracji bez zmian: ";
                        cin >> iterationsWithNoChange;
                        cout << "\nPodaj wielkosc kadencji: ";
                        cin >> term;
                        break;
                    case 2:
                        //SW
                        break;
                    default:
                        cout << endl << "Podano niepoprawna opcje!" << endl;
                        break;
                }
            }
                break;
            case 3: //sąsiedztwo
            {
                cout << "\nPodaj typ sasiedztwa (1-SWAP,2-INSERT,3-INVERT): ";
                cin >> typeNeigh;
                if (typeNeigh<1 || typeNeigh>3)
                {
                    typeN = "SWAP";
                    typeNeigh = 1;
                    cout << endl << "Podano niepoprawna opcje!" << endl;
                } else if (typeNeigh == 1)
                    typeN = "SWAP";
                else if (typeNeigh == 2)
                    typeN = "INSERT";
                else
                    typeN = "INVERT";

            }
                break;
            case 4: //Tabu search
            {
                if (matrix == nullptr) {
                    cout << "NIE WCZYTANO GRAFU!\n";
                } else {
                    TabuSearch* ts = new TabuSearch(matrix,stop,iterationsWithNoChange, term, typeNeigh);

                    ts->start();
                    path = ts->getShortestPath();
                    ts->printResults();
                    string s = "../Files/Output/ts_";
                    size_t pos = filename.find_last_of('/');
                    size_t pos2 = filename.find_last_of('.');
                    s += filename.substr(pos+1,pos2);
                    s += "_";
                    s += std::to_string(ts->getPathValue());
                    s += ".txt";
                    if (FileClass::saveToFile(s,path,matrix->getNodesCount()+1))
                        cout << "ZAPISANO DO PLIKU\n";
                    else
                        cout << "ERROR IN SAVE\n";
                    delete ts;
                }
            }
                break;
            case 6:
                if (matrix != nullptr) {
                    cout << "Pobieranie sciezki z pliku tekstowego. Podaj nazwe pliku: ";
                    {
                        string filename2;
                        cin >> filename2;
                        vector<int> path2(FileClass::readPathFile(filename2));
                        if (!path2.empty())   // jeśli nie wystąpił błąd, usuń macierz i zastąp ją nową
                        {
                            path = path2;

                            int helpCount = 0;
                            for (int i = 0; i < matrix->getNodesCount(); i++) {
                                //zliczanie całej wartości ścieżki. Jeśli dojdziemy do ostatniego wierzchołka w ścieżce, policz powrót
                                helpCount += matrix->getWsk()[path[i]][path[i + 1]];
                            }
                            cout << "KOSZT: " << helpCount;
                            cout << endl;
                        } else
                            cout << "ERROR IN READ" << endl;
                    }
                } else
                    cout <<"BRAK MACIERZY\n";
                break;
            case 0:
                system("cls");
                break;
            default:
                cout << endl << "Podano niepoprawna opcje!" << endl;
                break;
        }
        cout << endl << endl;
    } while (chooseOption);

    //usuń tablice po zakonczeniu
    delete matrix;
}

void Menu::autoBF(int* data, int dataCount)
{
    double time= 0.0;
    fstream file;
    Timer timer;
    AdjacencyMatrix* matrix;

    file.open("../Files/Output/test_BF.txt",ios::out);
    //ilość wierzchołków;średnia z 100 pomiarów
    for (int i = 0; i < dataCount; ++i) {
        file << data[i] <<';';
        for (int k = 0; k < 100; ++k) {
            cout <<"TEST (BF): " <<data[i] <<" wierzcholkow, "<<k<<" instancja: ";
            matrix = new AdjacencyMatrix(data[i],0, true);
            BruteForce* bf = new BruteForce(matrix);
            timer.run();
            int* heap = bf->main();
            timer.stop();
            time += timer.getTimeMs();
            cout << "X\n";
            delete matrix;
            delete bf;
            delete [] heap;
        }
        file << time/100 << '\n';
        time = 0.0;
    }
    file.close();
}

void Menu::autoBB(int *data, int dataCount) {
    double time= 0.0;
    fstream file;
    Timer timer;
    AdjacencyMatrix* matrix;

    file.open("../Files/Output/test_BB.txt",ios::out);
    //ilość wierzchołków;średnia z 100 pomiarów;ilość obliczonych w czasie 20s
    for (int i = 0; i < dataCount; ++i) {
        file << data[i] <<';';
        int counter = 0;
        for (int k = 0; k < 100; ++k) {
            cout <<"TEST (BB): " <<data[i] <<" wierzcholkow, "<<k<<" instancja: ";
            matrix = new AdjacencyMatrix(data[i],0, true);
            BranchAndBound* bb = new BranchAndBound(matrix);

            timer.run();

            list<NodeBB*> listEnd = bb->mainStop();
            timer.stop();

            if (!listEnd.empty())
            {
                time += timer.getTimeMs();
                counter++;
                cout << counter;
                cout << "X\n";
            } else
                cout << " -\n";

            bb->clear();
            delete matrix;
            delete bb;
        }
        file << time/counter << ";" <<counter <<'\n';
        time = 0.0;
    }
    file.close();
}

void Menu::autoDP(int *data, int dataCount) {
    double time= 0.0;
    fstream file;
    Timer timer;
    AdjacencyMatrix* matrix;
    file.open("../Files/Output/test_DP.txt",ios::out);
    //ilość wierzchołków;średnia z 100 pomiarów
    for (int i = 0; i < dataCount; ++i) {
        file << data[i] <<';';
        for (int k = 0; k < 100; ++k) {
            cout <<"TEST (DP): " <<data[i] <<" wierzcholkow, "<<k<<" instancja: ";
            matrix = new AdjacencyMatrix(data[i],0, true);
            DynamicPrograming* dp = new DynamicPrograming(matrix);
            timer.run();
            dp->main();
            timer.stop();
            time += timer.getTimeMs();
            cout << "X\n";
            delete matrix;
            delete dp;
        }
        file << time/100 << '\n';
        time = 0.0;
    }
    file.close();
}

void Menu::autoTS(string data[],int timeData[], int iterationsNoChange, int dataCount, int typeNeigh)
{
    fstream file;
    TabuSearch* ts;
    AdjacencyMatrix* matrix;
    vector<int> bestPath;
    int bestPathValue = INT32_MAX;
    int timeBest= 0;
    int l = 0;

    if (typeNeigh == 0)
    {
        l = 1;
        typeNeigh = 3;
    }
    else
        l = typeNeigh;

    file.open("../Files/Output/test_TS.txt",ios::out | ios::app);
    //nazwa pliku;najlepsze rozwizanie;czas;sąsiedztwo
    for (; l <= typeNeigh; ++l) {
        for (int i = 0; i < dataCount; ++i) {
            file << data[i] << ';';
            matrix = FileClass::matrixFromFile(data[i]);
            bestPath.clear();
            bestPath.resize(matrix->getNodesCount() + 1);
            for (int k = 0; k < 10; ++k) {
                cout << "TEST (TS): " << data[i] << ", " << k << " proba: ";
                ts = new TabuSearch(matrix, timeData[i], iterationsNoChange, 4, l);
                ts->start();
                if (ts->getPathValue() < bestPathValue) {
                    bestPathValue = ts->getPathValue();
                    timeBest = ts->getTime();

                    for (int j = 0; j < matrix->getNodesCount() + 1; ++j) {
                        bestPath[j] = ts->getShortestPath()[j];
                    }
                }
                cout << "X\n";
                delete ts;
            }
            string s = "../Files/Output/ts_";
            size_t pos = data[i].find_last_of('/');
            size_t pos2 = data[i].find_last_of('.');
            s += data[i].substr(pos + 1, pos2);
            s += "_";
            s += std::to_string(ts->getPathValue());
            s += ".txt";
            if (FileClass::saveToFile(s, bestPath, matrix->getNodesCount() + 1))
                cout << "ZAPISANO DO PLIKU\n";
            else
                cout << "ERROR IN SAVE\n";

            file << bestPathValue << ";" << timeBest << ";" << typeNeigh << '\n';

            bestPathValue = INT32_MAX;
        }
    }
    file.close();
}