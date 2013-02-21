/*-- test-q.c -- prelucrari cozi --*/
//#include "T-q-V.h"
//#include "Q-V.c"
#include "Q-LD-2.c"
#include "T-q-LD.h"
#include <conio.h>

#define MAX 256

int CitQ(char* mesaj, char* format, void* x)
	/* afiseaza mesaj si citeste cu format valori pe care le adauga la coada */
{ int v, nc = 0;   /* valoare citita, numar valori citite si introduse in structura */
	printf ("\n Introduceti (terminand cu caracter nenumeric)%s\n", mesaj);
	fflush (stdin);
	/*- cat timp ce citesc valori si se introduc corect in structura creste nc -*/
	while (scanf(format, &v) && IntrQ (x, &v)) nc++;
	fflush (stdin);
	return nc;
}

void AfiQ(char antet[], TF1 AfiElem, void*a)
	/* afiseaza antet si apoi aplica functia de afisare AfiElem tuturor elementelor */
{ printf ("%s", antet);          /* afiseaza antetul */
	if (VidaQ(a))
		printf("Coada vida!");
	else
		PrelQ(a, AfiElem);       /* afiseaza elementele in ordinea introducerii */
	printf("\n");
}

int AfiIntreg(void*x,...)
{ printf (" %i", *(int *)x);
	return 1;
}

int SchimbaSemn(void*a,...)
{ *(int*)a = -*(int*)a;
	return 1;
}
int Para(void *a,...)
{
	if (*(int*)a % 2 == 0)
		return 1;
	else
		return 0;
}

int main()
{ void *a1, *a2;
	int x, n1, n2;

	a1 = InitQ (sizeof(int),MAX);
	if (a1)
	{ a2 = InitQ(sizeof(int),MAX);
		if (a2)
		{ fflush (stdin);
			n1 = CitQ(", valorile din prima coada", "%i", a1);
			n2 = CitQ(", valorile din a doua coada", "%i", a2);
			printf("Numar valori citite: %i  si  %i\n", n1, n2);
			AfiQ("\tcoada_1: ", AfiIntreg, a1);
			AfiQ("\tcoada_2: ", AfiIntreg, a2);
			/*ExtrQ(a1, &x);
			  printf("\nDupa ExtrQ din coada_1\n");
			  AfiQ("\tcoada_1: ", AfiIntreg, a1);
			  */
			n1 = MutaQ(a1, a2);
			printf("\nDupa MutaQ (coada_1, MutaQ)\n");
			AfiQ("\tcoada_1: ", AfiIntreg, a1);
			AfiQ("\tcoada_2: ", AfiIntreg, a2);


			/*ResetQ(a2);
			  printf("\nDupa ResetQ (coada_2)\n");
			  AfiQ("\tcoada_2: ", AfiIntreg, a2);
			  DistrQ(&a2);*/
			getch();
		}
		DistrQ (&a1);
	}
}
