/* Tirnacop Flavius 313CB */
#include "Tema2.h"
#include "auxarb.c"
#include "CitireFis.c"
#include "Corectare.c"
#include "ConstrRez.c"
#include "Coada.c"
void AfisareLista(LExpresii *a)
{/*functie pt debugging*/
	LElemente *b;
	while(a)
	{
		printf("%s ",a->nume_exp);
		b=a->elem;
		if(!b)
		{
			printf("Arbore vid");
		}
		while(b)
		{
			printf("(");
			printf("%c,",b->tip);
			printf("%s,",b->valoare);
			printf("%i) ",b->indice);
			b=b->urm;
		}
		printf("\n");
		a=a->urm;
	}
}
void AfisareRez(Rez *a)
{/*functie pt debugging*/
	while(a)
	{
		printf("\n%s\n",a->nume_exp);
		printf("%s=%5.2f\n",a->reprez,a->rezultat);
		AfiArb2(a->arbore);
		a=a->urm;
	}
	return;
}
void Scriefisier(Rez* a,char* out)
{
	FILE* f;
	f=fopen(out,"wt");
	if(!f) return;
	while (a)
	{
		fprintf(f,"\n%s\n",a->nume_exp);
		fprintf(f,"%s=%5.2f\n",a->reprez,a->rezultat);
		AfiArb(a->arbore,f);
		a=a->urm;
	}
	fclose(f);
	return;
}
int main()
{
	LExpresii *a;
	Rez *rez;
	char in[10]="in.txt",out[10]="out.txt";
	a = CitireFis(in);
	if(!a)
	{
		return 0;
	}
	a = Corectare(a);
	rez=ConstrRez(a);
	Scriefisier(rez,out);
	return 0;
}
