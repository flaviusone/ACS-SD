/*-- Elementele stivei sunt memorate intr-un vector --*/
#include "T-st-V.h"

void *InitS(size_t d,...)      /* creeaza stiva vida cu elemente de dimensiune d;
				  este necesar si un al doilea parametru = numar maxim elemente in coada */
{ ASt a = (ASt)malloc(sizeof (TStiva));
	va_list ap;
	if (!a) return NULL;
	/* preia param.2 = nr.max.elemente */
	va_start(ap,d);
	a->maxe = va_arg(ap,size_t);  
	va_end(ap);
	a->dime = d;
	/* aloca spatiu pentru vector si test esec */
	a->b = (char*)calloc(a->maxe, d);         
	if (!a->b) { free(a); return NULL; }     
	/* actualizeaza adrese din descriptor */
	a->vf = a->b;  
	a->sv = a->b + d * a->maxe; 
	return (void *)a;
}

int Push(void *a, void *ae)     /* pune element in varful stivei */
{ if( PLINAS(a)) return 0;
	memcpy (VF(a), ae, DIMES(a));  /* copiaza elementul in varful stivei */
	VF(a) += DIMES(a);             /* deplaseaza varful stivei */
	return 1;
}

int Pop(void *a, void *ae)      /* extrage elementul din varful stivei la adresa ae */
{ if(VIDAS(a)) return 0;
	VF(a) -= DIMES(a);             /* deplaseaza varful stivei */
	memcpy (ae, VF(a), DIMES(a));  /* copiaza elementul scos din stiva */
	return 1;
}

int Top(void *a, void *ae)    /* copiaza elementul din varful stivei la adresa ae */
{ if(VIDAS(a)) return 0;
	memcpy (ae, VF(a)-DIMES(a), DIMES(a));   /* copiaza elementul din varful stivei */
	return 1;
}

int VidaS(void *a)               /* test stiva vida */
{ return VF(a) == BS(a); }

size_t NrES(void *a)          /* numarul de elemente din stiva */
{ return (VF(a) - BS(a)) / DIMES(a); }

size_t DimES(void *a)           /* dimensiunea elementelor din stiva */
{ return DIMES(a); }

void ResetS(void *a)          /* transforma stiva in stiva vida */
{ VF(a) = BS(a); }

void DistrS(void **aa)           /* elibereaza intregul spatiu ocupat de stiva */
{ free(BS(*aa)); free((ASt)*aa); /* elibereaza spatiul ocupat de vector si descriptor */
	*aa = NULL;                    /* stiva nu mai exista */
}

int InvS(void *a)             /* inverseaza continutul stivei */
{ char *temp = VF(a), *p, *q;
	if(temp >= SV(a)) temp = (char *)malloc(DIMES(a)); /* zona tampon alocata dinamic */
	if(!temp) return 0;          /* nu exista spatiu -> operatie imposibila */
	/* inverseaza perechi de elemente; p, q pornesc de la baza, respectiv varful stivei */
	for(p = BS(a), q = VF(a)-DIMES(a); p < q; p += DIMES(a), q -= DIMES(a))
	{ memcpy(temp, p, DIMES(a)); 
		memcpy(p, q, DIMES(a)); 
		memcpy(q, temp, DIMES(a));
	}
	if(temp != VF(a)) free(temp); /* daca tampon alocat dinamic, atunci elibereaza */
	return 1;
}

/*- prelucrarea tuturor elementelor din stiva; -> numar elemente pentru care f != 0 -*/

size_t Prel_B_V(void *a, TF1 f)  /* prelucreaza de la Baza spre Varf */
{ size_t k = 0;                    /* contor elemente pentru care f != 0 */
	char *p;
	for(p = BS(a); p < VF(a); p += DIMES(a))   /* incepand de la baza */
		if(f(p)) k++;                  /* aplica functia f si, eventual, creste contor */
	return k;
}

size_t Prel_V_B(void *a, TF1 f)  /* prelucreaza de la Varf spre Baza */
{ size_t k = 0;                    /* contor elemente pentru care f != 0 */
	char *p;
	for(p = VF(a); (p -= DIMES(a)) >= BS(a); )  /* incepand de la varf */
		if(f(p)) k++;                  /* aplica functia f si, eventual, creste contor */
	return k;
}

/* Operatii de deplasare din coada sursa in coada destinatie. Rezultat < 0 in caz de
   eroare (de exemplu dimensiunile elementelor difera), 0 daca sursa vida, 1 = succes */

int MutaS(void *ad, void *as)      /* muta elementul din varful stivei sursa */
{ /* teste dim.diferite, sursa vida, lipsa spatiu in stiva destinatie */
	if(DIMDIF(as,ad)) return -1;    
	if(VIDAS(as)) return 0;          
	if(PLINAS(ad)) return -2; 
	/* mutare element */
	VF(as) -= DIMES(as); 
	memcpy(VF(ad), VF(as), DIMES(as));
	VF(ad) += DIMES(ad);
	return 1;
}

int Suprapune(void *ad, void *as)   /* muta stiva sursa peste destinatie */
{ size_t n = VF(as) - BS(as);       /* numar octeti mutati */
	/* teste dim.diferite, sursa vida, lipsa spatiu in stiva destinatie */
	if(DIMDIF(as,ad)) return -1;      
	if(VIDAS(as)) return 0;
	if(VF(ad) + n > SV(ad)) return -2; 
	/* transfer elemente */
	memcpy(VF(ad), BS(as), n); 
	VF(ad) += n; VF(as) = BS(as);     /* actualizeaza varfuri stive */
	return 1;
}

int Rastoarna(void *ad, void *as)  /* suprapune inversul sursei destinatie */
{ size_t n = VF(as) - BS(as);
	if(DIMDIF(as,ad)) return -1;      /* dimensiuni diferite */
	if(VIDAS(as)) return 0;           /* sursa vida */
	if(VF(ad) + n > SV(ad)) return -2;/* nu exista spatiu pentru mutarea in destinatie */
	/* cat timp mai exista elemente in sursa -> muta din varf sursa in varf destinatie */
	while(VF(as) > BS(as))
	{ VF(as) -= DIMES(as); 
		memcpy(VF(ad), VF(as), DIMES(as)); 
		VF(ad) += DIMES(as);
	}
	return 1;
}
