#include "TLG.h"

/*
* Functia insereaza un serial intr-o lista primita ca parametru.
* Se aloca spatiu pentru noua celula si se apeleaza o functie pentru
* citirea serialului ce reprezinta informatia din celula. 
* Pentru inserare in lista, daca doua seriale au acelasi rating, se cauta
* primul serial cu numele mai mare decat cel de inserat, pentru a insera
* inaintea lui. Altfel, se cauta primul serial cu ratingul mai mic decat 
* cel de inserat si se face inserarea inaintea lui. Se face inserarea in 
* lista si se afiseaza la output un mesaj corespunzator.
*/
int Inserare_TLG(TLG *lista, FILE *in, int id, TFCmp cmp_rating,
				TFCmp cmp_name, FILE *out)
{
    TLG aux, ant = NULL, p = *lista;
    char nume[MAX_LENGTH_SERIAL];
    float rating = 0;
    int pozitie = 1;

    fscanf(in, "%s", nume);
    fscanf(in, "%f", &rating);

    aux = (TLG)malloc(sizeof(TCelula));
    if (!aux)
        return 0;

    aux->info = Citeste_serial(in, nume, rating, id);
	if (!aux->info) {
		free(aux);
		return 0;
	}

    for (; p != NULL; ant = p, p = p->urm, pozitie++) {
        if (cmp_rating(p->info, aux->info) == 0) { 
			if (cmp_name(p->info, aux->info) > 0) {
				break;
			}
        } else if (cmp_rating(p->info, aux->info) == 1) {
            break;
		}
    }

    if (ant == NULL) {
        aux->urm = *lista;
        *lista = aux;
		pozitie = 1;
    } else { 
		aux->urm = p;
		ant->urm = aux;			
	}
    
	fprintf(out, "Serialul %s a fost adaugat la pozitia %d.\n",
			nume, pozitie);
	return 1;
}

/*
* Functia returneaza numarul celulelor din lista
* primita ca parametru.
*/
int Cardinal_lista(TLG lista)
{
	int nr_elemente = 0;;
	
	while (lista != NULL) {
		lista = lista->urm;
		nr_elemente++;
	}
	return nr_elemente;
}

/*
* Functia elimina ultimul element dintr-o lista
* primita ca parametru. Aceasta parcurge lista 
* pana la ultima celula nevida, care este 
* dezalocata.
*/
void Elimina_ultimul(TLG lista)
{
	TLG p = lista, ant = NULL, aux;
	
	for (; p->urm != NULL; ant = p, p = p->urm); 
	aux = p;
	p = ant->urm = NULL;
	//free(aux->info);
	free(aux); 
}

/*
* Functia cauta serialul cu numele primit ca parametru in
* toate listele disponibile. Se returneaza id-ul listei in care 
* a fost gasit, iar pentru lista top10 se returneaza 4. 
*/
int Cauta_in_liste(TLG tendinte, TLG documentare, TLG tutoriale_C,
					TLG top10, char *nume, TFCmp2 cmp_name)
{
	while (tendinte != NULL) {
		if (cmp_name(tendinte->info, nume) == 0) {
			return 1;
		}
		tendinte = tendinte->urm;
	}

	while (documentare != NULL) {
		if (cmp_name(documentare->info, nume) == 0) {
			return 2;
		}
		documentare = documentare->urm;
	}

	while (tutoriale_C != NULL) {
		if (cmp_name(tutoriale_C->info, nume) == 0) {
			return 3;
		}
		tutoriale_C = tutoriale_C->urm;
	}

	while (top10 != NULL) {
		if (cmp_name(top10->info, nume) == 0) {
			return 4;
		}
		top10 = top10->urm;
	}
	return 0;
}

/*
* Functia distruge o lista simplu inlantuita
* celula cu celula, eliberand si informatia din
* fiecare celula.
*/
void Distruge_TLG(TLG *lista, TF_free distruge_info)
{
	TLG p;
	while (*lista != NULL) {
		p = *lista;
		(*lista) = (*lista)->urm;
		distruge_info(p->info);
		free(p);
	}

	(*lista) = NULL;
}