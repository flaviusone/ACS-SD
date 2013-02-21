/*-- Tst-L.h --- implementare stivei ca lista ---*/
#include "tstiva.h"

#ifndef _STIVA_DINAMICA_
#define _STIVA_DINAMICA_

typedef struct celst
{ struct celst *urm;   /* adresa urmatoarei celule */
  void* info;          /* adresa informatie */
} TCelSt, *ACelSt;

typedef struct stiva
{ size_t dime, dimc; /* dimensiune element, dimensiune celula */
  ACelSt vf;         /* adresa celulei din varful stivei */
} TStiva, *ASt;

#define VF(a) (((ASt)(a))->vf)
#define DIMES(a) (((ASt)(a))->dime)
#define DIMC(a) (((ASt)(a))->dimc)

#endif
