/*-- Elementele cozii sunt memorate intr-un vector --*/
#include "t-q-v.h"

void* InitQ(size_t d,...)
	/* creeaza coada vida cu elemente de dimensiune d;
	   este necesar si un al doilea parametru = numar maxim elemente in coada */
{ AQV a = (AQV)malloc (sizeof (TCoadaV));  /* adresa descriptor alocat */
	va_list ap;
	if(!a) return NULL;
	/* preia param.2 = nr.max.elemente */
	va_start(ap,d);             
	a->maxe = va_arg(ap,size_t); 
	va_end(ap); 
	a->dime = d;
	/* aloca spatiu pentru vector si test esec */
	a->v = (char*)calloc(a->maxe+1,d); 
	if(!a->v) { free(a); return NULL; }    
	/* actualizeaza adrese din descriptor */
	a->sv = a->v + (a->maxe+1) * d; 
	a->ic = a->sc = a->v;
	return (void*)a;
}

int IntrQ(void *a, void *ae)   /* adauga element la sfarsitul cozii */
{ if(PlinaQ(a)) return 0;
	memcpy(SC(a), ae, DimEQ(a));  /* copiaza elementul la sfarsitul cozii */
	Avans(a,SC(a));              /* sfarsitul cozii avanseaza */
	return 1;
}

int ExtrQ (void *a, void *ae)  /* extrage primul element din coada la adresa ae */
{ if(VidaQ(a)) return 0;
	memcpy(ae, IC(a), DimEQ(a));  /* copiaza elementul de la inceputul cozii */
	Avans(a,IC(a));              /* inceputul cozii avanseaza */
	return 1;
}

int PrimQ(void *a, void *ae)   /* copiaza primul element din coada la adresa ae */
{ if(VidaQ(a)) return 0;
	memcpy(ae, IC(a), DimEQ(a));  /* copiaza elementul de la inceputul cozii */
	return 1;
}

size_t NrEQ(void *a)       /* numarul de elemente din coada */
{ return Ocupat(a) / DimEQ(a); }

void ResetQ(void *a)       /* transforma coada in coada vida */
{ SC(a) = IC(a) = V(a); }  /* inceput si sfarsit coada = inceput vector */

void DistrQ(void **aa)     /* elibereaza intregul spatiu ocupat de coada */
{ free(V(*aa));  /* elibereaza spatiul ocupat de vector si descriptor */
	free(*aa);
	*aa = NULL;
}

size_t PrelQ(void *a, TF1 f)   /* prelucreaza elementele, folosind functia f;
				  rezultat = numarul de elemente pentru care f != 0 */
{ char *p = IC(a);               /* adresa element prelucrat = inceputul cozii */
	size_t k = 0;                  /* contor */
	for(; p != SC(a); Avans(a,p))  /* pentru fiecare element, pana la ultimul */
		if( f(p) ) k++;              /* daca f intoarce rezultat != 0 -> contorizeaza */
	return k;
}
