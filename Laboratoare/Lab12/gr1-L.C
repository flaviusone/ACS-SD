/*--- grafL.c --- Graf implementat cu liste --*/
#include "graf-L.h"

void* AlocG(int n,...) /* aloca spatiu pentru descriptor graf si
	                  vector de (n+1) adrese liste arce */
{ int i, j;
  AG g = (AG)malloc(sizeof(TGL));    /* spatiu descriptor */
  if (!g) return NULL;
  g->x = (AArc*)calloc((n+1), sizeof(AArc)); /* spatiu vector adr.liste arce */
  if(!g->x) { free(g); return NULL; }
  g->nn = n;
  return (void*)g;
}

void DistrG(void** ag)
{ TIdNod i;
  AArc p, aux;
  for(i = 1; i < N(*ag); i++)
  { p = G(*ag)->x[i];
    while(p)
    { aux = p; p = p->urm;
      free(aux);
    }
  }
  free(G(*ag)->x);
  free(*ag);
  *ag = NULL;
}

int NrNoduri(void* g)
{ return N(g); }

TCost CostArc(void* g, TIdNod s, TIdNod d)
{ AArc p = G(g)->x[s];
  for(; p && p->d < d; p = p->urm); /* avans peste predecesori */
  if(p && p->d == d) return p->c;
  /* s-a ajuns la sfarsit lista sau la succesor */
  return ArcInex;
}

int ModifCost(void* g, TIdNod s, TIdNod d, TCost c)
{ AArc p = G(g)->x[s];
  while(p && p->d < d) p = p->urm; /* avans peste predecesori */
  if(p && p->d == d) { p->c = c; return 1;}
  return 0;
}

TIdNod PrimAd(void* g, TIdNod s)
{ AArc a = G(g)->x[s];
  if (!a) return NodInex;
  return a->d;
}

TIdNod UrmAd(void* g, TIdNod s, TIdNod x)
{ AArc p = G(g)->x[s];
  for (; p != NULL && p->d <= x; p = p->urm);
  return !p ? NodInex : p->d;
}

int CitGraf(void** ag)
{ FILE * f;
  char numefis[21];
  AG g;
  TIdNod s, d;
  TCost x;
  AArc *p, aux;
  int i, n;

  printf("Numele fisierului de descriere a grafului = ");
  if (!scanf("%s", numefis)) return -1;
  f = fopen (numefis, "rt");
  if (!f) return -2;
  if (!fscanf (f, "%i", &n) || n <= 0) return -3;
  *ag = AlocG(n);
  g = *(AG*)ag;
  if (!g) return 0;
  while (fscanf(f, "%i%i%i", &s, &d, &x) == 3)
  { if (s < 1 || s > n || d < 1 || d > n)
    { fclose(f); return -4;}
    p = g->x + s;
    while (*p && (*p)->d < d) p = &(*p)->urm;
    aux = (TCelArc*)calloc(sizeof(TCelArc),1);
    if (!aux) return -2;                     /* criza spatiu */
    aux->urm = *p; *p = aux;
    aux->d = d; aux->c = x;
  }
  fclose(f);
  return 1;
}

void AfiGrafL(void* g)
{ int s;
  AArc p;
  for (s = 1 ; s <= N(g); s++)
  { printf("%3i : ", s);
    for (p = G(g)->x[s]; p != NULL; p = p->urm)
      printf("%3i (%i)", p->d, p->c);
    printf("\n");
  }
}

void AfiGrafM(void* g)
{ int i, j, n = N(g);
  TCost c;
  printf ("   ");
  for (i = 1; i <= n; i++) printf("_%2i_", i); /* indici coloane */
  printf("\n");
  for (i = 1; i <= N(g); i++)
  { printf("%2i|", i);
    for (j = 1; j <= n; j++)
    { c = CostArc(g, i, j);
      if (c == ArcInex)
	printf("  - ");
      else
	printf("%3i ", c);
    }
    printf("\n");
  }
}
