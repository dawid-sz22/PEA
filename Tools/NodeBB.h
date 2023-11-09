#ifndef P1_NODEBB_H
#define P1_NODEBB_H


class NodeBB {
public:
    int numberOfNode;       //rzeczywisty numer wierzcho�ka w grafie
    int** wsk;              //wska�nik na tablice w Branch&Bound
    NodeBB* father;         //wska�nik na ojca danego wierzcho�ka, aby odtworzy� �cie�k�
    int lowerBound;         //dolne ograniczenie wierzcho�ka
    int level;              //poziom na jakim znajduje si� wierzcho�ek w drzewie
    int nodesCount;         //liczba wierzcho�k�w
    NodeBB(int node, int level,int numberOfNodes, NodeBB* father);
    ~NodeBB();
};


#endif //P1_NODEBB_H
