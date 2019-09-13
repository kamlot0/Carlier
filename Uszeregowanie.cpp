#include "Uszeregowanie.h"
#include "Kopiec_zadan.h"

using namespace std;

Uszeregowanie::Uszeregowanie(char * nazwa_pliku)
{
	int rozmiar;				//zmienna pozorowana. trzeba gdzies wczytac "3"
	ifstream plikin(nazwa_pliku);
	plikin >> n;
	plikin >> rozmiar;
	Zadanie * wczytywane;
	int rr, pp, qq;
	for (int i=0; i<n; i++) {
		plikin >> rr >> pp >> qq;
		wczytywane = new Zadanie(rr,pp,qq,i+1);
		listaZadan.push_back(*(wczytywane));
		delete wczytywane;
	}
	plikin.close();

}


int Uszeregowanie::Schrage()
{
	int aktualnyCzas = 0;
	int _Cmax = 0;

	Kopiec_zadan kopiecZadan(&Zadanie::compR);						//kopiec z wszystkimi zadaniami posortowanymi wg. R
	for (int i=0; i<n; i++)
		kopiecZadan.push(listaZadan[i]);

	Kopiec_zadan dostepneZadania(&Zadanie::compQ);					//kopiec dostepnych w danej chwili czasowej zadan; posortowana od największego Q
	vector<Zadanie> listaSchrage;										//lista uszeregowana wg. algorytmu Schrage'a. pod koniec metody podpinana pod listeZadan

	while ((!kopiecZadan.empty()) || (!dostepneZadania.empty())) {
		while ((!kopiecZadan.empty()) && (kopiecZadan.top().r<=aktualnyCzas)) {
			dostepneZadania.push(kopiecZadan.top());
			kopiecZadan.pop();
		}

		if (dostepneZadania.empty()) {
			aktualnyCzas=kopiecZadan.top().r;
		}
		else {
			listaSchrage.push_back(dostepneZadania.top());		//dodajesz zadanie do listy
			dostepneZadania.pop();								//usuwa zadanie z puli dostepnych
			listaSchrage.back().t_on=aktualnyCzas;		//ustawia realny czas rozpoczecia realizacji zadania na maszynie
			aktualnyCzas+=listaSchrage.back().p;		//aktualizuje czas

			if (aktualnyCzas + listaSchrage.back().q > _Cmax)
				_Cmax=aktualnyCzas + listaSchrage.back().q;
		}
	}

	Cmax=_Cmax;
	listaZadan.clear();
	listaZadan=listaSchrage;
	listaSchrage.clear();
	return Cmax;
}

int Uszeregowanie::SciezkaKrytyczna()
{
	int aktualnyMax=0;
	for (int i=0; i < n; i++) {														//przejrzyj listeZadan. jezeli moment rozpoczecia realizacji+r+q = Cmax,
		if (listaZadan[i].t_on+listaZadan[i].p+listaZadan[i].q > aktualnyMax) {		//to mamy zadanie, ktore konczy caly proces
			b=i;
			aktualnyMax=listaZadan[i].t_on+listaZadan[i].p+listaZadan[i].q;
		}
	}
	a=b;
	while ((a>=1) && (listaZadan[a-1].t_on+listaZadan[a-1].p >= listaZadan[a].r) ){
		a--;
	}
	return 0;
}

int Uszeregowanie::ZadanieInterferencyjne()
{
	bool znalezionoC = false;

	for(int i=b-1; i>=a; i--)
		if ((!znalezionoC) && (listaZadan[i].q < listaZadan[b].q)) {
			znalezionoC=true;
			c=i;
		}

	if (znalezionoC==true)
		return 1;
	else
		return 0;
}

int Uszeregowanie::rMinBloku() {
	return rMin(c+1,b);
}

int Uszeregowanie::qMinBloku() {
	return qMin(c+1,b);
}

int Uszeregowanie::sumaPBloku() {
	return sumaP(c+1,b);
}

