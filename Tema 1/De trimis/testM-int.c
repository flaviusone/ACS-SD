/*-- testM-int.c --*/
/* Tema 1 - Merge Sort Recursiv */
/* Tirnacop Flavius-Costin 313CB */

#include "multimeV.h"
#include "funcM-1.c"
#include "funcM-aux.c"
#include "sortM.c"

typedef struct
{
	int v1;
	double v2;
	char v3[21];
} Tx, *Ax;
#define VX(a,camp) (((Ax)a)->camp)

/* afiseaza continut multime de Tx */
void afiMx(TMultime*m)
{
	Tx *p = (Tx*)(m->v);
	int i = 0, n = Card(m);
	printf("      v1     v2   v3\n");
	for(; i < n; i++)
		printf("[%2i]%4i%7.2lf  %s\n", i, p[i].v1, p[i].v2, p[i].v3);
}

/* Functie de comparare pt elementele Tx */
int comp3(const void *a, const void *b)
{
	int r = VX(b,v1) - VX(a,v1);
	double d;
	if(r) return r;                     /* difera campul v1 */
	d = VX(a,v2) - VX(b,v2);
	if(d != 0) return d < 0? -1 : 1;    /* difera campul v2 */
	return strcmp(VX(a,v3), VX(b,v3));  /* rezultat dictat de campul v3 */
}

/*-- functie de afisare multime de intregi --*/
void afi1(TMultime *m)
{
	int *x = (int*)(m->v), n = Card(m), i = 0;
	printf("[");
	for( ; i < n; i++) printf(" %i,", x[i]);
	printf("\b ]\n\n");
}

/*-- functie de afisare multime de double --*/
void afi2(TMultime *m)
{
	double *x = (double*)(m->v);
	int n = Card(m), i = 0;
	printf("[");
	for( ; i < n; i++) printf(" %5.2lf,", x[i]);
	printf("\b ]\n\n");
}
/*-- functie de comparare intregi --*/
int compI(const void *a, const void *b) /*-- functie de comparare --*/
{
	return *(int*)a - *(int*)b;
}

/*-- functie de comparare double --*/
int compD(const void *a, const void *b)
{
	double d;
	d = *(double*)a - *(double*)b;
	if (d==0) return d;
	if(d<0) return -1;
	else return 1;

}


int main(int argc, char *argv[])
{

	FILE *f;
	int n,i,tip;
	char numefis[20];
	if  (strcmp(argv[2],"I")==0)
	{
		////initializari
		int v[200];
		f = fopen(argv[1],"rt");
		if(!f) return 0;
		fscanf(f,"%i",&n);
		for (i=0; i<n; i++)
		{
			fscanf(f,"%i",&v[i]);
		}
		fclose(f);
		TMultime m = {sizeof(int),compI,NULL,v,v+n,v+200},
			 *x = &m;
		afi1(x);
		Merge_sort(x->v,Card(x),sizeof(int),compI);
		//qsort(x->v,Card(x),sizeof(int),compI);
		//sort
		afi1(x);
		return 0;

	}
	if  (strcmp(argv[2],"D")==0)
	{
		double v[210];
		f = fopen(argv[1],"rt");
		if(!f) return 0;
		fscanf(f,"%i",&n);
		for (i=0; i<n; i++)
		{
			fscanf(f,"%lf",&v[i]);
		}
		fclose(f);
		TMultime m = {sizeof(double),compI,NULL,v,v+n,v+200},
			 *x = &m;////aici o sa fol alta functie pt comp
		afi2(x);
		Merge_sort(x->v,Card(x),sizeof(double),compD);
		afi2(x);
		return 0;

	}

	if  (strcmp(argv[2],"TX")==0)
	{
		Tx v[200];
		f = fopen(argv[1],"rt");
		if(!f) return 0;
		fscanf(f,"%i",&n);
		for (i=0; i<n; i++)
		{

			fscanf(f,"%i%lf%s",&v[i].v1,&v[i].v2,v[i].v3);
		}
		fclose(f);
		TMultime m = {sizeof(Tx),comp3,NULL,v,v+n,v+200},
			 *x=&m ;
		afiMx(x);
		Merge_sort(x->v,Card(x),sizeof(Tx),comp3);
		afiMx(x);
		return 0;
	}
	printf("Date de itnrare gresite");

	return 0;
}


