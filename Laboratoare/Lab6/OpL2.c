/*--- OpL2.c ---
  operatii lista generica dublu inlantuita, circulara, cu santinela ---*/

#include "TL2.h"

TL2 InitL2(void* x)
	/* -> lista vida, cu info din santinela specifica aplicatiei */
{ TL2 aux = malloc (sizeof(TCel2));   /* incearca alocare santinela */
	if (aux)                              /* aux contine adresa santinelei */
	{ aux->pre = aux->urm = aux;          /* completeaza celula */
		aux->info = x;
	}
	return aux;     /* rezultatul este adresa santinelei sau NULL */
}

int InsL2(TL2 p, void* x)  /* inserare dupa celula cu adresa p -> 1/0 */
{ TL2 aux = (TL2)malloc (sizeof(TCel2));   /* incearca alocare celula */
	if (!aux) return 0;
	{ aux->pre = p;          /* completeaza celula */
		aux->urm = p->urm;
		p->urm->pre = aux;
		p->urm = aux;
		aux->info = x;
	}
	return 1;
}

size_t NrElem (TL2 s)      /* numarul de elemente din lista */
{
	TL2 p=s->urm;
	int nr=0;
	while(p!=s){
		nr++;
		p=p->urm;
	}
	return nr;
}

/*- functii de eliberare spatiu; parametrul fe – functie care elibereaza
  spatiul ocupat de un element */

void ResetL2(TL2 s, void (*fe)(void*))
	/* transforma lista in lista vida */
{
	TL2 pos = NULL, urm = NULL;

	for (pos = s->urm, urm = pos->urm; pos != s; pos = urm, urm = urm->urm)
	{
		if (fe != NULL)
			fe(pos->info);
		free(pos);
	}
	if (fe != NULL)
		fe(s->info);
	s->urm = s->pre = s;
}

void DistrL2(TL2* as, void (*fe)(void*))
	/* elibereaza tot spatiul ocupat de lista, inclusiv santinela */
{
}

void* ExtrL2 (TL2 p)  /* elimina celula de la adresa p -> adresa info */
{ void* r = p->info;             /* memoreaza adresa element */
	if (p == p->urm) return NULL;  /* lista vida -> NULL */
	p->pre->urm = p->urm;          /* deconecteaza din lista */
	p->urm->pre = p->pre;
	free (p);                      /* elibereaza spatiul ocupat de celula */
	return r;                      /* -> adresa element extras din lista */
}


int PreL2(TL2 s, TF1 f)
	/* aplica functia f tuturor elementelor -> numar elemente */
{ int i = 0;
	TL2 p = s->urm;
	for (; p != s; p = p->urm, i++)  /* pentru fiecare element */
		f(p->info);                    /* aplica functia f */
}


