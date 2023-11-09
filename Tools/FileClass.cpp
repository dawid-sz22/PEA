#include "FileClass.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

bool FileClass::file_read_line(ifstream &file, int tab[], int size) //wczytywanie danych z pliku w okreœlonej iloœci
{
    string s;
    getline(file, s);

    if(file.fail() || s.empty())
        return(false);

    istringstream in_ss(s);

    for(int i = 0; i < size; i++)
    {
        in_ss >> tab[i];
        if(in_ss.fail())
            return(false);
    }
    return(true);
}

AdjacencyMatrix* FileClass::matrixFromFile(string filename)
{
    ifstream file;
    int* tab = new int[1];
    AdjacencyMatrix* matrix = nullptr;
    file.open(filename.c_str());

    if(file.is_open())
    {
        if(file_read_line(file, tab, 1))
        {
            matrix = new AdjacencyMatrix(tab[0],0, false);        //stworzenie nowej macierzy
            tab = new int [tab[0]];                                                 //zmieniamy rozmiar tablicy na rozmiar grafu
            for(int i = 0; i < matrix->getNodesCount(); i++)
                if(file_read_line(file, tab, matrix->getNodesCount()))
                {
                    for (int j = 0; j < matrix->getNodesCount(); ++j) {
                        matrix->getWsk()[i][j] = tab[j];
                    }
                }
                else
                {
                    delete matrix;
                    cout << "File error - READ NODE" << endl;
                    return nullptr;
                }
        }
        else
            cout << "File error - READ INFO" << endl;
        file.close();
    }
    else
        cout << "File error - OPEN" << endl;

    return matrix;
}


