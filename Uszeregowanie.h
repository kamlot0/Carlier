#ifndef USZEREGOWANIE_H
#define USZEREGOWANIE_H

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

class Uszeregowanie
{
public:
	vector<Zadanie> listaZadan; //vector przechowujacy zadaną kolejnosc wykonywania zadan
	int n;						//ilosc wczytanych zadan
	int Cmax;					//moment zakonczenia q ostatniego zadania
	int LB;						//wartosc Cmax zwrocona przez algorytm Schrage z przerywaniami
	int a,b;					//indeksy początku i konca sciezki krytycznej
	int c;						//indeks zadania interferencyjnego
	int sLB;					//szybki LB. wg tego permutacje są kopcowane;


	int Schrage();				//algorytm Schrege'a: modyfikuje kolejnosc listyZadan

	int SciezkaKrytyczna();		//metoda odnajduje w liscieZadan sciezke krytyczna.
								//indeksy poczatku i konca przypisuje do pol a i b;
	int ZadanieInterferencyjne(); //metoda odnajduje zadanie interferencyjne w sciezce krytycznej
								  // wymaga poprawnie oznaczonej sciezki przez pola a i b.
								  // modyfikuje pole c;
	int h(int aa, int bb);		// metoda zwraca wartosc rmin+sumap+qmin dla zadanego przedziału;

	int rMin(int aa, int bb);	//metoda wyszukuje najmniejszy r z zadanego przedziału

	int qMin(int aa, int bb);	//metoda wyszukuje najmniejsze q z zadanego przedziału;

	int sumaP(int aa, int bb);  //metoda zwraca sume p z zadanego przedziału

	int rMinBloku();			//Trzy metody zwracają odpowiednie parametry BlokuK - zadan
								//od pierwszego za zadaniem interferencyjnym do ostatniego na
	int qMinBloku();			//sciezce krytycznej.

	int sumaPBloku();

	int SchragePtm();			//metoda zwraca wartosc Cmax algorytmu Schrage z przerywaniami. Modyfikuje pole LB

	int szybkiLB();				//metoda generuje szybki LB;

	void testyEliminacyjne(int UB);

	static bool cmpsLB (const Uszeregowanie & p1, const Uszeregowanie & p2) {
		return p1.sLB < p2.sLB;
	}

	friend ostream & operator << (ostream & strumienWyjsciowy, Uszeregowanie & doWypisania);


	Uszeregowanie (char * nazwa_pliku);
	Uszeregowanie(void);
	~Uszeregowanie(void);
};

#endif

