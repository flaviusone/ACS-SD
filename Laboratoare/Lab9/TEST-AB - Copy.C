/*-- test-ab.c --  prelucreaza arbori binari cu chei intregi --*/
#include "tarb.h"
#include "random.h"
#include "AUXARB.c"
#include "TARB.c"

/*-- se completeaza cu definitiile functiilor implementate --*/
    int F1(TArb r)
    {
        int n = 0;

        if (!r)
            return 0;

        if (r->st && r->dr && r->info > 0) {
            n += 1;
            printf(" %i ", r->info);
        }

        return n + F1(r->dr) + F1(r->st);
    }
int F2(TArb r,int n)
{
  int L;
  if (!r) return 0;
  if (n == 0)
  {
    if(r->info%2==0)
            return 1;
        else
            return 0;
  }
  L=F2(r->st, n-1);
  L+=F2(r->dr, n-1);
  return L;

}

int A1(TArb a, int niv)
{
  int n;
  if(!a) return 0;
  n=A1(a->st,niv+1);
    if((a->st!=NULL && a->dr==NULL) || (a->st==NULL && a->dr !=NULL) ) //daca are 1 subarbore
        if( a->info%2==0) //daca par
         {
          n++;
          printf("%i [%i] \n",a->info, niv);
         }
  n+=A1(a->dr,niv+1);
  return n;
}
int A2(TArb a, int niv)
{
  int n;
  if(!a) return 0;
  n=A2(a->st,niv+1);
  if (niv%2 != 0) //daca nivel e impar
  {
    if(a->info%2==0 && a->info>0) //info pare si pozitivve
        n++;
  }
  n+=A2(a->dr,niv+1);
  return n;
}
int A3(TArb a1, TArb a2)
{
  int n;
  if((a1!=NULL && a2==NULL)||(a1==NULL && a2!=NULL))
      return 0;
  if((a1==NULL && a2==NULL))
      return 1;
  n=A3(a1->st,a2->st);
  if(!n) return 0;
  n = A3(a1->dr,a2->dr);
  return n;
}

int main ()
{ TArb arb,arb2;
  char r;

  randomize();
  do { arb = ConstrAA (5, random(16), -50, 50);
       arb2 = ConstrAA (5, random(16), -50, 50);
       AfiArb (arb);
       //AfiArb (arb2);
       printf ("noduri: %i   niveluri: %i\n", NrNoduri(arb), NrNiv(arb));

       /*-- se completeaza cu apelurile functiilor implementate --*/
       printf("\nRezultat F1 %i \n",F1(arb));
       printf("\nRezultat F2 %i \n",F2(arb,2));
       //printf("<>A1<> S-au afisat %i valori\n",A1(arb,0));
       //printf("<>A2<> nr de valori pozitive si pare de pe niveluri impare = %i \n",A2(arb,0));
       if(A3(arb,arb))
        printf("Arborii sunt la fel \n");
        else
        printf("Nu sunt la fel \n");

       DistrArb (&arb);
       printf ("\nInca un arbore ? [D/N] ");
       for (; (r = toupper (getch())) != 'D' && r != 'N'; ); /* preia raspuns */
       printf ("%c\n", r);                              /* afiseaza raspunsul */
     } while (r != 'N');
}
