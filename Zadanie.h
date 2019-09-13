#ifndef ZADANIE_H
#define ZADANIE_H

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <queue>
#include <string>

using namespace std;

class Zadanie
{
public:
	int r, p, q, nr, t_on;

	friend ostream & operator<< (ostream & strumWyj, const Zadanie & doWypisania);
	static bool compR(const Zadanie &it1, const Zadanie &it2) {
        return it1.r > it2.r;  //UWAGA NA KIERUNEK!!
    }
	static bool compQ(const Zadanie &it1, const Zadanie &it2){
        return it1.q < it2.q;    ///UWAGA NA KIERUNEK!
    }

	Zadanie(int rr, int pp, int qq, int nnr);
	Zadanie(void);
	~Zadanie(void);
};

#endif

