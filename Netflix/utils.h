#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Serial.h"

#ifndef _UTIL_
#define _UTIL_

#define MAX_SERIES 2048
#define MAX_SEZONS 10
#define MIN_SEZONS 1
#define MAX_LENGTH_SERIAL 33
#define MAX_LENGTH_OPTION 20
#define MAX_TIME 120
#define MIN_TIME 1
#define MAX_RATING 10
#define MIN_RATING 1
#define MAX_EPISODES 20
#define MIN_EPISODES 1
#define MAX_POSITION_IN_TOP10 10
#define MIN_POSITION_IN_TOP10 1

typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void*, FILE *);     /* functie afisare/eliberare un element */
typedef int (*TFCmp2)(void*, char*);
typedef void (*TF_free)(void*);

/* functii */
int cmp_name(void*, void*);
int cmp_rating(void*, void*);
void afi_serial(void*, FILE*);
int is_integer(char*);
int compare_num(void*, char*);

#endif