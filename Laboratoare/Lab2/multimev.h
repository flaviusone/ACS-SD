
/*-- multimeV.h --*/
/*-- Multimi generice (elemente de orice tip) memorate ca vectori --*/

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#ifndef  _TMULTIME_
#define  _TMULTIME_

typedef int(*TFComp)(const void *, const void *);
typedef struct
{ size_t d;        /* dimensiune elemente */
  TFComp fid;      /* verificã identitatea elementelor */
  TFComp ord;      /* functia de ordonare sau NULL */
  void *v, *s, *t; /* adrese vector, sfarsit zona utila, disponibila */
} TMultime;

#define VidaM(m) ((m)->s == (m)->v)
#define PlinaM(m) ((m)->s == (m)->t)
#define Card(m) (((m)->s-(m)->v)/(m)->d)

/*--- initializari ---*/

TMultime *InitD(size_t n, size_t d, TFComp fid, TFComp ord);
     /* creeaza multime, alocand dinamic spatiu pentru descriptor
        si n elemente de dimensiune d; intoarce adr.multime sau NULL */
void InitS(TMultime *m, void *v, size_t n, size_t d,
           TFComp fid, TFComp ord);
     /* initializeaza multimea m, cu maxim n elemente de dimensiune d,
        memorate in vectorul v, deja alocat static sau dinamic */

/*--- operatii asupra multimilor NESORTATE ---*/

int Adauga(void *nou, TMultime *m);
     /* obiectiv: adaugarea unui nou element la sfarsitul vectorului;
        intoarce 1/0/-1 - succes/exista deja/lipsa spatiu */
int Elimina(void *x, TMultime *m);
     /* intoarce 1/0 cu semnificatia eliminat / nu exista */
void* Loc(void *x, TMultime *m);
     /* intoarce adresa elementului cautat sau NULL */

/*-- operatii cu rezultat 1/0 cu semnificatia adevarat/fals*/
#define Apartine(x,m) ((Loc(x,m)!=NULL))
int Identice(TMultime *m1, TMultime *m2);
int Inclus(TMultime *m1, TMultime *m2); //aka include

/*-- spatiul pentru multimea rezultat alocat in prealabil, la adresa r;
     rezultat intors = cardinalul multimii rezultat (>= 0) */
int Reuniune(TMultime *m1, TMultime *m2, TMultime *r);
int Diferenta(TMultime *m1, TMultime *m2, TMultime *r); //defacut
int Intersectie(TMultime *m1, TMultime *m2, TMultime *r); //defacut

/*--- operatii asupra multimilor SORTATE ---*/

int Inserare(void *nou, TMultime *m);
     /* obiectiv: inserarea noului element in vectorul ordonat;
        intoarce 1/0/-1 - succes/exista deja/lipsa spatiu */
int ElimO(void *x, TMultime *m);
     /* intoarce 1/0 cu semnificatia eliminat / nu exista */
void* LocO(void *x, TMultime *m);
     /* cautare secventiala, cu oprire la elem cautat sau la succesor
        sau la sfarsit; intoarce adresa elementului gasit sau NULL */
void *CautBin(void *x, TMultime *m, int *r);
     /* cautare binara in vector sortat; daca elementul cautat exista,
        atunci intoarce adresa si 1 (la adresa r),
        altfel intoarce adresa primului succesor si 0 */

/*-- operatii cu rezultat 1/0 cu semnificatia adevarat/fals*/
int IdenticeO(TMultime *m1, TMultime *m2);
int IncludeO(TMultime *m1, TMultime *m2);

/*-- spatiul pentru multimea rezultat alocat in prealabil, la adresa r;
     rezultat intors = cardinalul multimii rezultat (>= 0) */
int ReuniuneO(TMultime *m1, TMultime *m2, TMultime *r);
int DiferentaO(TMultime *m1, TMultime *m2, TMultime *r); //defacut
int IntersectieO(TMultime *m1, TMultime *m2, TMultime *r);

/*--- functii auxiliare ---*/

void *DeplDr(void *a, size_t dim, size_t d);
      /* deplaseaza cu d octeti la dreapta un pachet de dim octeti */
void DeplSt(void *a, size_t dim, size_t d);
      /* deplaseaza cu d octeti la stanga un pachet de dim octeti */
void Copie(void *dest, void *sursa, size_t n);
      /* copiaza la destinatie n octeti de la sursa */
void Invers(void *a, void *b, size_t n);
      /* inversearza n octeti intre a si b */
int Intersectie_Daniela(TMultime *a,TMultime *b);
#endif

/*-- declaratii necesare pentru generarea de valori aleatoare --*/
#ifndef randomize
#include <time.h>
#define random(num)   (rand() % (num))
#define randomize()   srand((unsigned)time(NULL))
#endif

/*-------------*/

