/*-- test-ab.c --  prelucreaza arbori binari cu chei intregi --*/
#include "tarb.h"
#include "random.h"
#include "AUXARB.c"
#include "TARB.c"

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

int InserAC(int cheie, TArb *aa,int lim)
{
    /* cautare */
    int auxlim=0;
    while (*aa)
    {
        auxlim++;
        if (auxlim==lim) return 0;
        if ( cheie == (*aa)->info) return -1;
        if ( cheie < (*aa)->info)
            aa = &((*aa)->st);
        else
            aa = &((*aa)->dr);
    }
    /* inserare */
    *aa = ConstrFr(cheie);
    return *aa != NULL; /* 1 sau 0 */
}


TArb CitABC(int lim)
{
    int cheie;
    TArb a=NULL;
    printf("Introduceti cheie: ");
    while(scanf("%i",&cheie)!=0)
    {

        if(!InserAC(cheie,&a,lim)) return a;
        printf("Introduceti cheie: ");
    }
    return a;
}
void F1Aux(TArb a, int r , int *nrt , int *nrf , int *nrtf)
{

    if (!a) return;
    if (r == 0)
    {
         (*nrt)++;
        if(a->st==NULL && a->dr==NULL) (*nrf)++; //eventual un return aici
    }
    if(a->st==NULL && a->dr==NULL) (*nrtf)++;
    F1Aux(a->st, r-1,nrt,nrf,nrtf);
    F1Aux(a->dr, r-1,nrt,nrf,nrtf);
}

int F1(TArb a, int r,double *p)
{
    int nrt=0,nrf=0,nrtf=0;
    F1Aux(a,r,&nrt,&nrf,&nrtf);
    if (!nrtf) *p=0;
    else *p=100. * nrf/nrtf;
    return nrt;
}
void F2Aux(TArb a, int niv, int* rez)
{
    if (!a) return;
    F2Aux(a->st,niv+1,rez);
    if(a->st==NULL && a->dr==NULL)
    {
        if(*rez==-2)
            *rez = niv;
        else
            if(*rez!=niv && *rez>=0)
             {
                *rez=-1;
                return;
             }
    }
    F2Aux(a->dr,niv+1,rez);
}

int F2(TArb a)
{
    int rez=-2,niv=0;
    F2Aux(a,niv,&rez);
    return rez;
}

int main ()
{
    TArb arb,arb2;
    char r;
    int lim,nivel,rez;
    double procent=0;
    randomize();
    do
    {
        //AfiArb (arb);
        //arb2 = ConstrAA (5, random(16), -50, 50);
        printf("Introdu lim= ",lim);
        scanf("%i",&lim);
        arb2=CitABC(lim);
        AfiArb (arb2);
        /*
        printf("Introduceti nivelul ");
        fflush(stdin);
        scanf("%i",&nivel);
        printf("Nr de noduri de pe nivelul %i este %i\n",nivel,F1(arb2,nivel,&procent));
        printf("Procentul este %5.2f \n",procent);
        */
        rez=F2(arb2);
        if(rez <0) printf("Nu are toate frunzele pe acc nivel \n");
        else printf("Toate frunzele pe nivelul %i",rez);
        DistrArb (&arb2);
        printf ("\nInca un arbore ? [D/N] ");
        for (; (r = toupper (getch())) != 'D' && r != 'N'; ); /* preia raspuns */
        printf ("%c\n", r);                              /* afiseaza raspunsul */
    }
    while (r != 'N');
}
