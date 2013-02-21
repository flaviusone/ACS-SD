/*-- sondaj.h.c --*/
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>


#ifndef __SONDAJ__
#define __SONDAJ__
typedef struct
{ char* intreb; /* text intrebare, alocat dinamic */
  int nr, lgr;  /* numar variante raspuns (maxim 9), lg.max text varianta */
  char* avar;   /* adresa variante, mem in spatiu alocat dinamic
                   exemplu pt lgr = 8: |clasic@  |rock@    |folclor@ |..... */
} TIntreb;

typedef struct
{ int ni;       /* numar intrebari */
  TIntreb* avi; /* adresa vector intrebari a    locat dinamic */
} TChestionar;

typedef struct
{ char* arasp;  /* adresa sir raspunsuri alocat dinamic */
  char info[4]; /* [0] M/F
                   [1] 'A'-'H' = cod ocupatie
                   [2] prima cifra a varstei ('2': 20-29, '9': >= 90)
                   [3] 'A'-'G' = cod nivel educatie */
} TPers;

typedef struct
{ int nmp, nep;    /* numar maxim si numar efectiv persoane */
  TPers* avp;      /* adresa vector persoane alocat dinamic */
  TChestionar* q;  /* adresa chestionar */
} TSondaj;

TChestionar* AlocCh(int ni);
TSondaj* AlocS(int n, TChestionar* q);
void ElibCh(TChestionar**x);
void ElibS(TSondaj**x);

#endif
