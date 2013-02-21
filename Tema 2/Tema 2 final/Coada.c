/*-- Coada - Lista DESCHISA --*/
#include "Tema2.h"

/*- Operatii de baza -*/

void* InitQ(size_t d,...)  /* creeaza coada vida cu elemente de dimensiune d;
			      anumite implementari pot necesita si alti parametri */
{ AQ c = (AQ)malloc(sizeof(TCoada)); /* spatiu pentru descriptor coada */
	if( ! c ) return NULL;             /* nu exista spatiu -> "esec" */
	c->dime = d;                       /* completeaza deescriptorul */
	c->dimc = sizeof(ACel) + d;
	c->ic = c->sc = NULL;
	return (void*)c;          /* intoarce adresa descriptorului cozii */
}

int IntrQ(void *ac, void *ae)  /* adauga element la sfarsitul cozii */
{ ACel aux = (ACel)malloc(DIMC(ac));  /* aloca o noua celula */
	if(!aux) return 0;                  /* alocare imposibila -> "esec" */
	memcpy(&(aux->info), ae, DIME(ac)); /* completeaza celula */
	aux->urm = NULL;
	if(SC(ac) == NULL)      /* coada vida */
		IC(ac) = aux;         /* -> noua celula se afla la inceputul cozii */
	else                    /* coada nevida */
		SC(ac)->urm = aux;    /* -> leaga celula dupa ultima din coada */
	SC(ac) = aux;  	      /* actualizeaza sfarsitul cozii */
	return 1;               /* operatie reusita -> "succes" */
}

int ExtrQ(void *ac, void *ae) /* extrage primul element din coada la adresa ae */
{ ACel p = IC(ac);            /* p - adresa primei celule */
	if(!p) return 0;            /* coada vida -> "esec" */
	memcpy(ae, &(p->info), DIME(ac));  /* preia informatia */
	IC(ac) = p->urm;            /* prima celula este scoasa din coada */
	free(p);	                  /* si distrusa */
	if(!IC(ac)) SC(ac) = NULL;  /* prin extragere coada a devenit vida */
	return 1;                   /* operatie reusita -> "succes" */
}

int PrimQ(void *ac, void *ae)  /* copiaza primul element din coada la adresa ae */
{ if(!IC(ac)) return 0;        /* coada vida -> "esec" */
	memcpy(ae, &(IC(ac)->info), DIME(ac));  /* preia informatia */
	return 1;                    /* operatie reusita -> "succes" */
}

size_t DimEQ(void *ac)         /* dimensiunea elementelor din coada */
{ return ((AQ)ac)->dime; }

int VidaQ(void *ac)            /* test coada vida */
{ return ((AQ)ac)->ic == NULL; }

size_t NrEQ(void* a)         /* numarul de elemente din coada */
{ size_t n = 0;
	ACel p = IC(a);            /* p - adresa primei celule */
	for(; p; p = p->urm) n++;
	return n;
}

void ResetQ(void* a)       /* transforma coada in coada vida */
{ ACel p = IC(a), aux;     /* p - adresa primei celule */
	while(p)
	{ aux = p; p = p->urm;
		free(aux);
	}
	IC(a) = SC(a) = NULL;
}

void DistrQ(void** aa)   /* elibereaza intregul spatiu ocupat de coada */
{ ResetQ(*aa);
	free(*aa);
	*aa = NULL;
}

size_t PrelQ(void* a, TF1 f) /* prelucreaza elementele, folosind functia f;
				rezultat = numarul de elemente pentru care f != 0 */
{ size_t n = 0;
	ACel p = IC(a);           /* p - adresa primei celule */
	for(; p; p = p->urm)
		if(f(&(p->info))) n++;
	return n;
}

