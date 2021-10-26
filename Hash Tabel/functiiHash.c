#include "functii.h"

/* 
* Functia initializeaza tabela hash, aloca un pointer la tabela
* si vectorul de liste de dimensiunea M primita ca parametru 
*/
TH* IniTH(size_t number_of_lists, TFHash fh) 
{
    TH* hash_tabel = (TH *)calloc(1, sizeof(TH));
    if (!hash_tabel) {
        return NULL;
    }

    hash_tabel->M = number_of_lists;
    hash_tabel->v = (TLDI *)calloc(number_of_lists, sizeof(TLDI));
    if (!hash_tabel->v) {
        free(hash_tabel);
        return NULL;
    }

    hash_tabel->fh = fh;
    return hash_tabel;
}

/*
* Functia parcurge tabela hash si pentru fiecare lista 
* elibereaza celulele si informatia alocata.
* In final se elibereaza vectorul de liste si pointerul la 
* tabela hash.
*/
void DistrTH(TH** ah, TF Distr_info)
{
    TLDI first, aux;
    size_t hash;

    for (hash = 0; hash < (*ah)->M; hash++) {
        if ((*ah)->v[hash] != NULL) {
            first = (*ah)->v[hash];
            TLDI el = first;
            do {
                aux = first;
                first = first->urm;
                Distr_info(aux->info);
                free(aux);
            } while (first != el);
        }
    }

    free((*ah)->v);
    free(*ah);
    (*ah) = NULL;
}

/* 
* Functia aloca o variabila de tip TSite in care este copiat continutul
* de tip <key, value> primit ca input, calculeaza hashul corespunzator
* pentru key si introduce site-ul in lista aferenta codului hash.
* Daca in tabela se gaseste deja un site cu acelasi key, acesta nu va
* mai fi introdus. Functia intoarce 1 in caz de reusita si 0 in caz de esec.
*/
int InsTH(TH *hash_tabel, void *key, void *value, TFCmp cmp_key)
{
    int hash = hash_tabel->fh(key, hash_tabel->M);
    TLDI first = hash_tabel->v[hash];

    if (first != NULL) {
        TLDI aux = first;
        do {
            if (cmp_key(aux->info, key) == 0) {
                return 0; 
            } else {
                aux = aux->urm;
            }
        } while (aux != first);
    }

    TSite *site = (TSite *)malloc(sizeof(TSite));
    if (!site) 
        return 0;

    site->name = (char *)malloc(strlen(key) + 1);
    if (!site->name) {
        free(site);
        return 0;
    }
    strcpy(site->name, key);

    site->IP = (char *)malloc(strlen(value) + 1);
    if (!site->IP) {
        free(site->name);
        free(site);
        return 0;
    }
    strcpy(site->IP, value);

    int rez = Put_key(hash_tabel->v + hash, (void *)site, ExistaKey);
    if (rez == 1) {
        return 1;
    }
    return 0; 
}

/* 
* Functia hash va calcula restul impartirii sumei caracterelor ce fac parte 
* din cheile stocate in hash la numarul maxim de bucketuri din hashtable.
*/
int codHash(void *key, size_t M)
{
	char *site = (char *)key;
	int suma = 0;
    size_t i;

    for (i = 0; i < strlen(site); i++) {
        suma += (int)site[i];
    }
	return suma % M;
}