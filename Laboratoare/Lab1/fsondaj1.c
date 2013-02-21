/*-- fsondaj1.c --*/
#include "sondaj.h"

/* Aloca spatiu (totul sau nimic!) pentru structura TChestionar si
   pentru vectorul de intrebari, initializat cu 0 */
TChestionar* AlocCh(int ni)
{ TChestionar* x = (TChestionar*) calloc(1,sizeof(TChestionar));
	if (!x) return NULL;                     /* alocare imposibila!!! => NULL */
	x->avi = (TIntreb*)calloc(ni,sizeof(TIntreb));
	if (!x->avi)                   /* alocare imposibila!!! */
	{ free(x); return NULL; }      /* elibereaza spatiu descriptor si => NULL */
	x->ni = ni;
	return x;
}



/* Aloca spatiu (totul sau nimic!) pentru structura TSondaj si
   pentru vectorul de persoane, initializat cu 0 */
TSondaj* AlocS(int n, TChestionar* q)
{ TSondaj* x = (TSondaj*) calloc(1,sizeof(TSondaj));
	if (!x) return NULL;                     /* alocare imposibila!!! => NULL */
	x->avp = (TPers*)calloc(n,sizeof(TPers));
	if (!x->avp)                   /* alocare imposibila!!! */
	{ free(x); return NULL; }      /* elibereaza spatiu descriptor si => NULL */
	x->nmp = n;
	x->q = q;
	return x;
}


/* Eliberare integrala spatiu chestionar */
void ElibCh(TChestionar**x)
{
	int i;
	for ( i= 0 ; i< (*x) -> ni ; i++){
		free((*x) -> avi[i].intreb);
		free((*x) ->avi[i].avar);
	}
	free((*x)->avi);
	free(*x);
	x=NULL;
}


/* Eliberare spatiu sondaj, apeland ElibCh pentru eliberarea spatiului
   ocupat de chestionar */
void ElibS(TSondaj**x)
{
	TPers *p,*s=(*x)->avp + (*x)->nep;
	for(p=(*x)->avp ; p < s ; p++){
		free(p->arasp);
	}
	free((*x)->avp);
	ElibCh(&(*x)->q);
	free((*x));
	*x=NULL;
}

