#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

#define MAX 30

typedef int (*TFCmp)(void*, void*); 
typedef void (*TF)(void*);     
typedef int (*TFHash)(void*, size_t); 

typedef struct celula2 {
  void *info;             
  struct celula2 *pre, *urm; 
} TCelula, *TLDI;

typedef struct {
  size_t M; 
  TFHash fh; 
  TLDI *v; 
} TH; 

typedef struct {
  char *name; 
  char *IP; 
} TSite;

TH* IniTH(size_t, TFHash);
void DistrTH(TH** ah, TF fe);
int InsTH(TH *, void *,void *, TFCmp);
int codHash(void *, size_t);

int Put_key(TLDI *, void *, TFCmp);
void Find_key(TH *, void *, TFCmp, FILE *);
void Get_key(TH *, void *, FILE *, TFCmp);
int Remove_key(TH *, void *, TFCmp, TF);
void Print_bucket(TH *, char *, FILE *);
void Print(TH *, FILE *);
void Afi_site(void *, FILE *);
int ExistaKey(void *, void *);
void DistrInfo(void *);
int cmp_key(void *, void *);