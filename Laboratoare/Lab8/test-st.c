/*-- test-st.c -- prelucrari stive --*/
//#include "t-st-v.h"
//#include "St-V.c"
#include "St-L-2.c"
#include "t-st-L.h"
#define MAX 256

int CitS(char *mesaj, char *format, void *x)
	/* afiseaza mesaj si citeste cu format valori care se introduc in stiva */
{ int v, nc = 0;  /* valoare citita, numar valori citite si introduse in stiva */
	printf("\n Introduceti (terminand cu caracter nenumeric)%s\n", mesaj);
	fflush(stdin);
	/*- cat timp ce citesc valori si se introduc corect in structura creste nc -*/
	while(scanf (format, &v) && Push (x, &v)) nc++;
	fflush(stdin);
	return nc;
}

void AfiS(char antet[], TF1 AfiElem, void *a)
	/* afiseaza antet si apoi aplica functia de afisare AfiElem tuturor elementelor */
{ printf("%s", antet);          /* afiseaza antetul */
	if(VidaS (a))
		printf("Stiva vida!");
	else
		Prel_B_V(a, AfiElem);       /* afiseaza elementele in ordinea introducerii */
	printf("\n");
}

int AfiIntreg(void *x,...)
{ printf (" %i", *(int *)x);
	return 1;
}

int SchimbaSemn(void*a,...)
{ *(int*)a = -*(int*)a;
	return 1;
}

int main()
{ void *a1, *a2;
	int x, n1, n2;

	a1 = InitS(sizeof(int),MAX);
	if(a1)
	{ a2 = InitS(sizeof(int),MAX);
		if(a2)
		{ fflush(stdin);
			n1 = CitS(", valorile din prima stiva", "%i", a1);
			n2 = CitS(", valorile din a doua stiva", "%i", a2);
			/*printf("Numar valori citite: %i  si  %i\n", n1, n2);
			  Pop(a1, &x);
			  printf("\n\nDupa Pop din stiva_1: ");
			  AfiS("", AfiIntreg, a1);

			  printf("\nDupa InvS (stiva_2)\n");
			  InvS(a2);
			  AfiS("\tstiva_2: ", AfiIntreg, a2);
			  */
			printf("\nDupa Suprapune (stiva1,stiva_2)\n");
			Suprapune(a1,a2);
			AfiS("\tstiva_1: ", AfiIntreg, a1);
			AfiS("\tstiva_2: ", AfiIntreg, a2);
			/*printf("\nAfisare stiva_1 de la varf\n");
			  n1 = Prel_V_B(a1, AfiIntreg);

			  n1 = Prel_V_B(a1, SchimbaSemn);
			  printf ("\nDupa Prel_V_B(stiva_1, SchimbaSemn)\n");
			  AfiS("\tstiva_1: ", AfiIntreg, a1);

			  ResetS(a2);
			  printf("\nDupa ResetS(stiva_2)\n");
			  AfiS("\tstiva_2: ", AfiIntreg, a2);
			  */
			//getch();
			DistrS(&a2);
		}
		DistrS (&a1);
	}
	return 0;
}

