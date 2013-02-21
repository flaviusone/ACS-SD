/*-- Test-LDI.c --*/
#include "tl2.h"

typedef struct {int x,y;} TPct, *APct;

#define XLP(a) (((TPct*)(a->info))->x)
#define YLP(a) (((TPct*)(a->info))->y)

void Citire(TL2 s,size_t N)
{  int i=0;
	TPct pct;
	TL2 aux;

	printf("Introduceti maxim %i perechi x si y\n", N);
	for (;i<N;i++)
	{ if(scanf("%i%i",&(pct.x),&(pct.y)) != 2) break;
		aux=(TL2)malloc(sizeof(TCel2));
		if (!aux) return;
		aux->info=malloc(sizeof(TPct));
		if (!aux->info) {free(aux); return;}
		*((APct)(aux->info))=pct;
		s->pre->urm=aux;
		aux->pre=s->pre;
		aux->urm=s;
		s->pre=aux;
	}
}

void Afisare(TL2 s,int d)
{TL2 p;
	if (d >= 0)
		for(p=s->urm;p!=s;p=p->urm)
			printf("\t%4i%5i\n",XLP(p),YLP(p));
	else
		for(p=s->pre;p!=s;p=p->pre)
			printf("\t%4i%5i\n",XLP(p),YLP(p));

}
int F1(const void* punct){
	return ((TPct*)punct)->x % 2;
}

int Grup(TL2 s, TF1 f , int Gasit){
	TL2 p ,r,aux;
	p = s->urm;
	r = s;
	int mutate=0;
	if(s==s->urm) return 0;
	while ( p!=s ){
		printf("f(p-info) %i",f(p->info));
		if(f(p->info) == Gasit){
			aux=p->urm;
			p->pre->urm=aux;
			p->urm->pre=p->pre;
			p->pre=r;
			p->urm=r->urm;
			r->urm->pre=p;
			r->urm=p;
			r=r->urm;
			p = aux;
			mutate++;
		}else p=p->urm;
	}
	return mutate;

}

int MutaSecv(TL2 s,int n,TF1 f, int Gasit){
	TL2 p,q,aux;
	if(s==s->urm) return 0;
	p=s->urm;
	q=s->urm;
	int nr=0;
	int precede=0;
	while(p!=s){
		while( f(q->info) == Gasit){
			nr++;
			printf("Nr  %i \n", nr);

			if (nr == n){
				//mutare
				printf("am intrat in mutare/n");
				aux = q->urm;
				p->pre->urm = q ->urm ; //
				q->urm->pre=p->pre;     //leg capetele
				p->pre = s->pre;
				q->urm = s;
				s->pre->urm = p;
				s->pre=q;
				//                return precede;
				/* dupa mutare parcurgere pana la sf listei */

				p=aux;
				while(p!=s){
					precede++;
					p=p->urm;
				}
				return precede;
				/* --------------------------------------*/
			}
			q=q->urm;
		}
		nr = 0;
		p = q;
		p=p->urm;
		q=q->urm;




	}
	return precede;

}

int main()
{ FILE *f;
	TPct pct, pp = {0,1};
	TL2 a;
	void*x;
	int nr;

	a=InitL2(x);
	Citire(a,10);
	printf("Lista:\n");
	Afisare(a,2);
	//printf("S-au mutat %i elemente \n", Grup(a,F1,0));
	//Afisare(a,2);
	printf("Nr de elemente ce precedau sublista %i \n",MutaSecv(a,2,F1,0));
	Afisare(a,2);

	/* Secventa din tema
	   printf("Lista inversata:\n");
	   Afisare(a,-1);
	   printf("Lista contine %i elemente\n",NrElem(a));
	   printf("Reseteaza lista\n");
	   ResetL2(a,free);
	   Afisare(a,2);
	   */
	//getch();
	return 0;
}


