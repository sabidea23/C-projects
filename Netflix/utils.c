#include "utils.h"

/*
* Functia compara numele a doua seriale.
*/
int cmp_name(void *a1, void *a2)
{
    TSerial *s1 = (TSerial *)a1;
    TSerial *s2 = (TSerial *)a2;

    return strcmp(s1->nume, s2->nume);
}

/*
* Finctia compara ratingurile a doua seriale, returneaza 0
* daca sunt egale, -1 daca primul e mai mare, 1 altfel.
*/ 
int cmp_rating(void *a1, void *a2)
{
    TSerial *s1 = (TSerial *)a1;
    TSerial *s2 = (TSerial *)a2;

	if (s1->rating == s2->rating) {
		return 0;
	} else if (s1->rating < s2->rating) {
		return 1;
	}
	return -1;
}

/* 
* Functia afiseaza numele si ratingul serialului
* primit ca parametru in fisierul de output.
*/
void afi_serial(void *info, FILE *out)
{
	TSerial *serial = (TSerial *)info;
	fprintf(out, "(%s, %1.1f)", serial->nume, serial->rating);
}

/*
* Functia returneaza 1 daca primul caracter din sirul
* primit ca parametru este cifra, 0 altfel.
*/
int is_integer(char *input)
{
    if (isdigit(input[0]) != 0)
		return 1;
    return 0;
}

/*
* Compara numele unui serial cu cel primit ca parametru.
*/
int compare_num(void *info, char *nume)
{
	TSerial *serial = (TSerial *)info;
	return strcmp(serial->nume, nume);
}