/*-- testM-x.c --*/
#include "multimeV.h"
#include "funcM-aux.c"
#include "funcM-1.c"
//#include "funcM-aux.c"

typedef struct
{ int v1;
	double v2;
	char v3[21];
} Tx, *Ax;

#define VX(a,camp) (((Ax)a)->camp)

void inix(Ax x) /* initializare aleatoare element */
{ int i = random(8)+2;
	x->v3[i] = '\0';
	while (i-- > 0) x->v3[i] = 'a' + random(26);
	i = x->v1 = random(20)-10;   x->v2 = random(10000)/100.;
}

void afiTx(Tx* ax) /* afiseaza un element de tip Tx */
{ printf("%4i%7.2lf  %s\n", ax->v1, ax->v2, ax->v3);
}

void afiMx(TMultime*m) /* afiseaza continut multime de Tx */
{ Tx *p = (Tx*)(m->v);
	int i = 0, n = Card(m);
	printf("      v1     v2   v3\n");
	for(; i < n; i++)
		printf("[%2i]%4i%7.2lf  %s\n", i, p[i].v1, p[i].v2, p[i].v3);
}

int comp3(const void *a, const void *b)
{ int r = VX(b,v1) - VX(a,v1);
	{ int r = VX(b,v1) - VX(a,v1);
		double d;
		if(r) return r;                     /* difera campul v1 */
		d = VX(a,v2) - VX(b,v2);
		if(d != 0) return d < 0? -1 : 1;    /* difera campul v2 */
		return strcmp(VX(a,v3), VX(b,v3));  /* rezultat dictat de campul v3 */
	}

	int main()
	{ Tx v[20], vv[10], *r,
		x = {3, -9.35, "test"}, y = {-1,1,"y"}, z = {0,0,"a"};
		TMultime m1 = {sizeof(Tx),comp3,NULL,v,v+10,v+20}, *a = &m1,
			 m2, *b = &m2, m3, *c;
		int i, nr, nvv, nrr1;
		int rez;

		randomize();
		printf("--- Demo multimi generice ---\n");
		/* initializeaza 10 elemente din v cu valori aleatoare */
		for(i = 0; i < 10; i++) inix(v+i);
		for(nvv = 4,i = 0; i < nvv; i++) inix(vv+i);
		/* initializeaza b */
		InitS(b, vv,10,sizeof(Tx),comp3,NULL);
		Adauga(v+5,b);    /* o valoare preluata din a */
		Adauga(&y, b), Adauga(&z, b);

		/* S = secventa de prelucrari, folosind operatii generice: */
		/*   - afisare multime, - test apartenenta, - test localizare */
		printf("-- Multimea a --\n");
		afiMx(a);
		rez = Apartine(&x, a);
		printf("elementul (%i,%4.2lf,%s) %sapartine multimii\n\n",
				x.v1, x.v2, x.v3, rez? "" : "nu ");
		y = v[2];
		r = (Tx*)Loc(&y, a);
		if(!r)
			printf("elementul (%i,%4.2lf,%s) nu apartine multimii\n\n",
					y.v1, y.v2, y.v3);
		else
			printf("elementul (%i,%4.2lf,%s) are adresa %p si indice %i \n\n",
					y.v1, y.v2, y.v3, r, r-v);
		getch();

		/* - adaugare 2 noi elemente: unul care nu exista si altul care exista
		   - afisare multime */
		printf("\n-- Teste adaugari --\n\n");
		rez = Adauga(&x, a);
		if(rez) printf("(%i,%4.2lf,%s) %s\n",
				x.v1, x.v2, x.v3, rez? "adaugat" : "exista deja");
		rez = Adauga(&y, a);
		if(rez) printf("(%i,%4.2lf,%s)  %s\n\n",
				y.v1, y.v2, y.v3, rez? "adaugat" : "exista deja");
		afiMx(a);

		/* - eliminare 2 elemente: unul care exista si altul care nu exista
		   - afisare multime
		   */
		printf("\n-- Teste eliminari --\n\n");
		rez = Elimina(&y, a);
		printf("(%i,%4.2lf,%s) %s\n",
				y.v1, y.v2, y.v3, rez? "eliminat" : "nu exista");
		rez = Elimina(&z, a);
		printf("(%i,%4.2lf,%s) %s\n",
				z.v1, z.v2, z.v3, rez? "eliminat" : "nu exista");
		afiMx(a);

		getch();

		printf("\n-- Test reuniune --\n\n");
		c = InitD(50,sizeof(Tx),comp3,comp3);
		if(!c)
		{ printf("Initializate dinamica esuata\n");
			getch(); return 1;
		}
		printf("\na:\n"); afiMx(a);
		printf("\nb:\n"); afiMx(b);
		nrr1 = Reuniune(a,b,c);
		printf("\n-- rezultat Reuniune(a,b)--\n"); afiMx(c);

		getch();

		/* Sortare multime, urmata de afisare */


		/* Repetarea S folosind functii specifice multimii sortate */


		return 0;
	}
