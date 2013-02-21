/*-- funcMO-1.c --*/
#include "multimeV.h"

void *LocO(void *x,TMultime *m)
	/* cautare secventiala, cu oprire la elem cautat sau la succesor
	   sau la sfarsit; intoarce adresa elementului gasit sau NULL */
{
	void *p=NULL;
	int r;
	for( p = m -> v ; p<m->s ; p+=m->d) //parcurgerea
	{

		r = m -> ord (p ,x );

		if ( r < 0 ) continue;
		if (r > 0) return NULL;
		if (m -> fid(p,x) == 0 ) return p;
	}
	return NULL;
}


int IdenticeO(TMultime *m1, TMultime *m2)
{
	TMultime *x,*y;
	if(Card(m1)!=Card(m2)) return 0;
	for(x = m1->v , y = m2->v ; x < m1->s ; x+= m1->d, y+=m2->d){
		if(m1->fid(x,y)!=0) return 0;
		// if( *(char*)x != *(char*)y ) return 0;
	}
	return 1;
}


int EliminaO(void *x, TMultime *m)
	/* intoarce 1/0 cu semnificatia eliminat / nu exista */
{
	TMultime *z,*y;
	if (!Loc(x,m)) return 0;
	DeplSt(Loc(x,m)+ (m->d),(m->s)-Loc(x,m),m->d);
	m->s=(m->s) - (m->d);
	return 1;
}

int ReuniuneO(TMultime *m1, TMultime *m2, TMultime *r){
	void *p=m1->v,*q=m2->v,*ru=r->v; //initializare
	int ro;
	if (!((m1->d == m2->d) && (m1->fid == m2->fid))) return -1;//preconditie
	while(p!=m1->s  && q!=m2->s){
		ro = m1->ord(p,q);
		if (ro<0) {
			Copie(ru,p,m1->d); //copiaza p in r
			ru += r->d;      //avans r si p
			p += m1->d;
		} else if (ro>0) {
			Copie(ru,q,m2->d); //copiaza q in r
			ru += r->d;
			q += m2->d;
		} else {                //daca similare
			Copie(ru,p,m1->d);
			ru += r->d;
			if (m1->fid(p,q) == 0)
				q+= m2->d;
			p+= m1->d;


		}
	}
	if(p!=m1->s){ //mai sunt elemente in m1 da nu in m2
		Copie(ru,p,(m1->s)-p);
		ru += (m1->s) - p;
	}
	if(q!=m2->s){ //mai sunt elemente in m1 da nu in m2
		Copie(ru,q,(m2->s)-2);
		ru += (m2->s) - q;
	}
	r->s = ru;
	return 1;
}
int IncludeO(TMultime *m1, TMultime *m2){
	void *p=m1->v,*q=m2->v;
	int ro,contor=0;
	//initializare
	if(Card(m2)>Card(m1)) return 0;
	while(p!=m1->s  && q!=m2->s){
		ro = m1->ord(p,q);
		if (ro<0) {
			p += m1->d;
			if (m1->ord(p,q)>0) return 0;
		} else if (ro>0) {
			q += m2->d;
			if (m1->ord(p,q)<0) return 0;
		} else {                //daca similare
			p += m1->d;
			q += m2->d;
			contor++;
		}
	}
	return contor;


}
int DiferentaO(TMultime *m1, TMultime *m2, TMultime *r)
{   //MA DEPASESTE
	void *p=m1->v,*q=m2->v,*ru=r->v;
	int ro,contor=0;
	//initializare

	while(p!=m1->s  && q!=m2->s){
		ro = m1->ord(p,q);
		if (ro<0) {
			Copie(ru,p,m1->d);
			ru += r->d;
			p += m1->d;
			contor++;
		} else if (ro>0) {
			Copie(ru,q,m2->d);
			ru += r->d;
			q += m2->d;
			contor++;

		} else {
			p += m1->d;
			q += m2->d;

		}
	}
	r->s=ru;
	return contor;
}
int IntersectieO(TMultime *m1, TMultime *m2, TMultime *r){//DONE

	void *p=m1->v,*q=m2->v,*ru=r->v;
	int ro,contor=0;
	//initializare

	while(p!=m1->s  && q!=m2->s){
		ro = m1->ord(p,q);
		if (ro<0) {
			p += m1->d;

		} else if (ro>0) {
			q += m2->d;

		} else {
			Copie(ru,q,m2->d);                  //daca similare
			p += m1->d;
			q += m2->d;
			ru += r->d;
			contor++;
		}
	}
	r->s=ru;
	return contor;


}