int Uszeregowanie::SchragePtm()
{
	int aktualnyCzas = 0;
	int _Cmax = 0;

	vector<Zadanie>listaNieprzydzielonych;								//ze wzgledu na konieczność swobodnego dostepu do wszystkich zadan nie mozna tego realizowac na kopcu.
	listaNieprzydzielonych = listaZadan;								//tworzymy kopie listy zadan
	sort(listaNieprzydzielonych.begin(), listaNieprzydzielonych.end(), Zadanie::compR);

	Kopiec_zadan listaDostepnych(&Zadanie::compQ);					//kopiec dostepnych w danej chwili czasowej zadan. Posortowany od najwiekszego Q

	vector<Zadanie> listaSchrage;										//lista uszeregowana wg. algorytmu Schrage'a. pod koniec metody podpinana pod listeZadan

	Kopiec_zadan listaPrzerwan(&Zadanie::compQ);						//lista tych zadan, na rzecz ktorych moze wystapic przerwanie.
																		//Posortowana od najmniejszego R

	while ((!listaNieprzydzielonych.empty()) || (!listaDostepnych.empty())) {
		while ((!listaNieprzydzielonych.empty()) && (listaNieprzydzielonych.back().r<=aktualnyCzas)) {
			listaDostepnych.push(listaNieprzydzielonych.back());					//tworzymy listę zadan, ktorych r juz uplynelo
			listaNieprzydzielonych.pop_back();
		}

		if (listaDostepnych.empty()) {
			aktualnyCzas=listaNieprzydzielonych.back().r;
		}
		else {
			while (!listaPrzerwan.empty())
				listaPrzerwan.pop();								//czyszczenie listy przerwan

			for (int i=0; i< (int)listaNieprzydzielonych.size();i++)	//tworzenie nowej listy przerwan
				if ((listaDostepnych.top().p + aktualnyCzas > listaNieprzydzielonych[i].r)&&(listaDostepnych.top().q < listaNieprzydzielonych[i].q))
					listaPrzerwan.push(listaNieprzydzielonych[i]);	//na liste przerwan kladziemy te zadania, ktorych q jest wieksze od aktualnie dodawanego algorytmem Schrage'a
																	//a r miesci sie w przedziale (aktualnyCzas, aktualnyCzas+p dodawanego). Na rzecz tych zadan powinno wystąpić przerwanie.
																	//elementy na liscie przerwan sa kopiami!

			if (listaPrzerwan.empty()) {							//nie ma przerwan - normalna procedura Schrage'a
				listaSchrage.push_back(listaDostepnych.top());		//dodajesz zadanie do listy
				listaDostepnych.pop();								//usuwa zadanie z puli dostepnych
				listaSchrage.back().t_on=aktualnyCzas;				//ustawia realny czas rozpoczecia realizacji zadania na maszynie
				aktualnyCzas+=listaSchrage.back().p;				//aktualizuje czas

				if (aktualnyCzas + listaSchrage.back().q > _Cmax)
					_Cmax=aktualnyCzas + listaSchrage.back().q;
			}
			else {							//przerwanie
				Zadanie part1 = listaDostepnych.top();
				listaDostepnych.pop();
				Zadanie part2=part1;

				part1.p=listaPrzerwan.top().r-aktualnyCzas;			//część zadania, która zrealizuje się do momentu przerwania.
				part2.p-=part1.p;									//pozostała część zadania: od part2.p (==part1.p oryginalnego) odejmujesz część, która będzie zrealizowana
				listaDostepnych.push(part2);						//reszta realizowanego zadania trafia spowrotem do listy dostepnych zadan

				listaSchrage.push_back(part1);
				listaSchrage.back().t_on=aktualnyCzas;
				aktualnyCzas+=listaSchrage.back().p;

				if (aktualnyCzas + listaSchrage.back().q > _Cmax)
					_Cmax=aktualnyCzas + listaSchrage.back().q;

				}
		}
	}
	return _Cmax;
}

ostream & operator << (ostream & strumienWyjsciowy, Uszeregowanie & doWypisania)
{
	for (int i=0; i < (int)doWypisania.listaZadan.size(); i++)
		strumienWyjsciowy<<doWypisania.listaZadan[i];

	return strumienWyjsciowy;
}

Uszeregowanie::Uszeregowanie(void)
{
}

Uszeregowanie::~Uszeregowanie(void)
{
}

int Uszeregowanie::rMin(int aa, int bb)
{
	int rmin=listaZadan.at(a).r;

	for (int i=a; i<=b; i++) {
		if (listaZadan.at(i).r<rmin)
			rmin=listaZadan.at(i).r;
	}

	return rmin;
}

int Uszeregowanie::qMin(int aa, int bb)
{
	int qmin=listaZadan.at(a).q;

	for (int i=a; i<=b; i++) {
		if (listaZadan.at(i).q<qmin)
			qmin=listaZadan.at(i).q;
	}
	return qmin;
}

int Uszeregowanie::sumaP(int aa, int bb)
{
	int sumaP=0;

	for (int i=a; i<=b; i++) {
		sumaP+=listaZadan.at(i).p;
	}

	return sumaP;
}


/*int Uszeregowanie::h(int aa, int bb)
{
	if ((aa<0) || (aa>bb) || (bb>(int)listaZadan.size())) {
		cerr<<"błąd wywołania funkcji h(int, int)\n";
		return 0;
	}
	return (rMin(aa,bb)+sumaP(aa,bb)+qMin(aa,bb));
}
*/
