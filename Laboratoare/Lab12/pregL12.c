/*--- pregL12.c ---*/
#include <conio.h>
#include "graf.h"
#include "gr1-M.c"

void AfiM(void* g)
{ int i,j,k, n = NrNoduri(g);
	for (i = 1; i <= n; i++)
	{ for (j = 1; j <= n; j++)
		{ k = CostArc(g,i,j);
			if(k == ArcInex) printf("  - ");
			else printf("%3i ", k);
		}
		printf("\n");
	}
}

int F1( void* g, int* nrnoduri)
{
	int max=-1,s,d,aux;

	for (s = 1 ; s < N(g) ; s++)
	{
		aux=0;
		for (d=1 ; d< N(g) ; d++)
		{
			//printf("%i ",CostArc(g,s,d));
			if (CostArc(g,s,d)>0)
				aux++;
		}
		if(aux>max)
		{
			max=aux;
			*nrnoduri=1;
		}else if (aux==max) *nrnoduri++;
	}
	return max;
}
int F1M(void *g, int* nrnoduri)
{
	int max=0,s,d,aux;
	for (s = 1 ; s < N(g) ; s++)
	{
		aux=0;
		for (d=1 ; d< N(g) ; d++)
		{

			//printf("%i ",G(g)->x[(s-1) * N(g) + (d-1)]);
			if (G(g)->x[(s-1) * N(g) + (d-1)]>0)
				aux++;
		}
		if(aux>max)
		{
			max=aux;
			*nrnoduri=1;
		}else if (aux==max) *nrnoduri++;
	}
	return max;
}

void AfiTM(void *g)
{
	int max=0,s,d,k;
	for (d = 1 ; d <= N(g) ; d++)
	{

		for (s=1 ; s<= N(g) ; s++)
		{
			k=G(g)->x[(s-1) * N(g) + (d-1)];
			if(k == 0) printf("  - ");
			else printf("%3i ", k);
			//printf("%i ",G(g)->x[(s-1) * N(g) + (d-1)]);

		}
		printf("\n");
	}
	return;
}
int main()
{ TIdNod i, x;
	void* g;
	int nrgradmax=0;
	if (CitGraf(&g) <= 0)
	{ printf("-=- eroare la citire -=-\n"); getch();  return -1;}
	printf(" -=- graf cu %i noduri -=-\n", NrNoduri(g));

	AfiM(g);
	//printf("Gradul de iesire maxim este %i\n",F1(g,&nrgradmax));
	//printf("Nr de noduri cu grad de iesire maxim este %i \n",nrgradmax);

	printf("\nGradul de iesire maxim este %i\n",F1M(g,&nrgradmax));
	printf("Nr de noduri cu grad de iesire maxim este %i \n",nrgradmax);
	AfiTM(g);
	getch();
	return 0;
}
