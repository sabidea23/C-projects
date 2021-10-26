#include "Stiva.h"

/* test stiva vida */
int VidaS(void *stiva)               
{ 
	return VIDAS(stiva);
}

/* returneaza dimensiunea elementelor din stiva */
size_t DimES(void *stiva)           
{ 
	return DIMES(stiva); 
}

/*
* Functia aloca o structua de tip stiva si se seteaza campul 
* dime cu dimensiunea data ca parametru, iar varful stivei este
* pe NULL, deoarece intial stiva este vida.
*/
void* InitS(size_t dime)
{
	Ast stiva;
	stiva = (Ast)malloc(sizeof(TStiva));
	if (!stiva)
		return NULL;

	stiva->dime = dime;
	stiva->vf = NULL;
	return (void*)stiva;
}

/*
* Functia introduce in stiva primita ca parametru o
* noua celula de lista in care pune informatia primita 
* ca parametru, iar inserarea se face in varful stivei.
*/
int Push(void* stiva, void* info)
{
	TLG aux;
	aux = (TLG)malloc(sizeof(TCelula));
	if (!aux) 
		return 0;

	aux->info = info; 
	aux->urm = VF(stiva);
	VF(stiva) = aux;
	return 1;
}

/*
* Functia extrage informatia din celula de lista 
* reprezentata de varful stivei primita ca parametru.
*/
int Pop(void *stiva, void *info)
{
	if (VF(stiva) == NULL)
		return 0;

	TLG aux = VF(stiva); 
	VF(stiva) = VF(stiva)->urm;
	memcpy(info, aux->info, DimES(stiva));
	//free(aux->info);
	//free(aux);
	return 1;
}

/*
* Functia rastoarna elementele din stiva sursa in stiva
* destinatie, intoarce 1 daca a reusit, sau 0 in cazul in
* care nu a mutat niciun element. Se parcurge coada sursa cu 
* ajutorul listelor, fiecare element al cozii sursa este pus 
* pe rand in varful cozii destinatie, avansul in coada sursa 
* facandu-se cu o lista auxiliara care retine mereu urmatorul element.
*/
int Rastoarna(void *stiva_sursa, void *stiva_destinatie)
{
	if (VF(stiva_sursa) == NULL)
		return 0;
	
	TLG lista = VF(stiva_sursa), aux;
	while (lista != NULL) {
		aux = lista->urm;
		lista->urm = VF(stiva_destinatie);
		VF(stiva_destinatie) = lista;
		lista = aux;
	}

	VF(stiva_sursa) = NULL;
	return 1;
}

/* 
* Functia afiseaza stiva primita, care este implementata
* cu ajutorul listelor simplu inlantuite generice. Se parcurge
* stiva si se prelucreaza fiecare informatie din celulele de lista.
*/
void Show_stiva(Ast stiva, char *nume, FILE *out)
{
	fprintf(out, "Categoria %s: [", nume);

	TLG p = VF(stiva);
	for (; p != NULL; p = p->urm) {
		afi_serial(p->info, out);
		if (p->urm != NULL)	{
			fprintf(out, ", ");
		}
	}
	
	fprintf(out, "].\n");
}

/*
* Functia verifica daca in stiva primita ca parametru se afla
* serialul cu numele name. Se extrage din stiva, dupa principiul
* LIFO, fiecare element, se compara cu numele cautat, apoi se
* introduce intr-o stiva auxiliara. Se reface stiva initiala prin 
* rasturnarea celei auxiliare .Functia intoarce 1 daca a fost gasit
* serialul, altfel 0.
*/
int Cauta_in_stiva(Ast stiva, TFCmp2 cmp_name, char *name)
{
	if (VF(stiva) == NULL) {
		return 0;
	}

	Ast	stiva_aux = InitS(DimES(stiva));
	if (!stiva)
		return -1;

	void *info = malloc(DimES(stiva));
	if (!info) {
		free(stiva_aux);;
		return -1;
	}
	int found = 0;

	while(VF(stiva) != NULL) {
		Pop(stiva, info);
		Push(stiva_aux, info);
		
		if (cmp_name(info, name) == 0) {
			found = 1;
		} 
		info = malloc(DimES(stiva)); 
		if (!info) {
			Rastoarna(stiva_aux, stiva);
			return -1;
		}
	}

	Rastoarna(stiva_aux, stiva);
	if (found == 0) { 
		return 0;
	}
	return 1; 
	//DistrS(stiva_aux, Distruge_serial)
}

/*
* Functia elibereaza celule de lista ale unei stive.
*/
void ResetS(void *stiva, TF_free distruge_info)
{
	TLG aux = VF(stiva), p;
	while (aux != NULL) {
		p = aux;
		aux = aux->urm;
		distruge_info(p->info);
		free(p);
	}

	VF(stiva) = NULL;
}

/*
* Functia elibereaza memoria alocata pentru o stiva.
*/
void DistrS(Ast *stiva, TF_free distruge_info)
{
	ResetS(*stiva, distruge_info);
	free(*stiva);
	stiva = NULL;
}