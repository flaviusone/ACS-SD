/* am facut asta ca sa salvez functiile ce contineau printfuri in ele pt test */

void afi(void *a, size_t n,size_t d)
{
	int *p=(int *)a,i=0;
	for(;i<n;i++)
		printf("%i ",p[i]);
	printf("\n");
}
void Interclasare(void* sursa,void* dest,size_t m,size_t n,size_t d,TFComp f){
	void    *p=sursa, *q=sursa+m*d,
		*sf2=sursa+(n-1)*d,
		*sf1=sursa+(m-1)*d; //initializari inceputuri si sfarsituri
	printf("Sf2 = %i\n",*(int*)sf2);
	printf("inainte p %i q %i \n",*(int*)p,*(int*)q);
	if(f(sursa+(m-1)*d,sursa+m*d)<0){  //daca ultimu element din primu
		// grup< primu din al doilea
		printf("in primu if din interclasare %i %i \n",*(int*)(sursa+(m-1)*d),*(int*)(sursa+m*d));
		Copie(dest,sursa,n*d);          //copiaza primu grup apoi al doilea
		//Copie(dest+m*d,sursa+m*d,(n-m)*d);
	}
	else if(f(sursa+(n-1)*d,sursa)<0){  //daca ultimul element din al doilea
		//grup < primul din primul grup
		printf("in al doilea if din interclasare %i %i \n",*(int*)(sursa+(n-1)*d),*(int*)(sursa));
		Copie(dest,sursa+m*d,(n-m)*d);  //copiaza al doilea grup apoi primul
		Copie(dest+(n-m)    *d,sursa,m*d);
	}   //cele 2 cazuri extreme
	else{
		while(p<=sf1 && q<=sf2){  //cat timp diferit sau egal cu sfarsit verifica
			if(f(p,q)<0) {
				printf("in interclasare copiez pe %i peste %i \n",*(int*)p,*(int*)(dest));
				Copie(dest,p,d);
				dest+=d;
				p+=d;
			}
			else {
				printf("in interclasare copiez pe %i peste %i \n",*(int*)q,*(int*)(dest));
				Copie(dest,q,d);
				dest+=d;
				q+=d;
			}
		}
		printf("dupa p %i q %i \n",*(int*)p,*(int*)q);
		if(p>sf1) { //copiaza ce a mai ramas
			printf("p (%i) > sf1 (%i) copiez sf2+d-q/d (%i) elemente \n",*(int*)p,*(int*)sf1,(sf2+d-q)/d);
			Copie(dest,q,sf2+d-q); //sf2-q+d pt ca ar fi copiat 0 elemente (deoarece sf2 si sf1 pleaca de la n-1 si m-1
			else if(q>sf2) {
				printf("q (%i) > sf2 (%i) copiez sf1+d-p/d (%i) elemente \n",*(int*)q,*(int*)sf2,(sf1+d-p)/d);
				Copie(dest,p,sf1+d-p);
			}
		}
	}




	void MSort(void* sursa,void* dest,size_t n,size_t d,TFComp f){
		//printf("n = %i \n",n);
		printf("sursa: ");afi(sursa,n,d);
		printf("dest: ");afi(dest,n,d);
		if (n>2){
			int m = (n)/2;
			MSort(dest,sursa,m,d,f);
			//printf("sursa: ");afi(sursa,n,d);
			//printf("dest: ");afi(dest,n,d);
			MSort(dest+m*d,sursa+m*d,n-m,d,f);
			printf("sursa: ");afi(sursa,n,d);
			printf("dest: ");afi(dest,n,d);
			printf("intru in interclasare \n");
			Interclasare(sursa,dest,m,n,d,f);
			printf("sursa: ");afi(sursa,n,d);
			printf("dest: ");afi(dest,n,d);
		} else if ( n == 2 ){
			if(f(sursa,sursa+d)>0){
				printf("copiez pe %i peste %i \n",*(int*)(sursa+d),*(int*)dest);
				Copie(dest,sursa+d,d);
				printf("copiez pe %i peste %i \n",*(int*)sursa,*(int*)(dest+d));
				Copie(dest+d,sursa,d);
			}
		}
	}










	void MSortoriginal(void* sursa,void* dest,size_t n,size_t d,TFComp f){
		//printf("n = %i \n",n);
		printf("sursa: ");afi(sursa,n,d);
		printf("dest: ");afi(dest,n,d);
		if (n>2){
			int m = (n+1)/2;

			MSort(dest,sursa,m,d,f);
			//printf("sursa: ");afi(sursa,n,d);
			//printf("dest: ");afi(dest,n,d);
			MSort(dest+m*d,sursa+m*d,n-m,d,f);
			printf("intru in interclasare \n");
			Interclasare(sursa,dest,m,n,d,f);
			//printf("sursa: ");afi(sursa,n,d);
			//printf("dest: ");afi(dest,n,d);
		} else if ( n == 2 ){
			if(f(sursa,sursa+d)>0){
				printf("copiez pe %i peste %i \n",*(int*)(sursa+d),*(int*)dest);
				Copie(dest,sursa+d,d);
				printf("copiez pe %i peste %i \n",*(int*)sursa,*(int*)(dest+d));
				Copie(dest+d,sursa,d);
			}/*else if(f(sursa,sursa+d)<=0){printf("sursa %i <= sursa +d %i \n",*(int*)sursa,*(int*)(sursa+d));
			   printf("copiez pe %i peste %i \n",*(int*)dest,*(int*)sursa);
			   Copie(dest,sursa,d);
			   printf("copiez pe %i peste %i \n",*(int*)(sursa+d),*(int*)(dest+d));
			   Copie(dest+d,sursa+d,d);
			   }*/
		}/*else if( n == 1){
		   printf("copiez pe %i peste %i \n",*(int*)sursa,*(int*)(dest));
		   Copie(dest,sursa,d);
		   }*/
	}
	void MSort23(void* sursa,void* dest,size_t n,size_t d,TFComp f){
		//printf("n = %i \n",n);
		printf("MSORT  \n");
		print_vec(sursa, n);
		print_vec(dest, n );
		printf("%i \n", n);

		if (n>=2){
			int m = n/2;
			MSort(dest,sursa,m,d,f);
			MSort(dest+m*d,sursa+m*d,n-m,d,f);
			Interclasare(dest,sursa,m,n,d,f);
		}
	}
	void Interclasareorig(void* sursa,void* dest,size_t m,size_t n,size_t d,TFComp f){

		if(f(sursa+(m-1)*d,sursa+m*d)<0){  //daca ultimu element din primu
			// grup< primu din al doilea
			//printf("%i %i \n",*(int*)(sursa+(m-1)*d),*(int*)(sursa+m*d));
			Copie(dest,sursa,m*d);          //copiaza primu grup apoi al doilea
			Copie(dest+m*d,sursa+m*d,(n-m)*d);
		}
		else if(f(sursa+(n-1)*d,sursa)<0){  //daca ultimul element din al doilea
			//grup < primul din primul grup
			//printf("%i %i \n",*(int*)(sursa+(n-1)*d),*(int*)(sursa));
			Copie(dest,sursa+m*d,(n-m)*d);  //copiaza al doilea grup apoi primul
			Copie(dest+m*d,sursa,m*d);
		}   //cele 2 cazuri extreme
		else{
			void *p=sursa, *q=sursa+m*d, *sf2=sursa+n*d,*sf1=sursa+(m)*d; //initializari
			while(p<sf1 && q<sf2){  //cat timp diferit de sfarsit pt fiecare bucata
				if(f(p,q)<0) {
					Copie(dest,p,d);
					dest+=d;
					p+=d;
				}
				else {
					Copie(dest,q,d);
					dest+=d;
					q+=d;
				}
			}
			printf("p %i q %i \n",*(int*)p,*(int*)q);
			if(p>=sf1) Copie(dest,q,sf2-q); //copiaza ce a mai ramas
			else if(q>=sf2) Copie(dest,p,sf1-p);
		}
	}

