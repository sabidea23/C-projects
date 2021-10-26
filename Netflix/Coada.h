#include "utils.h"
#include "TLG.h"
#include "_Coada.h"

#ifndef _COADA_
#define _COADA_

/* Coada implementata cu liste simplu inlantuite generice */
typedef struct {
	size_t dime;
	TLG ic, sc;
} TCoada, *AQ;

/*- macrodefinitii - acces campuri */
#define IC(a) 	(((AQ)(a))->ic)
#define SC(a) 	(((AQ)(a))->sc)

/*- teste -*/
#define DIMEQ(a) (((AQ)(a))->dime)
#define VIDAQ(a) ((((AQ)(a))->ic == NULL) && (((AQ)(a))->sc == NULL))

#endif