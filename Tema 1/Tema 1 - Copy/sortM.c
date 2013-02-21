#include "multimeV.h"
void Merge_sort(void* avector, size_t nr_elemente, size_t d, TFComp f){
	void *aux;
	aux = (void*)calloc(nr_elemente,d);
	MSort(avector,aux,avector,(avector+nr_elemente*d-d),d,f); //sursa , vector temporar, stanga, dreapta,d,f
	free(aux);

}
void afi(void *a, size_t n,size_t d)
{
	int *p=(int *)a,i=0;
	for(;i<n;i++)
		printf("%i ",p[i]);
	printf("\n");
}
void MSort(void* sursa,void* aux,void* stanga,void* dreapta,size_t d,TFComp f){
	if (dreapta > stanga){
		void* m;

		m = stanga + ((dreapta-stanga)/d/2)*d;  //impartim la d pt a face un nr intreg care imparti la 2
		//sa nu afecteze numarul de octeti impartiti in 2

		MSort(sursa,aux,stanga,m,d,f);
		MSort(sursa,aux,m+d,dreapta,d,f);
		Interclasare(sursa,aux,stanga,m+d,dreapta,d,f);
	}
}

void Interclasare(void* sursa,void* aux,void* stanga,void* m,void* dreapta,size_t d,TFComp f){
	void    *p=stanga,*q=m, //init pointeri de parcurgere
		*temp=aux, // ca sa nu depasim limita (in caz ca scriam in aux)
		*sfdreapta=dreapta,
		*sfstg=stanga+(m-stanga)-d; //primu elem din stanga mijlocului

	// num_elements poate


	while(p<=sfstg && q<=sfdreapta){  //cat timp diferit de sfarsit pt fiecare bucata
		if(f(p,q)<=0) {
			//printf("in interclasare copiez pe %i peste %i \n",*(int*)p,*(int*)(temp));
			Copie(temp,p,d);
			temp+=d;
			p+=d;
		}
		else {
			//printf("in interclasare copiez pe %i peste %i \n",*(int*)q,*(int*)(temp));
			Copie(temp,q,d);
			temp+=d;
			q+=d;
		}
	}
	if(p<=sfstg) {
		Copie(temp,p,sfstg-p+d); //copiaza ce a mai ramas
	}
	if(q<= sfdreapta) {
		Copie(temp,q,sfdreapta-q+d); // +d deoarece era cu 1 element in minus
	}
	//afi(aux,5,d);
	Copie(sursa + (stanga-sursa),aux, ((dreapta-stanga)+d));    //sursa ramane constanta si copiam la sursa + (stanga-sursa)
	//adica in continuarea ei
	//afi(sursa,5,d);
}


