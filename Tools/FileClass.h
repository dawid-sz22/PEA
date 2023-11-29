#include <iostream>
#include "../Graphs/AdjacencyMatrix.h"

using namespace std;
class FileClass
{
    static bool file_read_line(ifstream &file, int tab[], int size);
public:
    static AdjacencyMatrix* matrixFromFile(string filename);
    static AdjacencyMatrix* matrixFromFileH(string filename);
    static bool searchInFile(ifstream& inputFile, string toFind);
};