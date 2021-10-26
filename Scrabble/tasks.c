#include "scrabble.h"

/*
* Functia initializeaza tabla de joc cu ',' si o afiseaza.
*/
void task0()
{
    clear_board();
    print_board(board);
}

/*
* Se citeste un numar, care reprezinta numarul de linii ce urmeaza sa fie citite.
* Pentru fiecare linie citita, variabila *input[4] memoreaza indicele pe verticala (input[0]),
* indicele pe orizontala (input[1]), directia (input[2]), si cuvantul introdus (input[3]).
* Se adauga pe tabla fiecare cuvant, iar la final se afiseaza tabla.
*/
void task1()
{   
    clear_board(); 

	char number_of_lines[MAX], user_line[MAX];
    char *input[4];
    int i;
    fgets(number_of_lines, MAX, stdin);
    
    for (i = 0; i < atoi(number_of_lines); i++) {
        fgets(user_line, MAX, stdin); 

        char *token = strtok(user_line, " ");
        int k = 0;

        while (token != NULL) { 
            input[k++] = token; 
            token = strtok(NULL, " "); 
        }

        strip_newline(input[3]);
        put_word_on_board(atoi(input[0]), atoi(input[1]), atoi(input[2]), input[3]);
    }

    print_board(board);
}

/*
* Functia citeste inputul la fel ca la task-ul precedent.
* Daca indexul liniei este par, joaca primul user, altfel, joaca al doilea user.
* Pentru fiecare cuvant se calculeaza scorul fara conditia de bonus.
*/
void task2()
{
    char number_of_lines[MAX], user_line[MAX];
    char *input[4];
    int score_player1 = 0, score_player2 = 0, i;

    fgets(number_of_lines, MAX, stdin);
    
    for (i = 0; i < atoi(number_of_lines); i++) {
        fgets(user_line, MAX, stdin); 

        char *token = strtok(user_line, " ");
        int k = 0; 	

        while (token != NULL) { 
            input[k++] = token; 
            token = strtok(NULL, " "); 
        }

        strip_newline(input[3]);
        
        if (i % 2 == 0) { 
		    score_player1 += value_of_the_word(input[3]);

        } else {
            score_player2 += value_of_the_word(input[3]);
        }
    }

    print_score(score_player1, score_player2);
}

/*
* Functia citeste 2 substringuri pentru conditia de bonus, apoi are acelasi input
* ca la task-urile precedente.
* Pentru fiecare cuvant este calculat scorul final prin inmultirea scorului fara bonus
* cu numarul  rezultat din indeplinirea conditiilor de bonus (vezi functia bonus_score).
*/
void task3()
{
    char number_of_lines[MAX], user_line[MAX], string_for_bonus1[MAX], string_for_bonus2[MAX];
    char *input[4];
    int score_player1 = 0, score_player2 = 0, i;

	fgets(string_for_bonus1, MAX, stdin);
	strip_newline(string_for_bonus1);

    fgets(string_for_bonus2, MAX, stdin);
    strip_newline(string_for_bonus2);

    fgets(number_of_lines, MAX, stdin);
    
    for (i = 0; i < atoi(number_of_lines); i++) {
        fgets(user_line, MAX, stdin); 

        char *token = strtok(user_line, " ");
        int k = 0; 

        while (token != NULL) { 
            input[k++] = token; 
            token = strtok(NULL, " "); 
        }
    
		strip_newline(input[3]);

        if (i % 2 == 0) { 
            score_player1 += value_of_the_word(input[3]) * bonus_score(atoi(input[0]), 
                            atoi(input[1]), atoi(input[2]), input[3], string_for_bonus1, string_for_bonus2);
        } else {
			 score_player2 += value_of_the_word(input[3]) * bonus_score(atoi(input[0]), 
                             atoi(input[1]), atoi(input[2]), input[3], string_for_bonus1, string_for_bonus2);
        }
    }

    print_score(score_player1, score_player2);
}

/*
* Pentru gasirea urmatorului cuvant pe care Player2 poate sa il joace se verifica pentru 
* fiecare cuvant din words[][NUM_WORDS] daca a fost deja folosit de unul dintre jucatori.
* Daca se gaseste un cuvant nefolosit, se incearca obtinerea coordonatelor sale 
* astfel incat sa se incadreze in dimensiuea tablei de joc, iar prima sa litera se afla deja pe tabla.
* Daca se obtin niste coordonate care au corespondent pe tabla de joc, se adauga pe tabla.
*/
void task4()
{
    char number_of_lines[MAX], user_line[MAX], string_for_bonus1[MAX], string_for_bonus2[MAX];
    char *input[4];
    int new_word_location[3] = {-1, -1, -1}, used_words[NUM_WORDS], i, j;  

    for (i = 0; i < NUM_WORDS; i++) {
        used_words[i] = -1;
    }
    
    fgets(string_for_bonus1, MAX, stdin);
	strip_newline(string_for_bonus1);

    fgets(string_for_bonus2, MAX, stdin);
    strip_newline(string_for_bonus2);

    fgets(number_of_lines, MAX, stdin);
    
    for (i = 0; i < atoi(number_of_lines); i++) {
        fgets(user_line, MAX, stdin);

        char *token = strtok(user_line, " ");
        int k = 0; 

        while (token != NULL) { 
            input[k++] = token; 
            token = strtok(NULL, " "); 
        }

		strip_newline(input[3]);

         for (j = 0; j < NUM_WORDS; j++) {
			if (strcmp(input[3], words[j]) == 0) {
				used_words[i] = j;
			}
		}

        put_word_on_board(atoi(input[0]), atoi(input[1]), atoi(input[2]), input[3]);
    }

    for (i = 0; i < NUM_WORDS; i++) {
        if (check_already_played(used_words, i) == 0) {
            get_next_word(words[i], &new_word_location[0], &new_word_location[1], &new_word_location[2]);

                if (new_word_location[0] > -1 && new_word_location[1] > -1 && new_word_location[2] > -1) {
                put_word_on_board(new_word_location[0], new_word_location[1], new_word_location[2], words[i]);
                break;
            }
        }
    }
}

