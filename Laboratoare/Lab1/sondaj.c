/*-- sondaj.c --*/
#include "sondaj.h"


/* void AfiChestionar(TChestionar *aq) - afiseaza chestionarul sub forma
   01. Desert preferat
   [1.1] prajitura   [1.2] fructe  [1.3] inghetata
   . . . . .
   */
void AfiChestionar(TChestionar *aq)
{ int i, iv, L;
	char *p;
	for(i = 0; i < aq->ni; i++)
	{ printf("%02i. %s\n    ", i+1, aq->avi[i].intreb);
		L = aq->avi[i].lgr+1, p = aq->avi[i].avar;
		for(iv = 0; iv < aq->avi[i].nr; iv++, p += L)
			printf("[%i.%i] %s  ", i+1, iv+1, p);
		printf("\n");
	}
}



void AfiRezultateSondaj(TSondaj*as)
	/* afisare intr-un format la alegere, cat mai clar */
{
	int i,iv,L,contor,j;
	char *p;
	TChestionar *aq=as->q;
	TPers *avp=as->avp;
	for (i = 0 ; i < as->q->ni ; i++){
		printf("%02i. %s\n    ", i+1, as->q->avi[i].intreb);
		L = aq->avi[i].lgr+1, p = aq->avi[i].avar;
		for(iv = 0; iv < aq->avi[i].nr; iv++, p += L){
			printf("\t [%i.%i] %-*s raspunsuri: ", i+1, iv+1,aq->avi->lgr+1 ,p);
			//si aici trebuie parcurse raspunsurile
			contor=0;
			for( j=0 ; j<as->nep ; j++){
				if(avp[j].arasp[i] - '0' == iv+1){
					contor++;
				}
			}
			printf("%i \n",contor);

		}
		printf("\n");
	}

}



/* Functia de afisare a repartitiei pe varste pentru nivelul de
   educatie niv, astfel:
   ne persoane cu nivel de educatie niv; medie categorie varsta = y.yy
   y.yy adica toate varstele adunate/nr persoane (cu nivel de educatei niv)
   Repartitie pe categorii de varsta
   __2______3______4______5______6__
   xx.xx  xx.xx  xx.xx  xx.xx  xx.xx
   unde y.yy = media de varsta (suma categ.varsta/nr.pers cu nivel de educatie E,
   xx.xx = procentul de persoane dintr-o categorie de varsta
   cat % din totalul oamenilor au media de varsta
   */
void AfiV_E(TSondaj* as, char niv)
{
	float contor=0,ne=0;
	TPers *j,*avp=as->avp;
	int aux[10] = {0},i,contor2=0, sumv = 0;
	for (i=0 ; i<9 ; i++)
		printf("___%i___",i+1);
	printf("\n");
	for (i=0 ; i<9 ; i++){
		for(j=avp ; j<avp + as->nep ; j++){
			if(j->info[3]==niv){
				ne = ne + (j->info[2] - '0') ;
				contor2++;
			}
			if(j->info[2] - '0'== i){
				contor++;}
		}
		printf("%5.2f%% ",contor*100/as->nep);
		contor=0;
	}
	printf("\n\n");
	printf("medie categorie de varsta = %5.2f \n\n",ne/contor2);
}
void AfiV_E_clasa(TSondaj* as, char niv) {
	int aux[10] = {0},i,ne=0, sumv = 0;
	TPers *p=NULL, *sf=as->avp+as->nep;
	for(p=as->avp;p != sf ; p++){
		if(p->info[3] == niv){
			aux[p->info[2] - '0']++;
			ne++;
			sumv+=p->info[2] - '0' ;
		}
	}
	printf("%i persoane au nivelul de educatie %c\n",ne,niv);
	if(!ne) return;
	printf("Medie categorie varsta %4.2lf \n",(double)sumv/ne);
	for (i=0 ; i<9 ; i++)
		printf("___%i___",i+1);
	printf("\n");
	for (i=2;i<7;i++){
		printf("%7.2f",aux[i]*100./ ne);
	}
	putchar("\n");
}


/* CmpP, utilizabila de catre qsort pentru a sorta un vector de participanti dupa:
   categ.varsta v  , ocupatie ^, sex ^  */
int CmpP(const void *a, const void *b)
{ TPers *p1 = (TPers *)a, *p2 = (TPers *)b;
	int r = p2->info[2] - p1->info[2];
	if(r) return r;
	r = p1->info[1] - p2->info[1];
	if(r) return r;
	return p1->info[0] - p2->info[0];
}




/* Functie ce primeste adresa sondaj sortat ca mai sus, cod categorie de
   varsta (v) si indice intrebare (i), analizeaza numai raspunsurile persoanelor
   din categoria de varsta v (atentie la ordinea de sortare), la intrebarea i si
   furnizeaza ca rezultate indicii (>= 1) variantelor de raspuns
   "cel mai putin frecvent" si "cel mai frecvent".    */
char F_I(TSondaj*as, char v, int i, char* r2)
{ int nrv[10] = {0}, imin, imax, ip;
	/* parcurs pana incep aia cu v
	   cat timp sunt daia cu V
	   a[indice] = indice
	   calculam minimu si maximu
	   returneaza r2(min) si return celalalat(max)
	   */  int j=0,frecvent,putinfrec;
	while(as->avp[j].info[2]!=v){ //merge pana la v
		//ceva de genu
		//if (as->avp[j].info[2] == v + '1') iesire (also test pt sfarsit)
		j++;
	}
	while(as->avp[j].info[2]==v){ //cat timp v

		nrv[as->avp[j].arasp[i] - '0']++; //incrementam campu coresp optiunii
		j++;
	}
	frecvent=-1;putinfrec=10;
	for ( j=0 ; j<10 ; j++){
		if(frecvent<nrv[j])
			frecvent=j;
		if(putinfrec>nrv[j] && nrv[j]!=0)
			putinfrec=j;
	}
	*r2 = '0' + putinfrec;
	return '0' + frecvent;

}


char F_P(TSondaj*as, char v, int i, char* r2)
{ TPers* p = as->avp, *s = p + as->nep;
	int nrv[10] = {0}, *qmin, *qmax, *q, *sq = nrv+as->q->avi[i].nr;


}
int main ()
{ TSondaj* as;
	TChestionar* aq;
	int r,indice;
	char categ;

	/*-- citire si afisare chestionar --*/
	aq = CitChestionar(&r);
	if(r < 0) { printf("Eroare %i\n", r); getch(); return 1;}
	printf("\t%i intrebari\n\n", aq->ni);
	AfiChestionar(aq);

	/*-- alocare si completare sondaj --*/
	as = AlocS(10, aq);
	if(!as) { printf("er.aloc sondaj"); getch(); return 3;}
	r = FisPers(as);
	printf("--- %i persoane ---\n\n", as->nep);

	/*-- prelucrari sondaj --*/
	//AfiRezultateSondaj(as);
	AfiV_E_clasa(as,'D');

	/*
	   Secventa cel mai frecvent/putin frec

	   qsort(as->avp,as->nep,sizeof(TPers),CmpP);
	   printf("Introduceti categoria de varsta:");
	   fflush(stdin);
	   categ = getchar();
	   printf("introduceti indicele intrebarii: ");
	   scanf("%i",&indice);
	   char putinfrec,frecvent=F_I(as,categ,indice,&putinfrec);
	   printf("Cel mai frecvent: %c \n",frecvent);
	   printf("Cel mai putin frecvent: %c \n",putinfrec);
	   */
	return 0;
}

