/*-- T-q-LC.h -- coada este reprezentata ca Lista CIRCULARA --*/
#include "tcoada.h"

#ifndef _COADA_ListaCirculara_
#define _COADA_ListaCirculara_

typedef struct celula
{ struct celula * urm;
  char info;
} TCel, * ACel;

typedef struct coada
{ size_t dime, dimc; /* dimensiune element, dimensiune celula */
  ACel sc;           /* adresa ultimei celule */
} TCoada, *AQ;


/*- macrodefinitii utile -*/
#define DIME(ac) (((AQ)ac)->dime)
#define DIMC(ac) (((AQ)ac)->dimc)
#define SC(ac) (((AQ)ac)->sc)
#define IC(ac) (SC(ac)->urm)
#define DIMDIF(s,d) (DIME(s) != DIME(d))
#define VIDA(ac) (SC(ac) == NULL)

#endif

