/*-- T-q-LD.h -- coada este reprezentata ca Lista DESCHISA --*/
#include "tcoada.h"

#ifndef _COADA_ListaDeschisa_
#define _COADA_ListaDeschisa_

typedef struct celula
{ struct celula* urm;
  char info;
} TCel, *ACel;

typedef struct coada
{ size_t dime, dimc; /* dimensiune element, dimensiune celula */
  ACel ic, sc;       /* adresa primei si ultimei celule */
} TCoada, *AQ;

/*- macrodefinitii acces la campuri -*/
#define DIME(a) (((AQ)(a))->dime)
#define DIMC(a) (((AQ)(a))->dimc)
#define IC(a) (((AQ)(a))->ic)
#define SC(a) (((AQ)(a))->sc)
/*- teste -*/
#define DIMDIF(s,d) (DIME(s) != DIME(d))
#define VIDA(a) (IC(a) == NULL)

#endif
