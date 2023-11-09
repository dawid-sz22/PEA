#include <iostream>
#include "../Graphs/AdjacencyMatrix.h"

using namespace std;
class FileClass
{
    static bool file_read_line(ifstream &file, int tab[], int size);
public:
    static AdjacencyMatrix* matrixFromFile(string filename);
};