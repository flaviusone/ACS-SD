/*--- Liste.c ---*/
#include <conio.h>
#include <ctype.h>
#include "tlista.h"


/*- TransfM – transforma o lista (neordonata) in multime, eliminand duplicatele; rezultate: cardinalul multimii si numarul de elemente eliminate
  - OrdL – ordoneaza o lista, conform relatiei testate de functia de comparatie transmisa ca parametru (utilizati algoritmul prezentat in curs 4)
  - TransfM_O – transforma o lista ordonata in multime, eliminand duplicatele; rezultate: cardinalul multimii si numarul de elemente eliminate
  */

TLista CitL(size_t N,size_t *lg)
{
	TLista r=NULL, *u=&r;
	int aux;
	*lg=0;
	printf("Introduceti elementele listei:");
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
int TransfM(ALista x,int* elim)
{
	int card = 0;
	ALista y,z;
	for (; *x != NULL ; card++ , x = &(*x)->urm)
		for(y = &(*x)->urm ; *y != NULL ; y = &(*y)->urm)
			if ((*x)->info == (*y)->info)
			{
				ElimPL(y);
				(*elim)++;
				y = x;
			}
	return card;

}
int TransfM_O(ALista x,int* elim)
{
	int card = 0;
	ALista y,z;
	for (; *x != NULL ; card++ , x = &(*x)->urm)
		for(y = &(*x)->urm ; *y != NULL && (*y)->info == (*x)->info  ; y = &(*y)->urm)
		{
			ElimPL(y);
			ElimPL(y);
			(*elim)++;
			y = x;
		}
	return card;

}
int compI(const void *a, const void *b) /*-- functie de comparare --*/
{
	return *(int*)a - *(int*)b;
}
OrdL2(ALista x ,TFComp f )
{
	ALista p , q , aux , z ;
	if (!x) return x;
	if (!&(*x)->urm) return x;
	p = x;
	q = &(*x)->urm;
	while(*p != NULL && *q != NULL)
	{
		if(f(&(*q)->info,&(*p)->info) > 0 )
		{
			p = &(*p)->urm;
			q = &(*q)->urm;
		}
		else
		{
			aux = q;
			(*p)->urm = &(*q)->urm; //legat cele 2 elemente initiale
			for(z = x ; z != p ; z = &(*z)->urm)
				if (f(&(*aux)->info,&(*x)->info)<0)
				{
					//bagal la inceputu listei
					(*aux)->urm = x;
					x = aux;
					break;
				}
				else
				{
					if (f(&(*aux)->info,&(*z)->urm->info)<0)
					{
						(*aux)->urm = &(*z)->urm;
						(*z)->urm = aux;
						break;
					}

				}
			p = &(*p)->urm;
			q = &(*p)->urm;
		}


	}

	return x;
}

TLista OrdL(TLista L, TFComp f)
{
	TLista inc = L, aL, aux;
	TEL val;

	for(; L && L->urm; )

		if( f(&L->info, &L->urm->info) <= 0 )
			L = L->urm;
		else
		{
			val = L->urm->info;
			aL = inc;
			L->urm = L->urm->urm;
			if( f(&val, &aL->info) < 0 )
			{
				aux = AlocCel(&val);
				aux->urm = aL;
				inc = aux;
				aL = NULL;
			}
			for(; aL && aL->urm; aL = aL->urm)
				if( f(&val, &aL->urm->info) < 0 )
				{
					aux = AlocCel(&val);
					aux->urm = aL->urm;
					aL->urm = aux;

					break;
				}
		}
	return inc;
}

int F5_1(int (*f)(const void *, const void *),TLista x)
{
	int i = 1 ,ns = 0,ii;
	TLista p = x;
	while(p!= NULL && p->urm != NULL)
	{
		if(f(&(p->info),&(p->urm->info))<0)
		{
			ii = i;
			do
			{
				p = p->urm;
				i++;
			}
			while(p->urm != NULL && f(&(p->info),&(p->urm->info))<0);
			printf("[%i_%i] ",ii,i);
			ns++;
		}
		p=p->urm;
		i++;

	}
	return ns;
}
TLista F5_2(ALista x, int rm,size_t *lgy)
{
	TLista r = *x,p = *x;
	(*lgy)=0;
	if(*x == NULL) return NULL; //caz lista goala
	if((*x)->urm == NULL) //are un sg element
		if(p->info < rm) //daca elementul mai mic rm
		{
			*x = NULL;
			return r;
		}
		else return NULL;
	while(p->urm != NULL )
	{
		if((p->urm->info) < rm)
		{
			(*lgy)++;
			p = p->urm; // se opreste inainte de p->urm
		}
		else break;
	}

	*x = p->urm;
	p->urm = NULL;
	return r;
}






TLista F5_3(TLista x, int rm, size_t *lgy){

	TLista r = NULL, p = x;
	(*lgy)=0;
	if(x == NULL) return NULL; //caz lista goala
	if((x)->urm == NULL) //are un sg element
		if(p->info < rm) //daca elementul mai mic rm
		{
			InsSfL(&r,&(p->info));
		}
		else return NULL;
	while(p->urm != NULL )
	{
		if((p->urm->info) < rm)
		{
			InsSfL(&r,&(p->info));
			(*lgy)++;
			p = p->urm; // se opreste inainte de p->urm
		}
		else break;
	}
	InsSfL(&r,&(p->info));
	(*lgy)++;
	//p->urm = NULL;
	return r;

}

int main ()
{
	TLista x = NULL,y;     /* Lista prelucrata */
	size_t lx,lgy;           /* lungime lista */
	int val , elim = 0,N;

	/* Secventa citire lista de la tastatura */
	printf("Introduceti lungime dorita pt lista: ");
	scanf("%i",&N);
	x = CitL(N,&lx);
	AfisareL(&x, "x: [", "%4i", " ]\n");
	///////////////////////////////////////////

	/*Secventa functie f5_1 */
	//    printf("\nNumar de subliste %i",F5_1(compI,x));
	/* Secventa F5_2
	   y = F5_2(&x, 20 , &lgy);
	   AfisareL(&x, "x: [", "%4i", " ]\n");
	   AfisareL(&y, "y: [", "%4i", " ]\n");
	   printf("Lungime y: %i",lgy);
	   */

	/*
	   y = F5_3(x, 20 , &lgy);
	   AfisareL(&x, "x: [", "%4i", " ]\n");
	   AfisareL(&y, "y: [", "%4i", " ]\n");
	   printf("Lungime y: %i",lgy);
	   */



	/*Secventa TransfM *//*
				printf("Cardinal multime: %i \n",TransfM(&x,&elim));
				printf("S-au eliminat %i elemente \n",elim);
				AfisareL(&x, "x: [", "%4i", " ]\n");
	//////////////*/

	/*Secventa ordonare */ /*
				  OrdL2(&x,compI);
				  AfisareL(&x, "x: [", "%4i", " ]\n");
	//////////////////*/

	/*Secventa TransfM_O */ /*
				   printf("Cardinal multime: %i \n",TransfM_O(&x,&elim));
				   printf("S-au eliminat %i elemente \n",elim);
				   AfisareL(&x, "x: [", "%4i", " ]\n");
	/////////////////*/
}
