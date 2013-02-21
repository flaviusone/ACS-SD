/*--- pregL12.c ---*/
#include <conio.h>
#include "graf.h"
#include "gr1-L.c"

void AfiM(void* g)
{
	int i,j,k, n = NrNoduri(g);
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			k = CostArc(g,i,j);
			if(k == ArcInex) printf("  - ");
			else printf("%3i ", k);
		}
		printf("\n");
	}
}
int F1L(void *g, int* nrnoduri)
{
	int s,aux,max=-1;
	AG a;
	AArc p;

	for (s = 1 ; s <= N(g); s++)
	{
		aux=0;
		for (p = G(g)->x[s]; p != NULL; p = p->urm)
		{
			aux++;
		}


		if(aux>max)
		{
			max=aux;
			*nrnoduri=1;
		}
		else if (aux==max) *nrnoduri++;
	}

	return max;
}
int main()
{
	TIdNod i, x;
	int nrgradmax=0;
	void* g;

	if (CitGraf(&g) <= 0)
	{
		printf("-=- eroare la citire -=-\n");
		getch();
		return -1;
	}
	printf(" -=- graf cu %i noduri -=-\n", NrNoduri(g));

	printf("\nGradul de iesire maxim este %i\n",F1L(g,&nrgradmax));
	printf("Nr de noduri cu grad de iesire maxim este %i \n",nrgradmax);


	AfiM(g);
	getch();
	return 0;
}
