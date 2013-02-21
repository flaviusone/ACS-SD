
/*-- funcLOrd.c --*/
#include "tlista.h"

/*-- functie recursiva de inserare in lista ordonata conform f --*/
	int InsOrd_r(ALista a, AEL e, int (*f)(const void*, const void*))
{ if(!*a || f(e, &((*a)->info)) < 0)    /* sfarsit sau urmeaza succesor */
	return InsInc(a, e);                /* insereaza aici */
	return InsOrd_r(&((*a)->urm), e, f);  /* altfel insereaza in lista urm */
}

/*-- functie de generare lista ordonata conform f --*/
TLista GenerLOrd(int (*f)(const void*, const void*), int* lgl)
{ TLista r = NULL;
	TEL x;
	int N, v1, v2;
	printf("\nLungime maxima lista si valorile minima si maxima: ");
	for(;;)
	{ fflush(stdin);
		if(scanf("%i%i%i", &N, &v1, &v2) == 3 && N > 0 && v1 < v2 ) break;
		printf("Eroare! Corectati: ");
	}
	randomize();
	for(*lgl = 0; *lgl < N; (*lgl)++) /* cat timp mai sunt necesare inserari */
	{ x = random(v2-v1+1) + v1;       /* genereaza o noua valoare */
		if(!InsOrd_r(&r, &x, f)) break; /* nu mai exista spatiu pentru inserare */
	}
	return r;                         /* intoarce lista rezultat */
}

