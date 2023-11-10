#include "DynamicPrograming.h"
#include <iostream>
using namespace std;
DynamicPrograming::DynamicPrograming(AdjacencyMatrix *martrix) : maskAllVisited((1 << martrix->getNodesCount()) - 1), matrix(martrix),
result(0), subProblems(vector<vector<int>>(martrix->getNodesCount(),vector<int>((1<<martrix->getNodesCount()),-1))),
tablePath(vector<vector<int>>(martrix->getNodesCount(),vector<int>((1<<martrix->getNodesCount()),-1)))
{
}
void DynamicPrograming::main() {
    result = DPFunction(1<<matrix->getStartNode(),matrix->getStartNode());
}

int DynamicPrograming::DPFunction(int mask, int node) {
    //jeśli wszystkie miasta zostały odwiedzone, to zwróć drogę do początkowego wierzchołka
    if (mask == maskAllVisited)
    {
        return matrix->getWsk()[node][0];
    }
    //jeśli istnieje już rozwiązany podproblem --> zwróć wartość
    if (subProblems[node][mask] != -1)
    {
        return subProblems[node][mask];
    }

    int subResult = INT32_MAX;

    //przeszukiwanie nieodwiedzonych miast, rozwiązywanie podproblemów
    for (int i = 0; i < matrix->getNodesCount(); ++i) {
        //jeśli miasto nie jest odwiedzone --> rozwiąż podproblem
        //Operacja AND na masce i 1 na pozycji danego miasta
        if ((mask&(1<<i)) == 0)
        {
            //rozwiąż kolejny podproblem
            int newResult = matrix->getWsk()[node][i] + DPFunction(mask|(1<<i),i);
            if (min(subResult,newResult) == newResult)
            {
                subResult = min(subResult,newResult);
                tablePath[node][mask] = i;
            }
        }
    }
    subProblems[node][mask] = subResult;

    return subResult;
}

void DynamicPrograming::printResults() {
    cout << "Sciezka: \n";
    int maskHelp = 1;
    cout << matrix->getStartNode()<< " -> ";
    int helpNode = tablePath[matrix->getStartNode()][maskHelp];
    while (helpNode != -1)
    {
        cout << helpNode << " -> ";
        maskHelp = maskHelp | (1<<helpNode);
        helpNode = tablePath[helpNode][maskHelp];
    }
    cout << matrix->getStartNode() << endl;
    cout << "Koszt: " << result << endl;
}



