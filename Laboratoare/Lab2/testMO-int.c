/*-- testMO-int.c --*/     //unde testez ElimO Inserare LocO
#include "multimeV.h"
#include "funcM-aux.c"
#include "funcM-1.c"
#include "funcMO-1.c"


/*-- functie de afisare multime --*/
void afi1(TMultime *m)
{ int *x = (int*)(m->v), n = Card(m), i = 0;
	printf("[");
	for( ; i < n; i++) printf(" %i,", x[i]);
	printf("\b ]\n\n");
}

int compI(const void *a, const void *b) /*-- functie de comparare --*/
{ return *(int*)a - *(int*)b; }

int main() /*debug? */
{/* declaratie vector de intregi initializat ca multime */
	int v[20] = {-1, 2, 3, 4, 6, 10};
	TMultime m1 = {sizeof(int),compI,compI,v,v+6,v+20}, *a = &m1,
		 m2, *b = &m2, *c;
	int v1 = 4, v2 = 6, v3 = 5, rez;
	int *pr;
	/* S = secventa de prelucrari, folosind operatii generice: */
	/*   - afisare multime, - test apartenenta, - test localizare */
	afi1(a);
	pr = (int*)LocO(&v2, a); //chestie dura
	if(!pr)
		printf("elementul %i nu apartine multimii\n\n", v2);
	else
		printf("elementul %i apartine multimii si are indice %i %p \n\n", v2,pr-v);

	/* - adaugare 2 noi elemente: unul care nu exista si altul care exista
	   - afisare multime */
	rez = Inserare(&v1, a);
	printf("%i %s\n", v1, rez? "adaugat" : "exista deja");
	rez = Inserare(&v3, a);
	printf("%i %s\n\n", v3, rez? "adaugat" : "exista deja");
	afi1(a);
	/* - eliminare 2 elemente: unul care exista si altul care nu exista
	   - afisare multime */

	rez = EliminaO(&v1,a);
	printf("Elementul %i %s a fost eliminat \n",v1,rez? "" : "nu ");
	rez= EliminaO(&v3,a);
	printf("Elementul %i %s a fost eliminat \n",v3,rez? "" : "nu ");
	afi1(a);

}
