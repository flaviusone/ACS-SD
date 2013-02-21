/*--- graf-M.h --- Graf implementat cu Matrice de adiacente --*/
#include "graf.h"

#ifndef _GRAF_M_
#define _GRAF_M_

typedef struct 
{ TIdNod nn;   /* numar noduri */
  TCost* x;   /* vector costuri = matrice liniarizata */
} TGM, *AG;

#define G(x) ((AG)(x))
#define N(g) (((AG)g)->nn)
#define CA(g,s,d) (G(g)->x[(s-1) * N(g) + d-1])

#endif
