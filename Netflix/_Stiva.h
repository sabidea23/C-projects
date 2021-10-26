#ifndef _FUNCTII_S
#define _FUNCTII_S

#include "utils.h"
#include "Stiva.h"

/* functii de prelucrare a stivelor */
int VidaS(void*);
size_t DimES(void*);
void* InitS(size_t);
int Push(void*, void*);
int Pop(void*, void*);
int Rastoarna(void*, void*);
void Show_stiva(Ast, char*, FILE*);
int Cauta_in_stiva(Ast, TFCmp2, char*);
void ResetS(void*, TF_free);
void DistrS(Ast*, TF_free);

#endif