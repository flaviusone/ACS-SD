/* Tirnacop Flavius 313CB */
#include "Tema2.h"

/*elimina un element din lista de noduri*/
/*intoarce adresa elementului dinaintea celui eliminat*/
/*functie auxiliara */
LElemente* Elimina(LElemente **a,LElemente *b)
{
	LElemente *pcur,*pant; /*pointer curent si anterior*/
	pant=NULL; /*nu are anterior*/
	if(!b) return NULL;
	for (pcur=*a ; pcur!=NULL ; pant = pcur , pcur = pcur->urm)
	{
		if (pcur==b)
		{
			if(pant==NULL) /*daca e la inceput de lista*/
			{
				*a=pcur->urm;
				free(pcur);
				return *a;
			}

			else
				pant->urm = pcur->urm; /*eliminare*/
			free(pcur);
			return pant;
		}
	}
}
/*returneaza lungimea unei liste de noduri (functie aux)*/
int LungimeLista(LElemente *a)
{
	LElemente *b;
	int n=0;
	b = a;
	while(b)
	{
		n++;
		b=b->urm;
	}
	return n;
}
LExpresii* Corectare(LExpresii* a)
{
	/* functia parcurge lista de elemente si o corecteaza dupa
algoritmul: 1 indice 0 poate exista doar odata
2 daca nu exista indice 0 atunci arbore vid
3 elimin indicii care nu apar fix de 2 ori
4 elimin indicii inexistenti:
- sortare lista
- elimin orice mai mare ca indicele stabilit
*/
	LExpresii* head;
	LElemente *b,*aux,*c;
	int contor,n=0,contor2,i,j,target,indicemax;
	char stringaux[100],x;
	head = a;
	while(a)
	{

		/*----pas 1----*/
		b = a->elem;
		contor=0;
		while(b)
		{
			if(b->indice==0)
				if(contor == 1)/*daca am 0 elimina orice alt 0*/
				{
					b=Elimina(&a->elem,b);
				}
				else contor++;  /*am gasit un zero*/
			b=b->urm;
		}
		/*----sf pas 1----*/

		/*----pas 2----*/
		if (contor==0) /*daca nu sunt indici 0(nu e radacina)*/
		{
			b = a->elem;
			while(b)
			{
				aux=b;
				b=b->urm;
				free(aux);
			}
			a->elem=NULL;
		}
		/*----sf pas 2----*/

		/*----pas 3----*/
		/*pas 3 a eliminam elementele care apar de mai mult de 2 ori */
		n = LungimeLista(a->elem);
		for( i = 1 ; i<=n ; i++)
		{

			b = a->elem;
			for(j = 1 ; j<i ; j++) b = b->urm;/*merg pana la elementul i*/
			//printf("pozitionat pe (%c %i) \n",b->tip,b->indice);
			target = b->indice;
			b=b->urm;
			contor2=0;
			while(b) /*verific daca exista mai mult de 2 aparitii*/
			{
				if(b->indice == target)
				{
					//printf("%i ",contor2);
					if(contor2==1) /*daca 3 elemente cu acc indice elimina tot*/
					{
						b = a->elem;
						while(b)
						{
							aux=b;
							b=b->urm;
							free(aux);
						}
						a->elem=NULL;
						break;

					}
					else contor2++;
				}
				b=b->urm;
			}
			if(!a->elem) break;
		}

		/* pas 3 b - eliminarea indicilor care apar doar odata
		   in momentul de fata avem maxim 2 indici de acelasi fel si maxim un 0 */
		for ( i = 1 ; i <= n ; i++)
		{
			b=a->elem;
			contor2=0;
			aux=NULL;
			while(b)
			{
				if(b->indice == i)
				{
					if (contor2==0)/*prima data cand gasesc elementu*/
					{
						aux=b;
						contor2++;
					}
					else
					{
						contor2++;
						break; /*totul e ok */
					}
				}
				b=b->urm;
			}
			if (contor2==1)
			{
				b = a->elem;
				while(b)
				{
					aux=b;
					b=b->urm;
					free(aux);
				}
				a->elem=NULL;
				break;
			}
		}
		/*----sfarsit pas 3 ----*/
		/*sortarea listei si pregatirea pt eleiminari*/
		b=a->elem;
		while(b)
		{
			c=b->urm;
			while(c)
			{
				if(c->indice<b->indice)
				{//swap
					strcpy(stringaux,b->valoare);
					strcpy(b->valoare,c->valoare);
					strcpy(c->valoare,stringaux);
					i=b->indice;
					b->indice=c->indice;
					c->indice=i;
					x=b->tip;
					b->tip=c->tip;
					c->tip=x;
				}
				c=c->urm;
			}
			b=b->urm;
		}
		/* sfarsit sortare lista*/

		/*eliminari*/
		i=1;
		if(!a->elem) b=NULL;
		else b=a->elem->urm;
		while(b)
		{
			if(b->indice>i)
			{
				b = a->elem;
				while(b)
				{
					aux=b;
					b=b->urm;
					free(aux);
				}
				a->elem=NULL;
				break;
			}
			i++;
			b=b->urm;
		}
		printf("\n");
		if(a->elem != NULL && a->elem->urm==NULL)
		{
			a->elem=NULL;
		}
		a=a->urm;
	}
	return head;
}

