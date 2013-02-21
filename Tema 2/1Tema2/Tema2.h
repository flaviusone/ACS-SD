/* Tirnacop Flavius 313CB */
#include "T-q-LD.h"
#ifndef ARBORE
#define ARBORE
typedef struct Elemente
{
    char tip,valoare[20];
    int indice;
    struct Elemente *urm;
}LElemente;

typedef struct Expresii
{
    char nume_exp[20];
    struct Expresii *urm;
    LElemente *elem;
}LExpresii;

typedef struct nod
{ char  info[20];
  struct nod*st, *dr;
} TNod, *TArb, **AArb;

typedef struct Rez
{
    char nume_exp[20];
    char reprez[100];
    double rezultat;
    TArb arbore;
    struct Rez *urm;
}Rez;
Rez* ConstrRez(LExpresii *a);
LExpresii* CitireFis (char numefis[]);
LElemente* Elimina(LElemente **a,LElemente *b);
int LungimeLista(LElemente *a);
LExpresii* Corectare(LExpresii* a);
void Repr(TArb r, int centru, int linie, int dif);
//void AfiArb(TArb r,FILE* f);
void AfiArb2(TArb r);
#endif
