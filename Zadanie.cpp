#include "Zadanie.h"

using namespace std;

Zadanie::Zadanie(int rr, int pp, int qq, int nnr) {
	r=rr;
	p=pp;
	q=qq;
	nr=nnr;
	t_on=0;
}

ostream & operator << (ostream & strumWyj, const Zadanie & doWypisania)
{
	strumWyj<<"Nr: "<<doWypisania.nr<<"\tr: "<<doWypisania.r<<"\tp: "<<doWypisania.p<<"\tq: "<<doWypisania.q<<"\tt_on: "<<doWypisania.t_on<<endl;
	return strumWyj;
}

Zadanie::Zadanie(void)
{
}

Zadanie::~Zadanie(void)
{
}


