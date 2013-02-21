/*--- gr1-M.c --- Graf implementat cu Matrice de adiacente --*/
#include "graf-M.h"
#include <string.h>

void* AlocG(int n,...)
{ int i, j;
  AG g = (AG)malloc (sizeof(TGM));
  if (!g) return NULL;
  g->x = (TCost*)malloc(n * n * sizeof(TCost));
  if (!g->x) { free(g); return NULL; }
  for (i = 0; i < n * n; i++)
    g->x[i] = ArcInex;
  g->nn = n;
  return (void*)g;
}

void* CopieG(void* g)
{ int i, n = NrNoduri(g);
  AG c = (AG)AlocG (n);
  TCost * s = ((AG)g)->x;

  if (!c) return NULL;
  memcpy(c->x, s, n*n*sizeof(TCost));
  return (void*)c;
}

void DistrG(void** ag)
{ free (G(*ag)->x); free(*ag);
  * ag = NULL;
}

int NrNoduri(void* g)
{ return N(g); }

TCost CostArc(void* g, TIdNod s, TIdNod d)
{ if (s < 1 || s > N(g) || d < 1 || d > N(g)) return ArcInex;
  return CA(g, s, d);
}

int ModifCost(void* g, TIdNod s, TIdNod d, TCost c)
{ if (s < 1 || s > N(g) || d < 1 || d > N(g)) return 0;
  CA(g, s, d) = c;
  return 1;
}

TIdNod PrimAd(void* g, TIdNod s)
{ TCost * u = G(g)->x + s * N(g), * p = u - N(g), * q;
  for (q = p; q < u; q++)
    if (*q != ArcInex) return q-p+1;
  return NodInex;
}

TIdNod UrmAd(void* g, TIdNod s, TIdNod x)
{ TCost * u = G(g)->x + s * N(g), * p = u - N(g), * q;
  for (q = p + x; q < u; q++)
    if (*q != ArcInex) return q-p+1;
  return NodInex;
}

int CitGraf(void** ag)
{ FILE * f;
  char numefis[21];
  TIdNod i, j, n;
  TCost x;
  AG g;

  printf("Numele fisierului de descriere a grafului = ");
  if (!scanf("%s", numefis)) return -1;
  f = fopen(numefis, "rt");
  if (!f) return -2;
  if (!fscanf(f, "%i", &n) || n <= 0) return -3;
  *ag = g = (AG)AlocG(n);
  if (!g) return 0;
  while (fscanf(f, "%i%i%i", &i, &j, &x) == 3)
  { if (i < 1 || i > n || j < 1 || j > n)
    { fclose(f); return -4;}
    CA(g,i,j) = x;
  }
  fclose(f);
  return 1;
}

