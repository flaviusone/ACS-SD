/*--- TestList.c ---*/
#include <conio.h>
#include <ctype.h>
#include "tlista.h"

TLista CitL(size_t N,size_t *lg)
{
    TLista r=NULL, *u=&r;
    int aux;
    *lg=0;
    while(N>0)
    {
        if(scanf("%i",&aux)<1) break;
        if(!InsInc(u,&aux))  break;
        (*lg)++;
        u = &((*u)->urm);
        N--;
    }
    return r;
}

ALista InsSfLr (ALista a, AEL x)
/* functie recursiva de inserare la sfarsitul listei;
   intoarce adresa legatura la celula inserata sau NULL */
{
    if(*a == NULL)
    {
        InsInc(a,x);
        return a;

    }
    else return InsSfLr(&(*a)->urm,x);
}

ALista CautaU_r(ALista a, TFPrelEL f, int Gasit)
/* functie recursiva - intoarce NULL sau adresa legatura la ultima celula
   pentru a carei info functia f intoarce valoarea Gasit */
{

    if(!(*a)) return NULL;
    if( f( &((*a)->info))==Gasit) return a;
    else CautaU_r(&(*a)->urm,f,Gasit);

}

int ElimCond(ALista a, TFPrelEL f, int Gasit)
/* obiectiv: eliminarea din lista a primei celule pentru a carei info
   functia f intoarce valoarea Gasit; rezultat 1 = succes, 0 = esec */
{
    if(!(*a)) return 0;
    while((*a)!=NULL)
    {
        if(f(&((*a)->info))==Gasit)
        {
            ElimPL(a);
            return 1;
        }
        a=&((*a)->urm);
    }
    return 0;
}

int Test(AEL e,...) /* functie de test, la alegere */
{
    return *(int*)e;
}

int main ()
{
    TLista x = NULL;     /* Lista prelucrata */
    size_t lx;           /* lungime lista */
    int val;

    for (;;)
    {
        printf("\nLungime lista: ");
        fflush(stdin);
        scanf("%i", &lx);
        if (lx <= 0) break;
        /* genereaza si afiseaza lista cu maxim lx elemente */
        x = GenerL(lx, -20, 50, "");
        AfisareL(&x, "x: [", "%4i", " ]\n");


        printf("\n--- Inserari la sfarsitul listei ---\n");
        /* - cat timp se citeste o valoare insereaza la sfarsitul listei
           - afisare lista */
        /*    printf("Introduceti valoare de inserat: ");
              while(scanf("%i",&val)>0){
              InsSfLr(&x,&val);
              AfisareL(&x, "x: [", "%4i", " ]\n");
              printf("Introduceti valoare de inserat: ");
              fflush(stdin);
              }
              */


        printf("\n--- Eliminari din lista ---\n");
        /*   printf("Introduceti valoare de eliminat: ");
             while(scanf("%i",&val)>0){
             if(ElimCond(&x,Test,val))
             AfisareL(&x, "x: [", "%4i", " ]\n");
             else
             printf("Element nu exista \n");
             printf("Introduceti valoare de eliminat: ");
             fflush(stdin);
             }
        /* - cat timp se citeste o valoare
        { apeleaza ElimCond
        daca succes atunci afisare lista
        altfel afisare mesaj
        }
        */
        ALista aux;
        printf("\n--- Cautari in lista ---\n");
        AfisareL(&x, "x: [", "%4i", " ]\n");
        printf("Introduceti valoare de cautat: ");
        while(scanf("%i",&val)>0)
        {
            aux = CautaU_r(&x,Test,val);
            if(aux)
            {
                printf("Elementul se afla la adresa %p si are val %i \n",*aux,(*aux)->info);
            }
            else printf("Elementul nu a fost gasit \n");
            AfisareL(&x, "x: [", "%4i", " ]\n");
            printf("Introduceti valoare de inserat: \n");
            fflush(stdin);
        }
        /* - cat timp se citeste o valoare
           apeleaza CautaU_r si afiseaza rezultat (adresa si info) */

        DistrL(&x);
        printf ("\n  Inca un test ? [D/] ");
        if (toupper(getch()) != 'D') break;
    }
}

