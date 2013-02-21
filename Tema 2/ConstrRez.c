/*Tirnacop Flavius*/
#include "Tema2.h"
#define MAX 256
#define Frunza(a) ((a)->st == NULL && (a)->dr == NULL)
TArb Celmaiinalt(TArb a)
{
	/*returneaza adresa celui mai inalt nod care
	  e operand ( + - * /) si nu are fii */
	void *a1;
	char x[20];
	TArb b,inalt;
	a1 = InitQ (sizeof(TArb),MAX);
	if(!a1) return NULL;
	IntrQ(a1,&a);

	while(VidaQ(a1)!=1)
	{
		ExtrQ(a1,&b);
		if( b->info[0] == '+' || b->info[0] == '-' || b->info[0] == '*' || b->info[0] == '/' )
			if(b->st==NULL && b->dr==NULL)
				return b;
			else
			{
				IntrQ(a1,&b->st);
				IntrQ(a1,&b->dr);
			}
	}
	return NULL;
}

double Evaluare(TArb a)
{
	double x,y;
	if (!a) return 0;
	x=Evaluare(a->st);
	y=Evaluare(a->dr);
	if(a->info[0] == '+')
	{
		return x + y;
	}
	if(a->info[0] == '-')
	{
		return x - y;
	}
	if(a->info[0] == '*')
	{
		return x * y;
	}
	if(a->info[0] == '/')
	{
		return x / y;
	}
	else
	{
		return atoi(a->info);
	}
}
void Reprez(TArb r,char* x)
{
	if (Frunza(r))
	{
		strcat(x,r->info);
		return;
	}
	//strcat(x,"("); /*sau fara*/
	Reprez (r->st,x);
	strcat(x,r->info);
	Reprez (r->dr,x);
	//strcat (x,")");  /*sau fara*/
}

Rez* ConstrRez(LExpresii *a)
{
	Rez *rez=NULL,*head=NULL,*auxrez;
	LElemente *b;
	TArb arb,auxnod,nodinalt;
	int n,v[100]= {0},i;
	/*  rez parcurge lista cand o construiesc
	    head tine minte inceputul listei rez
	    arb adresa arborelui din fiecare celula a lui rez
	    auxnod aloca elemente pt noduri
	    nodinalt cel mai inalt nod care e + - * / si nu are fii
	    */

	while(a) /*pentru fiecare expresie in parte */
	{
		/*aloca celula rez*/
		/*-----daca arbore vid sare elementul*/
		while(!a->elem )
		{
			a=a->urm;
			if(!a) break;
		}
		if(!a) break;
		/*-----------------*/
		auxrez=(Rez*)malloc(sizeof(Rez));
		if(!auxrez) break;
		if(!head) head=auxrez;
		auxrez->arbore=NULL;
		strcpy(auxrez->reprez,"");
		strcpy(auxrez->nume_exp,a->nume_exp);
		/*sf alocare celula rez + numele ei*/

		/* crearea unui vector de parinti */
		for (i=0;i<100;i++) v[i]=0;
		b=a->elem;
		while(b)
		{
			v[b->indice]++;
			b=b->urm;
		}
		n = LungimeLista(a->elem);
		/*sf creare vector parinti*/

		/*adaugam intai radacina*/
		b=a->elem;
		while(b)
		{
			if(b->indice==0) break;
			b=b->urm;
		}

		arb = (TArb)malloc (sizeof(TNod));
		strcpy(arb->info,b->valoare);
		arb->st=NULL;
		arb->dr=NULL;
		auxrez->arbore = arb;
		/*sfarsit adaugare radacina*/

		/*adaugam restul elementelor */
		for( i = 1 ; i < n ; i++)
		{
			if ( v[i] != 0 ) /*trebuie introduse 2 elemente undeva*/
			{
				nodinalt=Celmaiinalt(arb);
				b=a->elem;
				while(b)
				{
					if(b->indice == i)
						if(nodinalt->st==NULL)
						{
							auxnod = (TArb)malloc (sizeof(TNod));
							strcpy(auxnod->info,b->valoare);
							auxnod->st=NULL;
							auxnod->dr=NULL;
							nodinalt->st=auxnod;
							//insereaza la st
						}
						else
						{
							auxnod = (TArb)malloc (sizeof(TNod));
							strcpy(auxnod->info,b->valoare);
							auxnod->st=NULL;
							auxnod->dr=NULL;
							nodinalt->dr=auxnod;
						}//insereaza la dr

					b=b->urm;
				}
			}
		}
		/* sf adaugare rest elemente */

		/* evaluare expresie*/
		auxrez->rezultat=Evaluare(auxrez->arbore);
		Reprez(auxrez->arbore,auxrez->reprez);
		/*sfarsit evaluare expresie*/

		if(!rez) rez=auxrez;   /* daca inceput de lista rez=auxrez*/
		else            /*altfel fa loopul in mod normal */
		{
			rez->urm=auxrez;
			rez=rez->urm;
		}

		a=a->urm;

	}
	if(!rez) return head;
	rez->urm=NULL;
	return head;
}
