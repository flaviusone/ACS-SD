/*-- Coada - Lista CIRCULARA --*/
#include "T-q-LC.h"

/*-- Operatii de baza --*/

void* InitQ(size_t d,...)  /* creeaza coada vida cu elemente de dimensiune d;
			      anumite implementari pot necesita si alti parametri */
{
	AQ c = (AQ)malloc(sizeof(TCoada)); /* spatiu pentru descriptor coada */
	if( ! c ) return NULL;             /* nu exista spatiu -> "esec" */
	c->dime = d;                       /* completeaza deescriptorul */
	c->dimc = sizeof(ACel) + d;
	c->sc = NULL;
	return (void*)c;          /* intoarce adresa descriptorului cozii */
}

int IntrQ(void *a, void *ae)  /* adauga element la sfarsitul cozii */
{
	ACel aux = (ACel)malloc(DIMC(a));  /* aloca o noua celula */
	if(!aux) return 0;                  /* alocare imposibila -> "esec" */
	memcpy(&(aux->info), ae, DIME(a)); /* completeaza celula */
	//aux->urm = NULL;
	if(SC(a) == NULL)       /* coada vida */
	{
		aux->urm = aux;
	}
	else                     /* coada nevida */
	{
		aux->urm=SC(a)->urm;
		SC(a)->urm = aux;    /* -> leaga celula dupa ultima din coada */
	}
	SC(a) = aux;
	return 1;               /* operatie reusita -> "succes" */
}

int ExtrQ(void *a, void *ae) /* extrage primul element din coada la adresa ae */
{
	ACel p = IC(a);            /* p - adre  sa primei celule */
	if(!p) return 0;            /* coada vida -> "esec" */
	memcpy(ae, &(p->info), DIME(a));    /* preia informatia */
	if(IC(a)==SC(a))                    /* daca exista un sg element */
		SC(a) = NULL;
	else
	{

		IC(a) = p->urm;            /* prima celula este scoasa din coada */
	}
	free(p);
	return 1;                   /* operatie reusita -> "succes" */
}

int PrimQ(void *a, void *ae)  /* copiaza primul element din coada la adresa ae */
{
	if(!SC(a)) return 0;        /* coada vida -> "esec" */
	memcpy(ae, &(IC(a)->info), DIME(a));  /* preia informatia */
	return 1;                    /* operatie reusita -> "succes" */
}


size_t DimEQ(void *a)         /* dimensiunea elementelor din coada */
{
	return ((AQ)a)->dime;
}

int VidaQ(void *a)            /* test coada vida */
{
	return ((AQ)a)->sc == NULL;
}


size_t NrEQ(void* a)         /* numarul de elemente din coada */
{
	size_t n = 0;
	ACel p = IC(a);            /* p - adresa primei celule */
	for(; p!=SC(a); p = p->urm) n++;
	return n;
}
void ResetQ(void* a)       /* transforma coada in coada vida */
{
	ACel p, aux;
	if (SC(a)!=NULL)
	{
		p=IC(a);
		while (p!=SC(a))
		{
			aux=p;
			p=p->urm;
			free(aux);
		}
		free(p);
		SC(a)=NULL;
	}
}

void DistrQ(void** aa)   /* elibereaza intregul spatiu ocupat de coada */
{
	ResetQ(*aa);
	free(*aa);
	*aa = NULL;
}

size_t PrelQ(void* a, TF1 f) /* prelucreaza elementele, folosind functia f;
				rezultat = numarul de elemente pentru care f != 0 */
{
	size_t n = 0;
	if(!SC(a)) return 0;
	ACel p = IC(a);           /* p - adresa primei celule */
	do{
		if(f(&(p->info))) n++;
		p = p->urm;
	}
	while(p!=SC(ac)->urm)

		/*
		   for(; p!=SC(a); p = p->urm)
		   if(f(&(p->info))) n++;
		   if(f(&(p->info))) n++;
		   */
		return n;
}
