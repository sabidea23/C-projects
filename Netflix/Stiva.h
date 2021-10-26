#include "utils.h"
#include "TLG.h"
#include "_Stiva.h"

#ifndef _STIVA_
#define _STIVA_

/* Stiva implementata cu liste simplu inlantuite generice */
typedef struct {
    size_t dime;
    TLG vf;
} TStiva, *Ast;

/*- macrodefinitii - acces campuri */
#define VF(a) 	(((Ast)(a))->vf)

/*- teste -*/
#define DIMES(a) (((Ast)(a))->dime)
#define VIDAS(a) (((Ast)(a)) == NULL)

#endif