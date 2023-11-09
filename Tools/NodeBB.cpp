#include "NodeBB.h"

NodeBB::NodeBB(int node, int level, int numberOfNodes, NodeBB *father): numberOfNode(node), level(level), lowerBound(0),
father(father),
table(std::vector<std::vector<int>>(numberOfNodes,std::vector<int>(numberOfNodes,0)))
{
    if (father!= nullptr)
    {
        for (int i = 0; i < numberOfNodes; ++i) {
            for (int j = 0; j < numberOfNodes; ++j) {
                table[i][j] = father->table.at(i).at(j);
            }
        }
    }

}
