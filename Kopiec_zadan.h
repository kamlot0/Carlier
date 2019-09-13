
#ifndef KOPIEC_ZADAN_H
#define KOPIEC_ZADAN_H

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <queue>
#include <string>

#include "Zadanie.h"

using namespace std;

class Kopiec_zadan
{
private:
	Zadanie * tablicaElementow;
	int iloscElementow;
	bool (*funkcjaPorownujaca)(const Zadanie &, const Zadanie &);
public:
	int push(Zadanie element);
	Zadanie pop();
	Zadanie top();
	bool empty();
	void wypisz();
	Kopiec_zadan (bool (*compare)(const Zadanie &, const Zadanie &));
};

#endif
