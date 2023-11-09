#include "Array.h"
#include <iostream>

Array::Array() : wsk(nullptr) , size(0)
{}

Array::~Array()
{
	if (wsk != nullptr)
		delete[] wsk;
}

void Array::addFirst(int numberToAdd)
{
	if (wsk != nullptr)					//je�li istnieje tablica
	{
		int* newWsk = new int[size + 1];	//utworzenie nowej tablicy o rozmiarze size + 1
		newWsk[0] = numberToAdd;			//dodanie podanej danej na sam pocz�tek tablicy
	
		for (unsigned i = 0; i < size; i++)
		{
			newWsk[i + 1] = wsk[i];		//kopiowanie element�w ze starej tablicy do nowej
		}

		delete[] wsk;					//usuwanie starej tablicy z pami�ci

		size++;							//zwi�kszenie wielko�ci tablicy o 1
		wsk = newWsk;					//przypisanie adresu nowej tablicy do zmiennej wsk
	}
	else
	{
		wsk= new int[size + 1];			//utworzenie nowej tablicy o rozmiarze size + 1
		wsk[0] = numberToAdd;			//dodanie podanej danej na sam pocz�tek tablicy
		size++;							//zwi�kszenie wielko�ci tablicy o 1
	}
}

bool Array::addIn(int numberToAdd, int index)
{

	if (wsk != nullptr && (index < size && index >= 0))						//je�li istnieje tablica i indeks mie�ci si� pomi�dzy (0 - size)
	{
		int* newWsk = new int[size + 1];	//utworzenie nowej tablicy o rozmiarze size + 1
		newWsk[index] = numberToAdd;		//dodanie elementu na zadany indeks
	
		for (unsigned i = 0; i < index; i++)
		{
			newWsk[i] = wsk[i];				//kopiowanie element�w ze starej tablicy do nowej (od 0 do zadanego indeksu-1)
		}

		for (unsigned i = index; i < size; i++)
		{
			newWsk[i + 1] = wsk[i];			//kopiowanie element�w ze starej tablicy do nowej (od zadanego indeksu do samego ko�ca)
		}

		delete[] wsk;						//usuwanie starej tablicy z pami�ci

		size++;								//zwi�kszenie wielko�ci tablicy o 1
		wsk = newWsk;						//przypisanie adresu nowej tablicy do zmiennej wsk
        return true;
	}
	else if(index == size)
	{
        if (index==0)
            addFirst(numberToAdd);
        else
            addLast(numberToAdd);
        return true;
	}
    return false;
}

void Array::addLast(int numberToAdd)
{
	if (wsk != nullptr)						//je�li istnieje tablica
	{
		int* newWsk = new int[size + 1];	//utworzenie nowej tablicy o rozmiarze size + 1
		newWsk[size] = numberToAdd;			//dodanie podanej danej na sam koniec tablicy

		for (unsigned i = 0; i < size; i++)
		{
			newWsk[i] = wsk[i];				//kopiowanie element�w ze starej tablicy do nowej
		}

		delete[] wsk;						//usuwanie starej tablicy z pami�ci

		size++;								//zwi�kszenie wielko�ci tablicy o 1
		wsk = newWsk;						//przypisanie adresu nowej tablicy do zmiennej wsk
	}
	else
	{
		wsk = new int[size + 1];		//utworzenie nowej tablicy o rozmiarze size + 1
		wsk[0] = numberToAdd;			//dodanie podanej danej na sam pocz�tek tablicy
		size++;							//zwi�kszenie wielko�ci tablicy o 1
	}
}

bool Array::deleteFirst()
{
	if (wsk != nullptr && size > 1)					//je�li istnieje tablica i jest wi�ksza ni� 1
	{
		int* newWsk = new int[size - 1];			//utworzenie nowej tablicy o rozmiarze size - 1

		for (unsigned i = 1; i < size; i++)
		{
			newWsk[i - 1] = wsk[i];					//kopiowanie element�w ze starej tablicy do nowej
		}

		delete[] wsk;								//usuwanie starej tablicy z pami�ci

		size--;										//zmniejszenie wielko�ci tablicy o 1
		wsk = newWsk;								//przypisanie adresu nowej tablicy do zmiennej wsk

		return true;
	}
	else if (wsk != nullptr && size == 1)
	{
        delete[] wsk;
		size--;
        wsk = nullptr;

		return true;
	}
	else
	{
		return false;
	}
}

bool Array::deleteIn(int index)
{
	if (wsk != nullptr && (index < size && index >= 0))		//je�li istnieje tablica i jest wi�ksza ni� 1 oraz indeks mie�ci si� pomi�dzy (0 - size)
	{
		int* newWsk = new int[size - 1];			//utworzenie nowej tablicy o rozmiarze size - 1

		for (unsigned i = 0; i < index; i++)
		{
			newWsk[i] = wsk[i];						//kopiowanie element�w ze starej tablicy do nowej
		}

		for (unsigned i = index + 1; i < size; i++)
		{
			newWsk[i - 1] = wsk[i];					//kopiowanie element�w ze starej tablicy do nowej
		}
		delete[] wsk;								//usuwanie starej tablicy z pami�ci

		size--;										//zmniejszenie wielko�ci tablicy o 1
		wsk = newWsk;								//przypisanie adresu nowej tablicy do zmiennej wsk

		return true;
	}else if(index == size - 1)
    {
        if (index==0)
            deleteFirst();
        else
            deleteLast();
        return true;
    }

    return false;
}

bool Array::deleteLast()
{
	if (wsk != nullptr && size > 1)					//je�li istnieje tablica i jest wi�ksza ni� 1
	{
		int* newWsk = new int[size - 1];			//utworzenie nowej tablicy o rozmiarze size - 1

		for (unsigned i = 0; i < size-1; i++)
		{
			newWsk[i] = wsk[i];						//kopiowanie element�w ze starej tablicy do nowej
		}

		delete[] wsk;								//usuwanie starej tablicy z pami�ci

		size--;										//zmniejszenie wielko�ci tablicy o 1
		wsk = newWsk;								//przypisanie adresu nowej tablicy do zmiennej wsk

		return true;
	}
	else if (wsk != nullptr && size == 1)
	{
        delete[] wsk;
		size--;
        wsk = nullptr;

		return true;
	}
	else
	{
		return false;
	}
}

int Array::search(int numberToSearch)
{
	if (size > 0)
	{
		for (int i = 0; i < size; i++)
		{
			if (wsk[i] == numberToSearch)			//je�li kt�ry� element jest r�wny poszukiwanemu
            {
                return i;
            }
		}
		return -1;
	}
	else {
        return -1;
    }
}

unsigned Array::getSize()
{
	return size;
}

void Array::print()
{
    if (size==0)
    {
        printf("PUSTA TABLICA");
        return;
    }
	for (unsigned i = 0; i < size; i++)
	{
        printf("%4u|%-6d", i, wsk[i]);

        if (!((i+1) % 10))
			printf("\n");
	}
}
void Array::setWsk(int* newWsk)
{
    delete[] wsk;
	wsk = newWsk;
}
void Array::setSize(int size)
{
	this->size = size;
}


void Array::createTableTest(unsigned dataSize) {
    delete[] wsk;
    size = 0;
    wsk = new int [dataSize];
    for (unsigned i = 0; i < dataSize; ++i) {
        wsk[i] = generator.getNumber();
        size ++;
    }
}

int Array::getByIndex(int index) {
    return wsk[index];
}
