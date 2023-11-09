#include "Menu.h"
#include "../Graphs/AdjacencyMatrix.h"
#include "../Tools/FileClass.h"
#include "../Tools/Timer.h"
#include "../Algorithms/BranchAndBound.h"
#include "../Algorithms/BruteForce.h"
#include <iostream>
#include <fstream>
#include <thread>

using namespace std;

void Menu::showMenu()
{
    int choose;
    do {
        cout << "Asymetryczny problem komiwojazera (ATSP)\n";
        cout << "1. Testy manualne\n";
        cout << "2. Testy automatyczne\n";
        cout << "0. Zakoncz program\n";
        cout << "Wybierz opcje: ";

        cin >> choose; //wybrana opcja

        switch (choose)
        {
            case 1:
                Menu::showMenuManual();
                break;
            case 2:
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
    AdjacencyMatrix* matrix = nullptr;
    Timer timer;
    double time= 0.0;
    fstream file;

    int chooseOption = 0;
    int dataCount;

    cout << "Podaj rozmiar problemu (X problemow po 100 losowych reprezentacji) : ";
    cin >> dataCount;

    int* data = new int [dataCount];

    for (int i = 0; i < dataCount; ++i) {
        cout << i+1 << ": ";
        cin >> data[i];
    }


    do
    {
        cout << "1. Brute Force\n";
        cout << "2. Branch&Bound\n";
        cout << "0. Wroc\n";
        cout << "Wybierz opcje: ";
        cin >> chooseOption; //wybrana opcje

        switch (chooseOption)
        {
            case 1: //Brute Force
            {
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
                break;
            case 2: //Branch&Bound
            {
                file.open("../Files/Output/test_BB.txt",ios::out);
                //ilość wierzchołków;średnia z 100 pomiarów
                for (int i = 0; i < dataCount; ++i) {
                    file << data[i] <<';';
                    for (int k = 0; k < 100; ++k) {
                        cout <<"TEST (BB): " <<data[i] <<" wierzcholkow, "<<k<<" instancja: ";
                        matrix = new AdjacencyMatrix(data[i],0, true);
                        BranchAndBound* bb = new BranchAndBound(matrix);
                        timer.run();
                        bb->main();
                        timer.stop();
                        time += timer.getTimeMs();
                        cout << "X\n";
                        delete matrix;
                        delete bb;
                    }
                    file << time/100 << '\n';
                    time = 0.0;
                }
                file.close();
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

                    for (NodeBB* node:listEnd) {
                        delete node;
                    }

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

                    atomic<bool> stopFlag (false);
                    auto stopFunction = [](atomic<bool> &stopFlag)
                    {
                        for (int i = 0; i < 2; ++i) {
                            std::this_thread::sleep_for(chrono::seconds (10));
                            if (stopFlag.load())
                                return;
                        }
                        stopFlag.store(true);
                    };
                    thread waitThread(stopFunction, ref(stopFlag));
                    timer.run();

                    list<NodeBB*> listEnd = bb->main(stopFlag);

                    timer.stop();
                    waitThread.detach();
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


                    delete bb;
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