
/*-- funcM-1.c --*/
#include "multimeV.h"

/*--- functii de initializare ---*/

TMultime *InitD(size_t n, size_t d, TFComp fid, TFComp ord)
	/* creeaza multime, alocand dinamic spatiu pentru descriptor
	   si n elemente de dimensiune d; intoarce adr.multime sau NULL */
{ TMultime *m = (TMultime*)calloc(1,sizeof(TMultime));
	if(!m) return NULL;                      /* alocare esuata */
	m->v = calloc(n, d);
	if(!m->v) { free(m); return NULL;}       /* alocare esuata */
	m->d = d;
	m->s = m->v, m->t = m->v + d * n;
	m->fid = fid, m->ord = ord;
	return m;                          /* initializare reusita */
}

void InitS(TMultime *m, void *v, size_t n, size_t d,
		TFComp fid, TFComp ord)
	/* initializeaza multimea m, cu maxim n elemente de dimensiune d,
	   memorate in vectorul v, deja alocat static sau dinamic */
{ m->d = d;
	m->s = m->v = v, m->t = v + d * n;
	m->fid = fid, m->ord = ord;
}

/*--- operatii asupra multimilor NESORTATE ---*/


int Inserare(void *nou, TMultime *m)
	/* obiectiv: adaugarea unui nou element la sfarsitul vectorului;
	   intoarce 1/0/-1 - succes/exista deja/nu exista spatiu */
{ void *x = m->s + m->d, *pozitie;           /* noul sfarsit, in caz de adaugare */
	int aux;
	// if(Apartine(nou, m)) return 0;   /* nou exista deja in m -> gata */
	if(PlinaM(m)) return -1;         /* multime plina */
	pozitie = CautBin(nou,m,&aux);
	if (aux == 1) return 0;                   //elementul este deja
	DeplDr(pozitie, m->s - pozitie , m->d);   //deplasare sa facem loc
	m->s += m->d;                             // schimbam finalul
	Copie(pozitie , nou , m->d);              //copiem noul element
	return 1;                        /* elementul a fost adaugat */
}

int Adauga(void *nou, TMultime *m)
	/* obiectiv: adaugarea unui nou element la sfarsitul vectorului;
	   intoarce 1/0/-1 - succes/exista deja/nu exista spatiu */
{ void *x = m->s + m->d;           /* noul sfarsit, in caz de adaugare */
	if(Apartine(nou, m)) return 0;   /* nou exista deja in m -> gata */
	if(PlinaM(m)) return -1;         /* multime plina */
	for(; m->s < x; (m->s)++, nou++) /* copiaza nou la sfarsit m */
		*(char*)(m->s) = *(char*)nou;
	return 1;                        /* elementul a fost adaugat */
}

void *CautBin(void *x, TMultime *m, int *r)
	/* cautare binara in vector sortat; daca elementul cautat exista,
	   atunci intoarce adresa si 1 (la adresa r),
	   altfel intoarce adresa primului succesor si 0 */
{
	void *inf = m->v , *sup = m->s ,*mij = NULL;
	while (inf <= sup){
		/*determinam mijloc */
		mij = inf + (sup - inf)/2;
		if (m->fid(mij,x)==0){ //indeplineste conditia
			*r=1;
			return mij;
		}
		if (m->ord(mij,x)>0)
			sup = mij - m->d;
		else
			inf = mij + m->d;
	}
	*r = 0;
	return mij; //esec
}

void* Loc(void *x, TMultime *m)/* intoarce adresa elementului cautat sau NULL */
{ void *p = m->v;
	for(; p < m->s; p += m->d)
		if(m->fid(p, x) == 0) return p;
	return NULL;
}

int Elimina(void *x, TMultime *m)
	/* intoarce 1/0 cu semnificatia eliminat / nu exista */
{
	TMultime *z,*y;
	if (!Loc(x,m)) return 0;
	for (z = Loc(x,m) , y = (m->s) - (m->d) ; z < (m->d) ; y++ , z++)
		*(char*)z=*(char*)y;
	m->s=(m->s) - (m->d);
	return 1;
}

int Identice(TMultime *m1, TMultime *m2)
{
	TMultime *p;
	if(Card(m1)!=Card(m2)) return 0;
	for(p=m1->v ; p< m1->s ; p+=m1->d){
		if (!Loc(p,m2)) return 0;
	}
	return 1;
}

int Reuniune(TMultime *m1, TMultime *m2, TMultime *r)
	/* Spatiul pentru reuniune alocat in prealabil, la adresa r;
	   intoarce cardinalul reuniunii */
	/* Preconditii: (m1->d == m2->d) && (m1->fid == m2->fid)*/
{
	int j;
	TMultime *x;

	if (!((m1->d == m2->d) && (m1->fid == m2->fid))) return -1;
	Copie(r->v, m1->v, (m1->s - m1->v));
	printf("dupa copie");
	r->s = r->v + (m1->s - m1->v);
	for (x=m2->v ; x < m2->s ; x =x + m2->d)
		if(!Apartine(x,m1)){ //puteam sa folosesc si loc chiar si mai sus
			Adauga(x,r);

		}

	return Card(r);

}

int Inclus(TMultime *m1, TMultime *m2){
	void *x ;//initializare
	if (Card(m1)>Card(m2)) return 0;
	for(x=m1->v ; x<m1->s ; x += m1->d)
		if(!Apartine(x,m2)) return 0;
	return 1;
}

int Diferenta(TMultime *m1, TMultime *m2, TMultime *r){
	//ce e in m1 si nu e in m2
	void *x;
	if (!((m1->d == m2->d) && (m1->fid == m2->fid))) return -1;
	for(x=m1->v ; x < m1->s ; x =x + m1->d){
		if(!Apartine(x,m2)){
			printf("apartine %i \n",Apartine(x,m2));
			Adauga(x,r);
		}
	}
	return 1;
} //defacut
int Intersectie(TMultime *m1, TMultime *m2, TMultime *r){
	void *x;
	if (!((m1->d == m2->d) && (m1->fid == m2->fid))) return -1;
	for(x=m1->v ; x < m1->s ; x =x + m1->d){
		if(Apartine(x,m2))
			Adauga(x,r);
	}

} //defacut

int Transforma(TMultime *a,TMultime *b){
	void *q,*p=a->v,*sf=a->v;
	while (p != a->s){
		if(Apartine(p,b)){
			if(p>sf){
				Copie(sf,p,a->d);
			}
			sf = sf + a->d;
		}
		p = p + a->d;
	}
	a->s = sf;
	return Card(a);

}

int Intersectie_Daniela(TMultime *a,TMultime *b){
	void *p=a->v,*q;
	int r,card = 0;

	while(p!=a->s){
		q=b->v;
		while (q != b->s){
			if(a->fid(p,q) == 0)
				card++;
			q += b->d;
		}
		p+=a->d;
	}
	return card;


}






/*-------------*/

