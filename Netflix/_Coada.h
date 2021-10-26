#ifndef _FUNCTII_C
#define _FUNCTII_C

#include "utils.h"
#include "Coada.h"

/* functii de prelucrare a cozilor */
void* InitQ(size_t);
size_t DimEQ(void*);
int IntrQ(void*, void*);
int ExtrQ(void*, void*);
int ConcatQ(void*, void*);
int VidaQ(void*);
void Show_coada(AQ, TF, FILE*);
int Cauta_in_coada(AQ, TFCmp2, char*);
void ResetQ(void*, TF_free);
void DistrQ(AQ*, TF_free);

#endif