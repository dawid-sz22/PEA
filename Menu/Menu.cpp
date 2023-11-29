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
        cout << "1. Testy manualne (Algorytmy dokładne)\n";
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
    double stop = 0.0;
    int* path = nullptr;
    int help = 0;

    do
    {
        cout << "1. Wczytaj graf z pliku\n";
        cout << "2. Wprowadz kryterium stopu (czas w ms)\n";
        cout << "3. Wybór sasiedztwa ? \n";
        cout << "4. Tabu Search\n";
        cout << "7. Zapisz sciezke do .txt\n";
        cout << "8. Wczytaj sciezke z .txt i podaj koszt\n";
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
            case 2: //Kryterium stopu
            {
                cout << "\nPodaj czas: ";
                cin >> stop;
            }
                break;
            case 3: //sąsiedztwo
            {

            }
                break;
            case 4: //Tabu search
            {
                if (matrix == nullptr) {
                    cout << "NIE WCZYTANO GRAFU!\n";
                } else {
                    TabuSearch* ts = new TabuSearch(matrix,stop);

                    delete[] path;
                    path = ts->start();
                    ts->printResults();
                    delete ts;
                }
            }
                break;
            case 7:
            {
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
