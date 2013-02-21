/*--- graf-L.h --- Graf implementat cu liste --*/
#include "graf.h"

#ifndef _GRAF_L_
#define _GRAF_L_

typedef struct celarc 
{ TIdNod d;           /* destinatie arc */
  TCost c;            /* cost arc */
  struct celarc *urm; /* adresa urmatorul adiacent */
} TCelArc, *AArc;

typedef struct 
{ int nn;     /* numar noduri */
  AArc* x;    /* vector adrese liste arce */
} TGL, *AG;

#define G(x) ((AG)(x))
#define N(g) (((AG)g)->nn)

#endif
