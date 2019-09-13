
#include "Kopiec_uszeregowania.h"

using namespace std;

Kopiec_uszeregowania::Kopiec_uszeregowania(bool (*cmp)(const Uszeregowanie & ,const  Uszeregowanie & ))
{
	iloscElementow = 0;
	funkcjaPorownujaca = cmp;
	tablicaElementow=NULL;
}

int Kopiec_uszeregowania::push(Uszeregowanie element)
{

	if (iloscElementow==0) { //dodajemy na szczyt kopca
		tablicaElementow = new Uszeregowanie[1];
		tablicaElementow[iloscElementow]=element;
		iloscElementow++;
		return 1;
	}
	else {
		Uszeregowanie * temp = tablicaElementow;
		tablicaElementow = new Uszeregowanie [iloscElementow+1];
		copy(temp, temp+iloscElementow, tablicaElementow);
		delete [] temp;

		int aktualnyIndeks=iloscElementow;
		int indeksOjca=iloscElementow/2;
		Uszeregowanie tmp;

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

Uszeregowanie Kopiec_uszeregowania::pop()
{
	Uszeregowanie doZwrotu;
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
				Uszeregowanie tmp = tablicaElementow[(aktualnyIndeks+1)*2];
				tablicaElementow[(aktualnyIndeks+1)*2]=tablicaElementow[aktualnyIndeks];
				tablicaElementow[aktualnyIndeks]=tmp;
				aktualnyIndeks=(aktualnyIndeks+1)*2;
			}
			else
			{
				Uszeregowanie tmp = tablicaElementow[(aktualnyIndeks+1)*2-1];
				tablicaElementow[(aktualnyIndeks+1)*2-1]=tablicaElementow[aktualnyIndeks];
				tablicaElementow[aktualnyIndeks]=tmp;
				aktualnyIndeks=(aktualnyIndeks+1)*2-1;
			}
	}
	iloscElementow--;

	Uszeregowanie * temp = tablicaElementow;
	tablicaElementow = new Uszeregowanie [iloscElementow];
	copy(temp, temp+iloscElementow, tablicaElementow);

	delete [] temp;
	return doZwrotu;
}

Uszeregowanie Kopiec_uszeregowania::top()
{
	Uszeregowanie doZwrotu;
	if (iloscElementow==0)
	{
		cerr<<"Brak elementow na kopcu!\n";
		return doZwrotu;
	}
	doZwrotu = tablicaElementow[0];
	return doZwrotu;
}

void Kopiec_uszeregowania::wypisz()
{
	for (int i=0; i<iloscElementow; i++)
	{
		cout<<"Indeks: "<<i<<" wartosc: "<<tablicaElementow[i]<<endl;
	}
}

bool Kopiec_uszeregowania::empty()
{
	if (iloscElementow==0)
		return true;
	else
		return false;
}
