/*--- TestList.c ---*/
#include <conio.h>
#include <ctype.h>
#include "tlista.h"



TLista CitL(size_t N,size_t *lg){
	TLista r=NULL, *u=&r;
	int aux;
	*lg=0;
	while(N>0){
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
	if(*a == NULL){
		InsInc(a,x);
		return a;

	}else return InsSfLr(&(*a)->urm,x);
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
	{ if(f(&((*a)->info))==Gasit)
		{ ElimPL(a);
			return 1;
		}
		a=&((*a)->urm);
	}
	return 0;
}
int F1 (TLista L){
	int perechi = 0,i;
	TLista p=L;
	for(i=1;p != NULL && p->urm != NULL ; p = p->urm->urm ,i++){
		if((p->info)*(p->urm->info) > 0 )
			printf("%2i.%4i%4i\n",i,p->info,p->urm->info);
		perechi++;
	}
	return perechi;
}

ALista F2(ALista A){
	ALista x=A,y=NULL;

	int min;
	min = 30000;

	while (*x != NULL){
		if((*x)->info % 2 == 0){
			if((*x)->info < min){
				min = (*x)->info;
				y=x;
			}
		}
		x = &((*x)->urm);
	}
	return y;


}

int Test(AEL e,...) /* functie de test, la alegere */
{return *(int*)e;}

int main ()
{   TLista x = NULL;     /* Lista prelucrata */
	size_t lx;           /* lungime lista */
	int val;
	int N,lg;
	ALista y;
	printf("Introduceti lungime dorita pt lista ");
	scanf("%i",&N);
	x = CitL(N,&lg);
	AfisareL(&x, "x: [", "%4i", " ]\n");
	//printf("S-au gasit %i perechi", F1(x));
	y = F2(&x);
	if(y)
		printf("%i",(*y)->info);
	else
		printf("nu sunt elemente");
}

