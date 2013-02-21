/*-- fsondaj2.c --*/
#include "sondaj.h"

int CitIntreb(TIntreb*ai, FILE*f)
	/*  preia din fisier info referitoare la intrebarea cu adresa ai */
{
	char temp[121];
	char* adr[10] = {
		temp  }
	, *p, *pp;  /* adr[i] = adresa varianta i */
	int r, nrv, i, lg;

	ai->lgr = 0;
	/* citeste text intrebare si numar variante */
	while(fgetc(f) != '\n');      /* avans la linia urmatoare */
	for(p = temp; (*p = fgetc(f)) != ';' ; p++); /* citeste pana la ; */
	*p = '\0';                    /* inlocuieste ';' cu terminator */
	ai->intreb = strdup(temp);    /* creeaza copie intrebare */
	if(!(ai->intreb)) return -1;
	fscanf(f, "%i", &(ai->nr));   /* citeste numar variante raspuns */
	/* preia variante raspuns, inlocuind ';' cu terminator si determina lg.max */
	while(fgetc(f) != '\n');      /* avans la linia urmatoare */
	for(p = temp, i = 0; i < ai->nr; i++)
	{
		for(adr[i] = p;; p++)       /* citeste pana la ';' */
		{
			*p = fgetc(f);
			if(*p == ';') break;
		}
		*p = '\0';                  /* inlocuieste ';' cu terminator */
		lg = (p++ - adr[i]);
		if(lg > ai->lgr) ai->lgr = lg; /* actualizeaza lgm daca este cazul */
	}
	/* aloca spatiu pentru memorare variante raspuns in zone consecutive egale */
	ai->avar = calloc(ai->nr, (ai->lgr+1));
	if(!(ai->avar)) {
		free(ai->intreb);
		return -2;
	}
	/* copiaza variante raspuns in zona alocata dinamic */
	for(p = ai->avar, i = 0; i < ai->nr; i++, p += ai->lgr+1)
		strcpy(p, adr[i]);
	return 1;
}
/* TChestionar* CitChestionar(int*rez) - deschide fisier text, preia nr intrebari,
   aloca spatiu pt chestionar si il completeaza cu informatiile despre intrebari,
   presupuse corecte si memorate in fisier ca in exemplul urmator:
   Sportul preferat:9
   gimnastica;fotbal;atletism;rugbi;inot;tenis;handbal;baschet;altul;
Rezultate: adresa chestionar / NULL, cod rezultat (cod eroare < 0 / succes = 0)
*/
TChestionar* CitChestionar(int*rez)
{
	TChestionar* aq;
	FILE*f;
	int ni,i;
	char numefis[20];
	printf("Fisier de citit intrebari: ");
	scanf("%s",numefis);
	f = fopen(numefis,"rt");
	fscanf(f,"%i",&ni);
	aq = AlocCh(ni);
	if(!aq){
		*rez=-1;
		return NULL;
	}
	for (i=0; i<ni ;i++){
		CitIntreb(aq->avi + i,f);}
	*rez=1;
	return aq;
}


int FisPers(TSondaj* as)
	/* deschide pentru citire un fisier text din care preia info si raspunsuri pentru
	   un grup de persoane (format: info;raspunsuri , de exemplu MA2B;2134612)
	   Prelucrarea se incheie in doua situatii:
	   - nu mai exista spatiu in vectorul de persoane
	   - esueaza alocarea de spatiu pentru memorarea raspunsurilor unei persoane
	   - se ajunge la sfarsitul fisierului
	   Rezultatul intors de functie = numar persoane adaugate la sondaj
	   */
{
	FILE*f;
	char temp[125];               /* zona de lucru */
	int r, np, ni = as->q->ni;//nr intrebri
	TPers *p = as->avp + as->nep, *sfp = as->avp + as->nmp, *pp = p;

	printf("\nNume fisier persoane: ");
	fflush(stdin);
	r = scanf("%s", temp);
	if(r < 1 || !*temp) return 0;
	f = fopen(temp, "rt");
	if(!f) return 0;
	for(; p < sfp; p++)
	{
		p->arasp = calloc(1,ni);    /* aloca spatiu pentru raspunsuri */
		if(!(p->arasp)) break;
		r = fscanf(f, "%s", temp);  /* citeste informatii specifice si raspunsuri */
		if(r != 1) break;
		strncpy(p->info, temp, 4);     /* copiaza cele 4 caractere info */
		strncpy(p->arasp, temp+5, ni); /* copiaza raspunsuri */
	}
	np = p - pp;    /* np - numar persoane adaugate */
	as->nep += np;  /* actualizeaza numar efectiv persoane */
	fclose(f);
	return np;
}

int DialogPers(TSondaj* as, int ip)
	/* Actualizeaza, in regim de DIALOG, informatiile despre persoana ip (>=0):
	   - aloca spatiu pentru raspunsuri; in caz de esec intoarce 0;
	   - preia info specifice: gen (M/F), ocupatie(A-H), varsta, nivel educatie(A-G)
	   - pentru fiecare intrebare
	   - afiseaza text si variante de raspuns
	   - preia raspuns (daca nu este unul valid se codifica cu '0')
	   Rezultat = numar persoane adaugate la sondaj
	   */
{
	static char *codOcup[8] = {
		"muncitor","liber profesionist","invatamant",
		"domeniu bancar","functionar","agricultor",
		"sanatate","artist"  }
	,
		*nivEduc[7] = {
			"fara","elementar","gimnaziu","liceu",
			"licenta","master","doctorat"  };


}


