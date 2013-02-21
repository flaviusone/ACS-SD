#include "multimeV.h"
void Merge_sort(void* avector, size_t nr_elemente, size_t d, TFComp f)
{
	void *aux;

	aux = (void*)calloc(nr_elemente,d);
	Copie(aux,avector,nr_elemente*d); //initialzieaza vectorul aux cu elementele din avector
	MSort(aux,avector,nr_elemente,d,f);
	free(aux);

}

void MSort(void* sursa,void* dest,size_t n,size_t d,TFComp f)
{
	if (n>2)
	{
		int m = (n)/2;
		MSort(dest,sursa,m,d,f);
		MSort(dest+m*d,sursa+m*d,n-m,d,f);
		Interclasare(sursa,dest,m,n,d,f);
	}
	else if ( n == 2 )
	{
		if(f(sursa,sursa+d)>0) //daca ordine incorecta inverseaza elemente
		{
			Copie(dest,sursa+d,d);
			Copie(dest+d,sursa,d);
		}
	}
}

void Interclasare(void* sursa,void* dest,size_t m,size_t n,size_t d,TFComp f)
{
	void    *p=sursa, *q=sursa+m*d,
		*sf2=sursa+(n-1)*d,
		*sf1=sursa+(m-1)*d; //initializari inceputuri si sfarsituri
	if(f(sursa+(m-1)*d,sursa+m*d)<0)    //daca ultimu element din primu
		// grup< primu din al doilea
		Copie(dest,sursa,n*d);          //copiaza primu grup apoi al doilea

	else if(f(sursa+(n-1)*d,sursa)<0)   //daca ultimul element din al doilea
	{                                   //grup < primul din primul grup
		Copie(dest,sursa+m*d,(n-m)*d);  //copiaza al doilea grup apoi primul
		Copie(dest+(n-m)    *d,sursa,m*d);
	}   //cele 2 cazuri extreme
	else
	{
		while(p<=sf1 && q<=sf2)   //cat timp diferit sau egal cu sfarsit verifica
		{
			if(f(p,q)<0)
			{
				Copie(dest,p,d);
				dest+=d;
				p+=d;
			}
			else
			{
				Copie(dest,q,d);
				dest+=d;
				q+=d;
			}
		}
		if(p>sf1)   //copiaza ce a mai ramas
			Copie(dest,q,sf2+d-q); //sf2-q+d pt ca ar fi copiat 0 elemente (deoarece sf2 si sf1 pleaca de la n-1 si m-1
		else if(q>sf2)
			Copie(dest,p,sf1+d-p);

	}
}
