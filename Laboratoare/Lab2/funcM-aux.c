/*-- funcM-aux.c --*/
#include "multimeV.h"

/*--- functii auxiliare ---*/

void *DeplDr(void *a, size_t dim, size_t d)
	/* deplaseaza cu d octeti la dreapta un pachet de dim octeti */
{ void *sursa = a + dim, *dest = sursa + d;
	while(sursa > a) *(char*)(--dest) = *(char*)(--sursa);
	return dest;
}

void DeplSt(void *a, size_t dim, size_t d)
	/* deplaseaza cu d octeti la stanga un pachet de dim octeti */
{ char* sursa = (char*)a, *dest = sursa - d, *sf = sursa + dim;
	while(sursa < sf) *(dest++) = *(sursa++);
}

void Copie(void *dest, void *sursa , size_t n)
	/* copiaza la destinatie n octeti de la sursa */
{ void *sf = sursa + n;
	for(; sursa < sf; sursa++, dest++) *(char*)dest = *(char*)sursa;
}

void Invers(void *a, void *b, size_t n)
	/* inversearza n octeti intre a si b */
{ void *sf = a + n;
	char temp;
	for(; a < sf; a++, b++)
	{ temp = *(char*)a; *(char*)a = *(char*)b; *(char*)b = temp; }
}
/*-------------*/

