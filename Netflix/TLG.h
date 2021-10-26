#include "utils.h"
#include "Serial.h"

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

/* structura pentru liste simplu inlnatuite generice */
typedef struct celula {
	void *info;
	struct celula *urm;
} TCelula, *TLG;

/* functii de prelucrae a listelor */
int Inserare_TLG(TLG*, FILE*, int, TFCmp, TFCmp, FILE*);
int Cardinal_lista(TLG);
void Elimina_ultimul(TLG);
int Cauta_in_liste(TLG, TLG, TLG, TLG, char*, TFCmp2);
void Distruge_TLG(TLG*, TF_free);

#endif