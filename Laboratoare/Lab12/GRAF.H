/*--- graf.h --- Graf --*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#ifndef GRAF__
#define GRAF__

typedef int TIdNod;
typedef int TCost;

#define NodInex 0
#define ArcInex 0

void* AlocG(int,...); /* aloca memorie pt.reprezentare graf cu nr.noduri dat */
void* CopieG(void*);  /* construieste copia grafului dat */
void DistrG(void**);  /* elibereaza tot spatiul ocupat de graf */

int NrNoduri(void*);
TCost CostArc(void*, TIdNod, TIdNod);
int ModifCost(void*, TIdNod, TIdNod, TCost);
TIdNod PrimAd(void*, TIdNod);
TIdNod UrmAd(void*, TIdNod, TIdNod);

int CitGraf(void**);  /* citeste descriere graf */
void AfiGrafM(void*); /* afisare ca matrice */
void AfiGrafL(void*); /* afisare liste de adiacente */

#define ExistaArc(g,s,d) (CostArc(g,s,d) != ArcInex)

#endif
