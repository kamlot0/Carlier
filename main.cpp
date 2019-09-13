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

//#include "Kopiec_zadan.h"
#include "Kopiec_uszeregowania.h"

using namespace std;



int Carlier(char * pliki, char * pliko);

int main(int argc, char** argv)
{

	Carlier("in50.txt", "out50.txt");
	Carlier("in100.txt", "out100.txt");
	Carlier("in200.txt", "out200.txt");

	return 0;

}

int Carlier(char * pliki, char * pliko) {
	int LB, UB;
	bool znalezionoOptymalne = false;
	Uszeregowanie permut0(pliki);
	Uszeregowanie optymalna, aktualna, potomek1, potomek2;
	permut0.sLB=1; //i tak jest zdejmowana odrazu

	Kopiec_uszeregowania kolejkaCarliera(&Uszeregowanie::cmpsLB);
	UB=permut0.Schrage();
	LB=permut0.SchragePtm();

	kolejkaCarliera.push(permut0);
	optymalna=permut0;
	while (!kolejkaCarliera.empty()) { //&&(!znalezionoOptymalne) ?
		aktualna=kolejkaCarliera.top();
		kolejkaCarliera.pop();

		if (aktualna.SchragePtm() < UB){			 //najlepszy możliwy jest lepszy od znalezionego UB - dzielimy problem
			aktualna.Schrage();
			if (aktualna.Cmax < UB) {				//układamy wg. algorytmu Schrage. Jezeli znaleźliśmy lepsze rozwiazanie - zapisujemy je.
				UB=aktualna.Cmax;
				optymalna=aktualna;
			}
			aktualna.SciezkaKrytyczna();
			if(aktualna.ZadanieInterferencyjne()) {

				potomek1=potomek2=aktualna;
				potomek1.listaZadan[potomek1.c].r=potomek1.rMinBloku()+potomek1.sumaPBloku();
				potomek2.listaZadan[potomek2.c].q=potomek2.qMinBloku()+potomek2.sumaPBloku();

//				potomek1.szybkiLB();
	//			potomek2.szybkiLB();


				kolejkaCarliera.push(potomek1);
				kolejkaCarliera.push(potomek2);

			}
			else {
				znalezionoOptymalne=true;
				cout<<"znaleziono lokalnie optymalne: "<< aktualna.Cmax<<endl;
			}

		}
	}

	cout<<"Cmax znalezionego: "<<optymalna.Cmax<<endl;
	ofstream plikout(pliko);

	plikout<<"1 "<<optymalna.n<<endl;
	for(int i=0;i<optymalna.n;i++){
		plikout<<optymalna.listaZadan[i].nr<<" ";
	}
	plikout<<endl<<optymalna.Cmax;
	plikout.close();

	return optymalna.Cmax;
}
