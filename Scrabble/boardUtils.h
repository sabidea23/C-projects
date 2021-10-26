#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utilStructure.h"

#ifndef _PRINT_BOARD_HEADER
#define _PRINT_BOARD_HEADER

void print_board();
int value_of_the_word(char *);
int power(int , int );
int bonus_score(int , int , int , char *, char *, char *);
int check_horizontal(char *, int , int);
int check_vertical(char *, int , int );
int check_already_played(int *, int );
void clear_board();
void put_word_on_board(int , int , int , char *);
void get_next_word(char *, int *, int *, int *);
void get_optimum_word(int *, int *, char *, char *);
void print_score(int , int );
void strip_newline(char* );

#endif