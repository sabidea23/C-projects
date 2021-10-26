#include "Coada.h"

/* test coada vida */
int VidaQ(void *coada)         
{ 
	return VIDAQ(coada); 
}

/* returneaza dimensiunea elementelor din coada */
size_t DimEQ(void *coada)      
{ 
	return DIMEQ(coada); 
}

/* 
* Functia aloca un pointer de tip AQ, pentru o coada vida.
*/
void* InitQ(size_t dime)
{
	AQ coada;
	coada = (AQ)malloc(sizeof(TCoada));
	if (!coada)
		return NULL;

	coada->dime = dime;
	coada->ic = coada->sc = NULL;
	return (void*)coada;
}

/*
* Functia aloca o noua celula de lista in care este pusa
* informatia primita ca parametru. Atunci cand coada este vida,
* se insereaza noua celula ca fiind prima din coada, altfel se
* insereaza la sfarsitul cozii.
*/
int IntrQ(void *coada, void *info)
{
    TLG aux = (TLG)malloc(DimEQ(coada));
    if (!aux) {
        return -1;
    }

	aux->info = info;
	aux->urm = NULL;
    if (IC(coada) == NULL && SC(coada) == NULL) {
        IC(coada) = SC(coada) = aux;
		return 1;
    }

    SC(coada)->urm = aux;
    SC(coada) = aux;
    return 1;
}

/* 
* Daca strucura este nevida, se extrage 
* din coada informatia din prima celula, dupa principiul FIFO.  Daca 
* dupa extragere, inceputul cozii se afla pe NULL, adica a fost doar
* un element in coada, se seteaza si sfarsitul cozii pe NULL.
* Se elibereaza informatia si celula de lista din care s-a
* facut extragerea.
*/
int ExtrQ(void *coada, void *info)
{
	if (VidaQ(coada))
		return 0;

	TLG aux = IC(coada);
	memcpy(info, aux->info, DimEQ(coada));
	IC(coada) = IC(coada)->urm;
	//free(aux->info);
	//free(aux); 

	if (IC(coada) == NULL) {
		SC(coada)  = NULL;
	}
	return 1;
}

/* 
* Functia concateneaza coada sursa la coada destinatie, 
* intoarce 1 daca a reusit sa concateneze elemente, altfel 0.
* Daca coada sursa este vida, nu sunt elemente de concatenat si
* se returneaza 0. Daca coada destinatie este vida, inceputul
* si sfarsitul cozii sursa devin inceputul si sfarsitul cozii destinatie.
* Altfel, se concateneaza sfarsitul cozii destinatie la inceputul cozii sursa,
* iar sfarsitul cozii destinatie se muta pe sfarsitul cozii sursa.
* In final, se seteaza coada sursa vida.
*/
int ConcatQ(void *coada_sursa, void *coada_destinatie)
{
	if (VidaQ(coada_sursa)) {
		return 0;
	}

	if (VidaQ(coada_destinatie)) {
		IC(coada_destinatie) = IC(coada_sursa);
		SC(coada_destinatie) = SC(coada_sursa);
		IC(coada_sursa) = NULL;
		SC(coada_sursa) = NULL;
		return 1;
	}

	SC(coada_destinatie)->urm = IC(coada_sursa);
	SC(coada_destinatie) = SC(coada_sursa);
	IC(coada_sursa) = NULL;
	SC(coada_sursa) = NULL;
	return 1;
}

/* 
* Se parcurge coada later implementata cu liste generice simplu
* inlantuite si se prelucreaza informatia din fiecare celula
* cu ajutorul functiei primita ca parametru.
*/
void Show_coada(AQ later, TF afisare_serial, FILE *out)
{
	fprintf(out, "Categoria later: [");

	TLG lista = IC(later);
	for (; lista != NULL; lista = lista->urm) {
		afisare_serial(lista->info, out);
		if (lista->urm != NULL)	{
			fprintf(out, ", ");
		}
	}
	fprintf(out, "].\n");
}

/*
* Functia cauta in coada later serialul care are numele primit ca parametru
* Se extrag pe rand elementele din coada si se compara cu ajutorul functiei
* compara_nume, apoi se introduc intr-o coada auxiliara, iar in final se reface 
* coada initiala prin concatenare. Functia intoarce 1 daca a gasit numele
* serialului in coada. altfel 0,
*/
int Cauta_in_coada(AQ later, TFCmp2 compara_nume, char *name)
{
	void *info = malloc(DimEQ(later));
	if (!info) {
		return -1;
	}

	AQ coada_aux = (AQ)malloc(DimEQ(later));
	if (!coada_aux) {
		free(info);
		return -1;
	}

	int found = 0;
	while (!VidaQ(later)) {
		ExtrQ(later, info);
		if (compara_nume(info, name) == 0) {
			found = 1;
		}
		IntrQ(coada_aux, info);
		info = malloc(DimEQ(later));
		if (!info) {
			ConcatQ(coada_aux, later);
			return -1;
		}
	}

	ConcatQ(coada_aux, later);
	if (found == 0) 
		return 0; 

	//DistrQ(coada_aux, Distruge_serial);
	return 1; 
}

/*
* Functia elibereaza celulele de lista ale unei cozi.
*/
void ResetQ(void *coada, TF_free distruge_info)
{
	TLG aux = IC(coada), p;
	while (aux != NULL) {
		p = aux;
		aux = aux->urm;
		distruge_info(p->info);
		free(p);
	}

	IC(coada) = SC(coada) = NULL;
}

/*
* Functia elibereaza memoria alocata pentru o coada,
*/
void DistrQ(AQ *coada, TF_free distruge_info)
{
	ResetQ(*coada, distruge_info);
	free(*coada);
	coada = NULL;
}