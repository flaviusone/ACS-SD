/*-- testM-int.c --*/
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

int main(int argc, char *argv[])
{/* declaratie vector de intregi initializat ca multime */
	int v[20] = {2, 5, 3, 9, 8},
	    z[10] = {11, 8, 3, 16, 5},
	    l[10] = {-1, 23, 4, 6, -9, 10};
	TMultime m1 = {sizeof(int),compI,compI,v,v+5,v+20}, *a = &m1,
		 m2, *b = &m2, *c=&m1;
	int v1 = 100, v2 = 6, v3 = 11, rez ,v4=1323;
	int *pr;

	/* S = secventa de prelucrari, folosind operatii generice: */
	/*   - afisare multime, - test apartenenta, - test localizare */
	/*  afi1(a);
	    rez = Apartine(&v1, a); //apartine e macro la functia Loc
	    printf("elementul %i %sapartine multimii\n", v1, rez? "" : "nu ");
	    pr = (int*)Loc(&v2, a);
	    if(!pr)
	    printf("elementul %i nu apartine multimii\n\n", v2);
	    else
	    printf("elementul %i are adresa %p si indice %i\n\n", v2, pr, pr-v);

	/* - adaugare 2 noi elemente: unul care nu exista si altul care exista
	- afisare multime */
	/*  rez = Adauga(&v1, a);
	    printf("%i %s\n", v1, rez? "adaugat" : "exista deja");
	    rez = Adauga(&v2, a);
	    printf("%i %s\n\n", v2, rez? "adaugat" : "exista deja");
	    afi1(a);

	/* - eliminare 2 elemente: unul care exista si altul care nu exista
	- afisare multime
	*/
	/*   rez = Elimina(&v1,a);
	     printf("Elementul %i %s a fost eliminat \n",v1,rez? "" : "nu ");
	     rez= Elimina(&v4,a);
	     printf("Elementul %i %s a fost eliminat \n",v4,rez? "" : "nu ");
	     afi1(a);

	/* - test initializare cu InitS -*/
	InitS(b, z, 10, sizeof(int),compI,compI); /* multime vida */
	b->s = z + 5;  /* modifica sfarsit zona utila */
	/*  printf("Cardinal(b) = %i\n", Card(b));
	    printf("b: "); afi1(b);

	/* - test Identice(a,a) si Identice(a,b) -*/
	/*    rez=Identice(a,a);
	      printf("Identice(a,a) - Cele 2 %s sunt identice\n",rez? "" : "nu ");
	      rez=Identice(a,b);
	      printf("Identice(a,b) - Cele 2 %s sunt identice\n",rez? "" : "nu ");

	/* - test IncludeO - */
	/*    afi1(a);
	      afi1(b);
	      rez = IncludeO(a,b);
	      printf("Multimea a %s include b \n",rez? "" : "nu ");
	      rez = IncludeO(b,a);
	      printf("Multimea b %s  include a \n",rez? "" : "nu ");
	      rez = IncludeO(a,a);
	      printf("Multimea a %s include a \n",rez? "" : "nu ");



	/* - test ReuniuneO - */
	c = InitD(20, sizeof(int),compI,compI);
	//    qsort(a->v, Card(a), sizeof(int), compI);
	//    qsort(b->v, Card(b), sizeof(int), compI);
	/*    printf("a: "); afi1(a);
	      printf("b: "); afi1(b);
	      rez = ReuniuneO(a, b, c);
	      printf("c = reuniune(v,z): "); afi1(c);
	      printf("Cardinal(c) = %i\n", Card(c));
	/* ------------------------ */

	/* - test Diferenta - */
	/*   printf("a: "); afi1(a);
	     printf("b: "); afi1(b);
	     afi1(c);
	     rez = Diferenta(a, b, c);
	     printf("c = diferenta(a,b): "); afi1(c);
	/* ------------------------*/


	/* - test Intersectie - */
	/*    printf("a: "); afi1(a);
	      printf("b: "); afi1(b);
	      rez = Intersectie(a, b, c);
	      printf("c = Intersectie(a,b): "); afi1(c);
	/* ------------------------*/

	printf("a: "); afi1(a);
	printf("b: "); afi1(b);
	rez = Transforma(a, b);
	printf("Transforma(a,b): "); afi1(a);
	rez = Transforma(b,a);
	printf("Transforma(b,a): "); afi1(b);
	printf("Cardinal intesectie a si b %i",Intersectie_Daniela(a,b));

	return 0;
}


