#include "boardUtils.h"

void print_board()
{
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j =0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

/*
* Functia calculeaza scorul pentru cuvantul primit ca parametru, fara a lua in considerare
* conditia de bonus, cu ajutorul unui vector de 26 de elemente. 
*/
int value_of_the_word(char *word)
{
	int value[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 
                    3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int score = 0, letter_value, i;
	int wl = (int)strlen(word); 

	for (i = 0; i < wl ; i++) {
		letter_value = value[word[i] - 'A'];
 		score += letter_value;
    }

    return score;	
}

/*
*Functia calculeaza base ^ exponent in mod recursiv
*/
int power(int base, int exponent)
{
    if (exponent == 0) {
        return 1;
    } else {
        return base * power(base, exponent - 1);
    }
}

/*
* Functia returneaza numarul cu care trebuie inmultit scorul initial dupa aplicarea conditiilor de bonus.
* Variabila se_aplica_bonus1 si se_aplica_bonus2 verifica conditiile de bonus.
* Variabilele numar_aparitii_1 si numar_aparitii_2 returneaza numarul de casute de 1 si de 2
* cu care se suprapune un cuvant in tabla de bonusuri si care indeplinesc conditia de bonus 
* pentru casutele de 1 sau 2.
*/
int bonus_score(int X, int Y, int D, char *word, char *string_for_bonus1, char *string_for_bonus2)
{
    int bonus = 1;
	int se_aplica_bonus1 = 0;
	int se_aplica_bonus2 = 0;
    int numar_aparitii_1 = 0, numar_aparitii_2 = 0;
    int wl = (int)strlen(word), l;

    if (strstr(word, string_for_bonus1) != NULL) {
		se_aplica_bonus1 = 1;
    }
    se_aplica_bonus2 = strcmp(string_for_bonus2, (word + strlen(word) - 2));
	
	for (l = 0; l < wl; l++) {
		if (D == 0) { 
			if (bonus_board[X][Y + l] == 1 && se_aplica_bonus1 == 1) {
				numar_aparitii_1++;
            }

			if (bonus_board[X][Y + l] == 2 && se_aplica_bonus2 == 0) {
				numar_aparitii_2++; 
            }
		}

		if (D == 1) { 
			if (bonus_board[X + l][Y] == 2 && se_aplica_bonus2 == 0) {
				numar_aparitii_2++; 
            }

			if (bonus_board[X + l][Y] == 1 && se_aplica_bonus1 == 1) {
				numar_aparitii_1++;
            }
		}
	}

	bonus *= (power(2, numar_aparitii_1)) * (power(3, numar_aparitii_2));

	return bonus;
}

/*
* Functi primeste ca parametrii un pointer la un string si coordonatele primei sale litere de pe tabla de joc.
* Returneaza 1 in cazul in care cuvantul merge scris pe orizontala fara a depasi dimensiunea tablei.
*/
int check_horizontal(char *word, int row, int col) 
{
    int wl = strlen(word);
    int k, tmp_col = col;

    if ((BOARD_SIZE - col) >= wl ) {
        for (k = 0; k < wl - 1; k++) {
            tmp_col++;

            if (board[row][tmp_col] != '.') {
                return 0;
            }
        }

    } else {
        return 0; 
    }   
    return 1;
}

/*
* Functia primeste ca parametrii un pointer la un string si coordonatele primei sale litere de pe tabla de joc.
* Returneaza 1 in cazul in care cuvantul merge scris pe verticala fara a depasi dimensiunea tablei. 
*/
int check_vertical(char *word, int row, int col) 
{
    int wl = strlen(word);
    int k, tmp_row = row;

    if ((BOARD_SIZE - row) >= wl ) {
        for (k = 0; k < wl - 1; k++) {
            tmp_row++;

            if (board[tmp_row][col] != '.') {
                return 0;
            }
        }

    } else {
         return 0; 
    }    
    return 1;
}

/*
* Functia check_already_played verifica daca un anumit index se afla intr-un vector.
* Se foloseste la task4, 5, 6, pentru a verifica daca un cuvant din vectorul words[][NUM_WORDS]
* a fost deja ales de jucator.
*/
int check_already_played(int *used_words_array, int word_index)
{   
    int j;
    for (j = 0; j < NUM_WORDS; j++) {
        if (used_words_array[j] == word_index) {
            return 1;
        }
    }
    return 0;
}

/* 
* Functia initializeaza tabla de joc cu ','
*/
void clear_board()
{
    int i, j; 

    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = '.';
        }
    }
}

