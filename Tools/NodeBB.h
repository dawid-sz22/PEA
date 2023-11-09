#ifndef P1_NODEBB_H
#define P1_NODEBB_H


class NodeBB {
public:
    int numberOfNode;       //rzeczywisty numer wierzcho³ka w grafie
    int** wsk;              //wskaŸnik na tablice w Branch&Bound
    NodeBB* father;         //wskaŸnik na ojca danego wierzcho³ka, aby odtworzyæ œcie¿kê
    int lowerBound;         //dolne ograniczenie wierzcho³ka
    int level;              //poziom na jakim znajduje siê wierzcho³ek w drzewie
    int nodesCount;         //liczba wierzcho³ków
    NodeBB(int node, int level,int numberOfNodes, NodeBB* father);
    ~NodeBB();
};


#endif //P1_NODEBB_H
