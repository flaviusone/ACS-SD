
/*-- Stiva - LISTA --*/
#include "t-st-L.h"

int Suprapune(void *ad,void *as)
{
	//salvare vf sursa in aux
	//parcurgere stiva sursa pana la baza
	//mutare pointer de la baza la vf de la destinatie
	//mutare vf de la destinatie la vf de la sursa
	if(VF(as)==NULL) return 0; //stiva vida
	ACelSt aux=VF(as);
	ACelSt p=VF(as);
	for(;p->urm != NULL;p=p->urm);
	p->urm = VF(ad);
	VF(ad)=aux;
	VF(as)=NULL;

	return 1;
}


void* InitS(size_t d,...) /* initializeaza stiva cu elem.de dimensiune d;
			     anumite implementari pot necesita si alti parametri */
{ ASt s;
	s = (ASt)malloc(sizeof(TStiva));    /* spatiu pentru descriptor stiva */
	if(!s) return NULL;
	s->dime = d;
	s->dimc = sizeof(TCelSt*) + d; /* actualizeaza descriptorul */
	s->vf = NULL;
	return (void*)s;             /* intoarce adresa descriptorului */
}

int VidaS(void *as)            /* test stiva vida */
{ return VF(as) == NULL; }

size_t DimES(void *as)         /* dimensiunea elementelor din stiva */
{ return ((ASt)as)->dime; }

int Push(void *as, void *ae)   /* pune element in varful stivei */
{ ACelSt aux = (ACelSt)malloc(DIMC(as)); /* aloca o noua celula */
	if(!aux) return 0;                   /* alocare imposibila -> "esec" */
	memcpy(&(aux->info), ae, DIMES(as));  /* actualizeaza informatia */
	aux->urm = VF(as); VF(as) = aux;     /* noua celula devine varful stivei */
	return 1;
}

int Pop(void *as, void *ae)   /* extrage elementul din varful stivei la adresa ae */
{ ACelSt aux = VF(as);                /* adresa celula din varf */
	if(!aux) return 0;                  /* stiva vida -> "esec" */
	memcpy(ae, &(aux->info), DIMES(as)); /* preia informatia */
	VF(as) = aux->urm;                  /* actualizeaza adresa varf */
	free(aux);                          /* elimina celula */
	return 1;
}

int Top(void *as, void *ae)
	/* copiaza valoarea din varful stivei la adresa ae */
{ ACelSt aux = VF(as);              /* adresa celula din varf */
	if(! aux) return 0;               /* stiva vida -> "esec" */
	memcpy(ae, &aux->info, DIMES(as)); /* preia informatia */
	return 1;
}

size_t NrES (void* a)        /* numarul de elemente din stiva */
{ size_t k = 0;              /* contor */
	ACelSt p = VF(a);          /* adresa celula din varf */
	for(; p; p = p->urm ) k++; /* numara celule */
	return k;
}

void ResetS(void *a)  /* transforma stiva in stiva vida */
{ ACelSt x = VF(a), aux;
	while(x)        /* elibereaza spatiul ocupat de celule */
	{ aux = x;
		x = aux->urm;
		free(aux);
	}
	VF(a) = NULL;
}

void DistrS(void **aa)  /* elibereaza intregul spatiu ocupat de stiva */
{ ACelSt x = (*(ASt*)aa)->vf, aux;
	while(x)        /* elibereaza spatiul ocupat de celule */
	{ aux = x;
		x = aux->urm;
		free(aux);
	}
	free((ASt)*aa); /* si descriptor */
	*aa = NULL;     /* stiva nu mai exista */
}

int InvS(void *as)             /* inverseaza continutul stivei */
{ ACelSt r, p, u;
	if (! VF(as) || ! VF(as)->urm)       /* stiva vida sau cu o singura celula */
		return 1;
	for(r = NULL, p = VF(as); p; )  /* cat timp nu s-a ajuns la baza */
	{ u = p->urm; p->urm = r;       /* leaga predecesor ca succesor */
		r = p; p = u;                 /* avans */
	}
	VF(as) = r;                     /* actualizeaza varful stivei */
	return 1;
}

size_t Prel_V_B(void *a, TF1 f) /* prelucreaza de la Varf spre Baza */
{ size_t k = 0;               /* contor elemente pentru care f != 0 */
	ACelSt p = VF(a);           /* adresa celula din varf */
	for(; p; p = p->urm )       /* parcurge lista */
		if(f(&(p->info))) k++;    /* aplica functia f si, eventual, creste contor */
	return k;
}

/* functie recursiva de prelucrare a listei */
size_t pbv(ACelSt x, TF1 f)
{ if(!x) return 0;
	return pbv(x->urm, f) + (f(&(x->info)) != 0);
}

size_t Prel_B_V(void *a, TF1 f)  /* prelucreaza de la Baza spre Varf */
{ return pbv(VF(a), f); }


int MutaS(void* ad, void* as)  /* muta elementul din varful stivei sursa */
{ ACelSt p = VF(as);
	if(!p) return 0;
	VF(as) = p->urm;
	p->urm = VF(ad);
	VF(ad) = p;
	return 1;
}
