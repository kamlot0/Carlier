
#include "Kopiec_zadan.h"

using namespace std;

Kopiec_zadan::Kopiec_zadan(bool (*cmp)(const Zadanie & ,const  Zadanie & ))
{
	iloscElementow = 0;
	funkcjaPorownujaca = cmp;
	tablicaElementow=NULL;
}

int Kopiec_zadan::push(Zadanie element)
{

	if (iloscElementow==0) { //dodajemy na szczyt kopca
		tablicaElementow = new Zadanie[1];
		tablicaElementow[iloscElementow]=element;
		iloscElementow++;
		return 1;
	}
	else {
		Zadanie * temp = tablicaElementow;
		tablicaElementow = new Zadanie [iloscElementow+1];
		copy(temp, temp+iloscElementow, tablicaElementow);
		delete [] temp;

		int aktualnyIndeks=iloscElementow;
		int indeksOjca=iloscElementow/2;
		Zadanie tmp;

		tablicaElementow[iloscElementow]=element;
		while ((indeksOjca>=0) && (funkcjaPorownujaca(tablicaElementow[indeksOjca],tablicaElementow[aktualnyIndeks])))
		{
			tmp = tablicaElementow[indeksOjca];
			tablicaElementow[indeksOjca]=tablicaElementow[aktualnyIndeks];
			tablicaElementow[aktualnyIndeks]=tmp;

			aktualnyIndeks=indeksOjca;
			indeksOjca/=2;
		}
		iloscElementow++;
		return iloscElementow;
	}
}

Zadanie Kopiec_zadan::pop()
{
	Zadanie doZwrotu;
	if (iloscElementow==0)
	{
		cerr<<"Brak elementow na kopcu!"<<endl;
		return doZwrotu;
	}
	doZwrotu = tablicaElementow[0];
	tablicaElementow[0]=tablicaElementow[iloscElementow-1];
	int aktualnyIndeks=0;

	while ((((aktualnyIndeks+1)*2-1<iloscElementow-1)&&(funkcjaPorownujaca (tablicaElementow[aktualnyIndeks],tablicaElementow[(aktualnyIndeks+1)*2-1]))) || //jezeli ktores z dzieci jest wieksze - zamien z wiekszym z nich
		(((aktualnyIndeks+1)*2<iloscElementow-1)&&(funkcjaPorownujaca (tablicaElementow[aktualnyIndeks],tablicaElementow[(aktualnyIndeks+1)*2]))))
		 {
			if (funkcjaPorownujaca(tablicaElementow[(aktualnyIndeks+1)*2-1], tablicaElementow[(aktualnyIndeks+1)*2])) //jeżeli prawe dziecko jest wieksze
			{																											// to z nim zamieniamy aktualny indeks
				Zadanie tmp = tablicaElementow[(aktualnyIndeks+1)*2];
				tablicaElementow[(aktualnyIndeks+1)*2]=tablicaElementow[aktualnyIndeks];
				tablicaElementow[aktualnyIndeks]=tmp;
				aktualnyIndeks=(aktualnyIndeks+1)*2;
			}
			else
			{
				Zadanie tmp = tablicaElementow[(aktualnyIndeks+1)*2-1];
				tablicaElementow[(aktualnyIndeks+1)*2-1]=tablicaElementow[aktualnyIndeks];
				tablicaElementow[aktualnyIndeks]=tmp;
				aktualnyIndeks=(aktualnyIndeks+1)*2-1;
			}
	}
	iloscElementow--;

	Zadanie * temp = tablicaElementow;
	tablicaElementow = new Zadanie [iloscElementow];
	copy(temp, temp+iloscElementow, tablicaElementow);

	delete [] temp;
	return doZwrotu;
}

Zadanie Kopiec_zadan::top()
{
	Zadanie doZwrotu;
	if (iloscElementow==0)
	{
		cerr<<"Brak elementow na kopcu!\n";
		return doZwrotu;
	}
	doZwrotu = tablicaElementow[0];
	return doZwrotu;
}

void Kopiec_zadan::wypisz()
{
	for (int i=0; i<iloscElementow; i++)
	{
		cout<<"Indeks: "<<i<<" wartosc: "<<tablicaElementow[i]<<endl;
	}
}

bool Kopiec_zadan::empty()
{
	if (iloscElementow==0)
		return true;
	else
		return false;
}

