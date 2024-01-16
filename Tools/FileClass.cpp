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

AdjacencyMatrix* FileClass::matrixFromFileH(const string& filename)
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
bool FileClass::searchInFile(ifstream& inputFile, const string& toFind) {
    string tmp;
    string toFind2;
    if (toFind.substr(toFind.size() - 1, 1) == ":") {
        toFind2 = toFind.substr(0, toFind.size() - 1);
    }
    int check = 20;
    do {
        inputFile >> tmp;
        check--;
    }     while (tmp != toFind && tmp != toFind2 && check > 0);
    if (check == 0) return false;
    return true;
}
AdjacencyMatrix *FileClass::matrixFromFile(const string& fileName) {
    string s;
    ifstream file(fileName);
    if (!file)
    {
        cout << "Error: Unable to open a file" << endl;
    }
    else
    {
        if (fileName.find(".txt") != std::string::npos)
        {
            int* tab = new int[1];
            AdjacencyMatrix* matrix = nullptr;

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
        else if (fileName.find(".atsp") != std::string::npos)
        {
            if (!searchInFile(file, "DIMENSION:")) return nullptr;
            int nodesCount;

            file >> nodesCount;
            AdjacencyMatrix* matrix = new AdjacencyMatrix(nodesCount,0, false);  //stworzenie nowej macierzy

            if (!searchInFile(file, "EDGE_WEIGHT_TYPE:")) return nullptr;
            if (!searchInFile(file, "EXPLICIT")) return nullptr;
            if (!searchInFile(file, "EDGE_WEIGHT_FORMAT:")) return nullptr;
            if (!searchInFile(file, "FULL_MATRIX")) return nullptr;

            if (!searchInFile(file, "EDGE_WEIGHT_SECTION")) return nullptr;

            for (int i = 0; i < nodesCount; i++)
            {
                for (int j = 0; j < nodesCount; j++)
                {
                    file >> matrix->getWsk()[i][j];
                }
            }
            for (int i = 0; i < nodesCount; i++)
            {
                for (int j = 0; j < nodesCount; j++)
                {
                    if (i == j) matrix->getWsk()[i][j] = -1;
                }
            }
            return matrix;
        }
    }
    return nullptr;
}

bool FileClass::saveToFile(const string& fileName, std::vector<int> &path, int nodesCount) {
    fstream file;
    file.open(fileName,ios::out);
    if (file.is_open())
    {
        file << nodesCount << endl;
        for (int i = 0; i < nodesCount; ++i) {
            file << path[i] << endl;
        }
        return true;
    }
    return false;
}

vector<int> FileClass::readPathFile(const string& fileName) {
    ifstream file;
    int* tab = new int[1];
    vector<int> path;
    int size=0;
    file.open(fileName.c_str());

    if(file.is_open())
    {
        if(file_read_line(file, tab, 1))
        {
            size = tab[0];
            path.resize(size);
            for(int i = 0; i < size; i++)
            {
                if(file_read_line(file, tab, 1))
                {
                    path[i] = tab[0];
                }
                else
                {
                    delete[] tab;
                    cout << "File error - READ NODE" << endl;
                    path.clear();
                    return path;
                }
            }
        }
        else
        {
            cout << "File error - READ INFO" << endl;
            path.clear();
        }
        file.close();
    }
    else
    {
        cout << "File error - OPEN" << endl;
        path.clear();
    }

    return path;
}