/*
* Functia primeste ca parametrii coordonatele si un pointer la cuvantul introdus
* si il adauga pe tabla de joc.
*/
void put_word_on_board(int X, int Y, int D, char *word)
{
    int l;

	for (l = 0; l < (int)strlen(word); l++) {
	   if (D == 0) {
			board[X][Y+l] = word[l]; 
		}

		if (D == 1) {
            board[X+l][Y] = word[l]; 
		}
	}     
}

/*
* Functia primeste un pointer la un cuvant din vectorul words[] si verifica daca acesta
* poate fi pus pe tabla de joc, astfel incat prima litera se afla deja pe tabla,
* iar cuvantul se incadreaza in dimensiunile tablei.
*/
void get_next_word(char *word, int *x, int *y, int *dir)
{
    int row, col;

    for (row = 0; row < BOARD_SIZE; row++) {

        for (col = 0; col < BOARD_SIZE; col++) {

            if (board[row][col] == word[0]) { 

                if (check_horizontal(word, row, col) == 1) {
                    *dir = 0;
                    *x = row;
                    *y = col;

                } else if (check_vertical(word, row, col) == 1) {
                    *dir = 1;
                    *x = row;
                    *y = col;
                }
            }

            if (*dir > -1 && *x > -1 && *y > -1) {
                break;
            }
        }

        if (*dir > -1 && *x > -1 && *y > -1) {
            break;
        }
    }
}

/*
* Functia get_optimum_word - selecteaza cuvantul optim, cu scorul cel mai mare, care merge pus pe tabla.
* (din vectorul words[]). Pentru fiecare cuvant nefolosit din words, se cauta prima sa litera pe tabla de joc.
* Daca se gaseste, se verifica daca merge scris pe orizontala sau verticala, se obtin coordonatele sale si scorul 
* Daca scorul este maxim, acela este cuvantul cautat. Daca se obtine scorul maxim pentru mai multe pozitii,
* atunci optim_words memoreaza cele mai mici coordonate x si y.
*/
void get_optimum_word(int *used_words, int *optim_word, char *string_for_bonus1, char *string_for_bonus2) 
{
    int cur_max_score = 0, word_index;
    int x, y ,d, x_tmp, y_tmp, d_tmp, score_tmp, row, col, i;

    for (row = 0; row < BOARD_SIZE; row++) {
        for (col = 0; col < BOARD_SIZE; col++) {
            for (i = 0; i < NUM_WORDS; i++) {

                if (check_already_played(used_words, i) == 1) {
                    continue;
                }

                if (board[row][col] == *words[i]) {
                    d_tmp = -1; 
                    x_tmp = -1; 
                    y_tmp = -1;

                    if (check_horizontal(words[i], row, col) == 1) {
                        d_tmp = 0;
                        x_tmp = row;
                        y_tmp = col;
                    } 

                    if (check_vertical(words[i], row, col) == 1) {
                        d_tmp = 1;
                        x_tmp = row;
                        y_tmp = col;
                    }
                 
                    if (d_tmp > -1 && x_tmp > -1 && y_tmp > -1) {
                        score_tmp = value_of_the_word(words[i]) * bonus_score(x_tmp, y_tmp,
                                     d_tmp, words[i], string_for_bonus1, string_for_bonus2);

                        if (score_tmp > cur_max_score) {
                            cur_max_score = score_tmp;
                            d = d_tmp;
                            x = x_tmp;
                            y = y_tmp;
                            word_index = i;

                        } else if (score_tmp == cur_max_score) {
                           
                            if (x > x_tmp) {
                                cur_max_score = score_tmp;
                                d = d_tmp;
                                x = x_tmp;
                                y = y_tmp;
                                word_index = i;

                            } else if (y > y_tmp && x >= x_tmp) {
                                cur_max_score = score_tmp;
                                d = d_tmp;
                                x = x_tmp;
                                y = y_tmp;
                                word_index = i;
                            }
                        }
                    }
                }
            }
        }
    }
    optim_word[0] = x;
    optim_word[1] = y;
    optim_word[2] = d;
    optim_word[3] = word_index;
    optim_word[4] = cur_max_score;
}

/*
* Afiseaza scorul fiecarui jucator conform output-ului cerut.
*/
void print_score(int score_player1, int score_player2)
{
	printf("Player 1: %d Points\n", score_player1);
	printf("Player 2: %d Points\n", score_player2);
} 

/*
* Functia verifica daca intr-un sir se gaseste caracterul '/n' si il inlocuieste
* cu null terminator.
*/
void strip_newline(char word[MAX])
{
    char *pos;
	if ((pos = strchr(word, '\n')) != NULL) {
         *pos = '\0';
    }
}