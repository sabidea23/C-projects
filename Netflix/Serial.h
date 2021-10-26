#ifndef _SERIAL_NETFLIX_
#define _SERIAL_NETFLIX_

#include "Coada.h"
#include "Stiva.h"
#include "TLG.h"
#include "utils.h"

/* 
* Stuctura defineste un sezon al unui serial, contine numarul de episoade ale
* sezonului si coada de episoade, care este implementata cu liste si contine
* in campul informatie durata fiecarui episod. 
*/
typedef struct {
	int nr_episoade;
	AQ episoade; 
} TSezon;

/*
* Structura defineste un serial, care are un id, nume alocat dinamic, rating, 
* un numar de sezoane, durata totala a serialului(suma duratelor tuturor
* episoadelor), durata de timp vizionata deja din serial si coada de
* sezoane, implementata cu liste, care in fiecare celula contine un sezon.
*/
typedef struct {
	int id;
	char *nume; 
	float rating;
	int nr_sezoane;
	AQ sezoane;
	int total_minutes;
	int already_watched;
} TSerial;

/* functii prelucrare seriale */
void *Citeste_sezon(FILE*, int*);
void *Citeste_serial(FILE*, char*, float, int);
void Show(TLG, FILE*, int, TF);
void Show_top10(TLG, FILE*, TF);
int Add_top_10(TLG*, FILE*, FILE*, TF);
void Add_later(TLG*, AQ, TFCmp2, char*, int*, FILE*);
int Watching_serial(void*, FILE*, int, Ast);
void Watch_fromTLG(TLG*, Ast, Ast, TFCmp2, char*, FILE*, int);
void Continue_to_watch(Ast, Ast, char*, FILE*, TFCmp2, int);
void Watch_from_later(AQ, Ast, Ast, char*, FILE*, int, TFCmp2);
void* Create_new_sezon(int*, FILE*);
void Add_sez_for_serial(void *, FILE*, FILE*);
void Add_sez(TLG, char*, FILE*, FILE*, TFCmp2);
void Add_sez_in_later(AQ, char*, TFCmp2, FILE*, FILE*);
void Add_sez_in_watching(Ast, TFCmp2, char*, FILE*, FILE*);
void Distruge_sezon(void*);
void Distruge_serial(void*, TF_free);

#endif