#include "functii.h"

/*
* Functia compara key-urile a doua site-uri
* primite ca parametru.
*/
int ExistaKey(void *key1, void *key2)
{
    TSite *site1 = (TSite *)key1;
    TSite *site2 = (TSite *)key2;
    return strcmp(site1->name, site2->name);
}

/* 
* Functia face o inserare ordonata dupa key in lista 
* primita ca parametru. Se aloca o celula noua care urmeaza sa
* fie inserata. Se face inserarea in lista si se refac legaturile 
* in functie de pozitia primei celule cu numele mai mare decat cea 
* pe care vrem sa o inseram, pentru a face inserare inaintea ei.
*/
int Put_key(TLDI *first, void *key, TFCmp cmp)
{
    TLDI aux = (TLDI)malloc(sizeof(TCelula));
    if (aux == NULL) {
        return 0;
    }

    TLDI p = *first, q = *first;
    int insert_first = 0;

    if (*first == NULL) { 
        aux->info = key;
        aux->urm = aux;
        aux->pre = aux;
        *first = aux;
        return 1;
        
    } else {
        do {
            if (cmp(key, p->info) < 0) { 
                insert_first = 1;
                break;
            } else 
                p = p->urm;
        } while (p != *first);
        
        TLDI last = (*first)->pre;
        if (p == q) {
            last->urm = aux;
            aux->pre = last;
            (*first)->pre = aux;
            aux->urm = *first;
            aux->info = key;

            if (insert_first == 1) {
                *first = aux;
            }
        
        } else { 
            p->pre->urm = aux;
            aux->pre = p->pre;
            aux->urm = p;
            p->pre = aux;
            aux->info = key;
        }
    }
    return 1;
}

/*
* Functia cauta in tabela hash lista corespunztoare key-ului primit 
* ca parametruu. Daca lista exista, se localizeaza in cadrul listei
* celula care contine informatia respectiva. Daca informatia exista,
* se elimina celula din cadrul listei si se refac legaturile.
* Pentru toate cazurile, am eliberat memoria ocupata de informatia
* din celula si de campul eliminat din lista.
*/
int Remove_key(TH *hash_tabel, void *key, TFCmp cmp_key, TF Distr_info)
{
    int hash = hash_tabel->fh(key, hash_tabel->M);
    TLDI *first = hash_tabel->v + hash;
    TLDI aux = *first, q = *first;
    int find = 0;

    if (*first != NULL) {
        do {
            if (cmp_key(aux->info, key) == 0) {
                find = 1;
                break;
            } else {
                aux = aux->urm;
            }
        } while ((aux != *first));

        TLDI last = (*first)->pre;
        if (find == 0) {
            return 0; 

        } else if ((*first) == (*first)->urm) { 
            *first = NULL;
            last = NULL;

        } else if (aux == q) { 
            aux->pre->urm = last;
            last->urm = (*first)->urm;
            *first = aux->urm;
            (*first)->pre = last;

        } else if (aux == last) { 
            aux->pre->urm = *first;
            (*first)->pre = aux->pre;
            last = aux->pre;

        } else { 
            aux->pre->urm = aux->urm;
            aux->urm->pre = aux->pre;
        }
        Distr_info(aux->info);
        free(aux);
    }
    return 1;
}

/*
* Functia parcurge lista din tabela hash corespunzatoare codului
* generat de functia de hash si compara key-ul primit la input cu 
* cele din lista. Daca acesta exista in lista, functia afiseaza 
* in fisierul de output mesajul "True", altfel afiseaza "False".
*/
void Find_key(TH *hash_tabel, void *key, TFCmp cmp_key, FILE *out)
{
    int hash = hash_tabel->fh(key, hash_tabel->M);
    TLDI first = hash_tabel->v[hash];
    TLDI aux = first;
    int find = 0;

    if (first != NULL) {
        do {
            if (cmp_key(aux->info, key) == 0) {
                find = 1;
            } else {
                aux = aux->urm;
            }
        } while (aux != first && find == 0);
    }

    if (find == 0) {
        fprintf(out, "%s\n", "False");
    } else {
        fprintf(out, "%s\n", "True");
    }
}

/*
* Functia parcurge lista din tabela hash corespunzatoare codului
* generat de functia de hash si compara key-ul primit la input cu 
* cele din lista. Daca acesta exista in lista, functia afiseaza adresa IP
* corespunzatoare acestuia in fiserul de output, altfel afiseaza NULL
*/
void Get_key(TH *hash_tabel, void *key, FILE *out, TFCmp cmp_key)
{
    int hash = hash_tabel->fh(key, hash_tabel->M);
    TLDI first = hash_tabel->v[hash];
    TLDI el = first;
    int find = 0;

    if (first != NULL) {
        do {
            if (cmp_key(el->info, key) == 0) {
                Afi_site(el->info, out); 
                fprintf(out, "\n");
                find = 1;
                break;
            } else {
                el = el->urm;
            } 
        } while (el != first);
    }

    if (find == 0) {
        fprintf(out, "NULL\n");
    }
}

/*
* Functia afiseaza in fisierul de outpit
* valoarea IP-ului site-ului primit ca parametru.
*/
void Afi_site(void *key, FILE *out)
{
    TSite* site = (TSite *)key;
    fprintf(out, "%s", site->IP);
}

/*
* Functia parcurge lista care are codul index_bucket primit
* ca parametru si afiseaza in fisierul de output toate valorile
* adreselor IP ale site-urilor din lista. Daca lista nu exista,
* in fisier va aparea mesajul "VIDA".
*/
void Print_bucket(TH *hash_tabel, char *index_bucket, FILE *out)
{
    size_t hash = 0;
    sscanf(index_bucket, "%zu", &hash);
    if (hash >= hash_tabel->M) {
        return;
    }

    TLDI first = hash_tabel->v[hash];
    TLDI aux = first;

    if (first == NULL) {
        fprintf(out, "%s", "VIDA\n");
    } else {
        do {
            Afi_site(aux->info, out);
            fprintf(out, " ");
            aux = aux->urm;
        } while (aux != first);
        fprintf(out, "\n");
    }
}

/*
* Functia parcurge tabela hash si afiseaza pentru 
* fiecare lista existenta codul generat, urmat de 
* adresele IP ale site-urilor existente in lista.
*/
void Print(TH *hash_tabel, FILE *out)
{
    size_t i;

    for (i = 0; i < hash_tabel->M; i++) {
        TLDI first = hash_tabel->v[i];

        if (first != NULL) {
            fprintf(out, "%zu: ", i);
            char index_bucket[10];
            sprintf(index_bucket, "%zu", i);
            Print_bucket(hash_tabel, index_bucket, out);
        }
    }
}

/*
* Functia elibereaza memoria alocata pentru o variabila
* de tip TSite.
*/
void DistrInfo(void *ae)
{
    TSite *site = (TSite *)ae;
    free(site->IP);
    free(site->name);
    free(site);
}

/*
* Functia compara numele a doua site-uri
*/
int cmp_key(void *ae1, void *ae2)
{
    TSite *site1 = (TSite *)ae1;
    char *key2 = (char *)ae2;
    return strcmp(site1->name, key2);
}
