/*-- T-st-V.h -- elementele stivei sunt memorate intr-un vector --*/
#include "tstiva.h"

#ifndef _STIVA_VECTOR_
#define _STIVA_VECTOR_

typedef struct
{ size_t maxe, dime;  /* numar maxim elemente in stiva, dimensiune element */
  char *b, *sv, *vf;  /* inceput, sfarsit vector, varful stiva */
} TStiva, *ASt;

/*- macrodefinitii utile */
/*- acces campuri -*/
#define DIMES(a) (((ASt)(a))->dime)
#define BS(a) (((ASt)(a))->b)
#define SV(a) (((ASt)(a))->sv)
#define VF(a) (((ASt)(a))->vf)
/*- teste -*/
#define DIMDIF(s,d) (DIMES(s) != DIMES(d))
#define VIDAS(a)  (VF(a) == BS(a))
#define PLINAS(a) (VF(a) == SV(a))

#endif
