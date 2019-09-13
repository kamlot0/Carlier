#ifndef KOPIEC_USZEREGOWANIA_H
#define KOPIEC_USZEREGOWANIA_H

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <queue>
#include <string>

#include "Zadanie.h"
#include "Uszeregowanie.h"

using namespace std;

class Kopiec_uszeregowania
{
private:
	Uszeregowanie * tablicaElementow;
	int iloscElementow;
	bool (*funkcjaPorownujaca)(const Uszeregowanie &, const Uszeregowanie &);
public:
	int push(Uszeregowanie element);
	Uszeregowanie pop();
	Uszeregowanie top();
	bool empty();
	void wypisz();
	Kopiec_uszeregowania (bool (*compare)(const Uszeregowanie &, const Uszeregowanie &));
};

#endif

