/*-- T-q-V.h -- elementele cozii sunt memorate intr-un vector --*/
#include "tcoada.h"

#ifndef _COADA_VECTOR_
#define _COADA_VECTOR_

typedef struct
{ size_t dime, maxe;      /* numar maxim elemente in coada, dimensiune element */
  char *v, *sv, *ic, *sc; /* inceput, sfarsit vector, inceput, sfarsit coada */
} TCoadaV, *AQV;

/*- macrodefinitii acces la campuri -*/
#define V(a) (((AQV)(a))->v)
#define SV(a) (((AQV)(a))->sv)
#define IC(a) (((AQV)(a))->ic)
#define SC(a) (((AQV)(a))->sc)
#define DimEQ(a) (((AQV)(a))->dime)
/*- teste si prelucrari -*/
#define DIMDIF(s,d) (DimEQ(s) != DimEQ(d))  
#define VidaQ(a) (IC(a) == SC(a))
#define PlinaQ(a) ((SC(a)+DimEQ(a)) == (IC(a) == V(a) ? SV(a) : IC(a)))
#define Avans(a,p) ((p) = ((p) += DimEQ(a)) < SV(a) ? (p) : V(a))
#define Ocupat(a) ((SC(a) - IC(a)) + (IC(a) <= SC(a) ? 0: SV(a) - V(a)))
#define Liber(a) ((IC(a)-SC(a)-DIME(a)) + (IC(a) <= SC(a)? 0: SV(a)-V(a)))

#endif
