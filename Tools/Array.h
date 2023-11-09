#pragma once

#include "../Tools/Timer.h"
#include "../Tools/Generator.h"

class Array
{
private:
    Generator generator;
	int* wsk;					//wska�nik tablicy
	unsigned size;					//wielko�� tablicy

public:
	Array();					//konstruktor domy�lny
	~Array();					//destruktor

    void addFirst(int);		    //dodaj element na pierwszej pozycji
    bool addIn(int, int);		//dodaj element w �rodku tablicy
    void addLast(int);			//dodaj element na ko�cowej pozycji
	bool deleteFirst();			//usu� element na pierwszej pozycji
	bool deleteIn(int);			//usu� element w �rodku tablicy
	bool deleteLast();			//usu� element na ko�cowej pozycji
    int search(int);			//wyszukaj dany element w tablicy
    int getByIndex(int);		//wyszukaj dany element w tablicy
    void print();				//wy�wietlanie tablicy w konsoli
    void createTableTest(unsigned dataSize);				//wy�wietlanie tablicy w konsoli

    unsigned getSize();				//zwr�� wielko�� tablicy
	void setWsk(int*);				//zwr�� wska�nik
	void setSize(int);				//zwr�� wska�nik
};


