#include <iostream>
#include "../Graphs/AdjacencyMatrix.h"
#include <vector>

using namespace std;
class FileClass
{
    static bool file_read_line(ifstream &file, int tab[], int size);
public:
    static AdjacencyMatrix* matrixFromFile(const string& filename);
    static AdjacencyMatrix* matrixFromFileH(const string& filename);
    static bool searchInFile(ifstream& inputFile, const string& toFind);
    static bool saveToFile(const string& fileName,std::vector<int> &path, int nodesCount);
    static vector<int> readPathFile(const string& fileName);
};