/*
* Variabila optim_word va retine: rand, coloana, directie, index_cuvant din words[], scor.
* Se afiseaza cuvintele pe tabla si se calculeaza scorul pentru fiecare player.
* Se obtin coordonatele, scorul si indexul cuvantul optim din words care aduce scorul maxim pentru Player2.
* Daca acesta va produce un scor mai mare *sau* egal cu scorul Player-ului 1, se afiseza pe tabla.
*/
void task5()
{
    char numar_cuvinte_primite[MAX], user_line[MAX], string_for_bonus1[MAX], string_for_bonus2[MAX];
    char *input[4];
    int optim_word[5] = {-1, -1, -1, -1, -1}, score_player1 = 0, score_player2 = 0, i, j;
    int used_words[NUM_WORDS];
	
    for (i = 0; i < NUM_WORDS; i++) {
        used_words[i] = -1;
    }
    
	fgets(string_for_bonus1, MAX, stdin);
	strip_newline(string_for_bonus1);
	
    fgets(string_for_bonus2, MAX, stdin);
    strip_newline(string_for_bonus2);

    fgets(numar_cuvinte_primite, MAX, stdin);
    
    for (i = 0;  i < atoi(numar_cuvinte_primite); i++) {
        fgets(user_line, MAX, stdin); 

        char *token = strtok(user_line, " ");
        int k = 0; 	

        while (token != NULL ) { 
            input[k++] = token; 
            token = strtok(NULL, " "); 
        }

        strip_newline(input[3]);
        for (j = 0; j < NUM_WORDS; j++) {
			if (strcmp(input[3], words[j]) == 0) {
				used_words[i] = j; 
				break;
			}
		}

        put_word_on_board(atoi(input[0]), atoi(input[1]), atoi(input[2]), input[3]);
        if (i % 2 == 0) { 
            score_player1 += value_of_the_word(input[3]) * bonus_score(atoi(input[0]),
                             atoi(input[1]), atoi(input[2]), input[3], string_for_bonus1, string_for_bonus2);
        } else {
            score_player2 += value_of_the_word(input[3]) * bonus_score(atoi(input[0]), 
                            atoi(input[1]), atoi(input[2]), input[3], string_for_bonus1, string_for_bonus2);
        }
    }
  
    get_optimum_word(used_words, optim_word, string_for_bonus1, string_for_bonus2);
    if (optim_word[4] >= score_player1 - score_player2) {
        put_word_on_board(optim_word[0], optim_word[1], optim_word[2], words[optim_word[3]]);
        print_board(board);
    } else {
        printf("Fail!");
    }       
}

/*
* Se citeste ca input un cuvant pentru Player1, iar pentru Player2 se obtine cuvantul 
* optim prin apelul functiei get_optimum_word.
* Cuvintele se pun pe tabla, se calculeaza scorul pentru fiecare jucator. 
* (se repeta pana sunt citite toate cuvintele pentru Player1).
* La final, se afiseaza tabla, si in functie de scorul obtinut, se afiseaza care jucator a castigat. 
*/
void task6()
{
    char numar_cuvinte_primite[MAX], user_line[MAX], string_for_bonus1[MAX], string_for_bonus2[MAX];
    char *input[4];
    int optim_word[5] = {-1, -1, -1, -1, -1}, score_player1 = 0, score_player2 = 0, cur_used_index = 0;
    int used_words[NUM_WORDS], i, j;

    for (i = 0; i < NUM_WORDS; i++) {
        used_words[i] = -1;
    }

	fgets(string_for_bonus1, MAX, stdin);
	strip_newline(string_for_bonus1);

    fgets(string_for_bonus2, MAX, stdin);
    strip_newline(string_for_bonus2);

    fgets(numar_cuvinte_primite, MAX, stdin);
    
    for (i = 0; i < atoi(numar_cuvinte_primite); i++) {
        fgets(user_line, MAX, stdin);

        char *token = strtok(user_line, " ");
        int k = 0; 	
        
        while (token != NULL) { 
            input[k++] = token; 
            token = strtok(NULL, " "); 
        }

        strip_newline(input[3]);
        for (j = 0; j < NUM_WORDS; j++) {
			if (strcmp(input[3], words[j]) == 0) {
				used_words[cur_used_index++] = j;
				break;
			}
		}
        

        put_word_on_board(atoi(input[0]), atoi(input[1]), atoi(input[2]), input[3]);
        get_optimum_word(used_words, optim_word, string_for_bonus1, string_for_bonus2);
        put_word_on_board(optim_word[0], optim_word[1], optim_word[2], words[optim_word[3]]);

        score_player1 += value_of_the_word(input[3]) * bonus_score(atoi(input[0]), atoi(input[1]),
                         atoi(input[2]), input[3], string_for_bonus1, string_for_bonus2);
        score_player2 += value_of_the_word(words[optim_word[3]]) * bonus_score(optim_word[0], optim_word[1],
                         optim_word[2], words[optim_word[3]], string_for_bonus1, string_for_bonus2);
        used_words[cur_used_index++] = optim_word[3];
    }
    print_board(board);

    if (score_player1 > score_player2) { 
        printf("Player 1 Won!\n"); 
    } else if (score_player1 < score_player2) { 
        printf("Player 2 Won!\n"); 
    }
}
