/* Tirnacop Flavius 313CB */
#include "Tema2.h"

/* Fisierul de test contine expresie urmata de caracterele specificate
Exemplu: Exp1 (O, +, 0), (T, 1, 1),
dupa fiecare virgula exista cate un spatiu pentru a
face mai usoara citirea si prelucrarea cu scanf */

/* intoarce adresa unei liste de expresii citita din fisier */
LExpresii* CitireFis (char numefis[])
{
	LExpresii *a=NULL,*aux,*head=NULL;
	LElemente *a2=NULL,*aux2;
	FILE* f;
	char nume[20],c,s[20];
	int intaux;
	f=fopen(numefis,"rt");
	if(!f) return NULL;
	/* sfarsit initializari */

	while(fscanf(f,"%s",nume) == 1)
	{
		aux = (LExpresii*)malloc(sizeof(LExpresii));
		if(!aux) return NULL;
		if(!head) head=aux;
		strcpy(aux->nume_exp,nume);
		aux->elem=NULL;
		while(1) /* parcurge fiecare paranteza in parte si creeaza celule*/
		{
			aux2 = (LElemente*)malloc(sizeof(LElemente));
			if(!aux2)
			{
				//eliberare toata lista
				break;
			}
			fscanf(f,"%s",s);
			aux2->tip=s[1];        /*citeste primul element din paranteza*/
			if(aux2->tip=='T')      /*citeste al doilea element din paranteza*/
			{
				fscanf(f,"%i",&intaux);
				itoa(intaux,s,10);
				strcpy(aux2->valoare,s);
				fscanf(f,"%s",s); /*sari peste virgula de dupa int */
			}else
			{
				fscanf(f,"%s",s);
				s[1]='\0';
				strcpy(aux2->valoare,s);
			}
			fscanf(f,"%i",&aux2->indice);     /*citeste al treilea element din paranteza*/
			if(!a2)
			{
				a2=aux2;
				a2->urm=NULL;
			}
			else
			{
				a2->urm=aux2;
				a2=a2->urm;
				a2->urm=NULL;
			}
			if (!aux->elem) aux->elem = a2; /*seteaza inceputul listei*/
			fscanf(f,"%s",s);
			if(s[1]==';') break;
		}
		a2=NULL;
		/*initializare si citire elemente */
		if(!a) a=aux;   /* daca inceput de lista a=aux*/
		else            /*altfel fa loopul in mod normal */
		{
			a->urm=aux;
			a=a->urm;
		}

	}
	a->urm=NULL;
	fclose(f);
	return head;     /*return inceput lista */
}
