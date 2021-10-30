#include "utils.h"

void* (* Abilities[4])(void* x) = {RotateMatrix,
								 DecodeString, InvertArray, KillPlayer};

char *fromEnumtoString(PlayerRoles playerRole)
{
	char *str = calloc(MAX_LEN_STR_ATR, sizeof(char));
	switch(playerRole)
	{
		case Rotator:
			str = strcpy(str, "Rotator");
			break;
		case Decoder:
			str = strcpy(str, "Decoder");
			break;
		case Invertor:
			str = strcpy(str, "Invertor");
			break;
		case Impostor:
			str = strcpy(str, "Impostor");
			break;
	}
	return str;
}

/*
* Functia intoarce matricea la 90 de grade.
*/
void reverse_mat(int **mat, int size_of_matrix)
{ 
    int i, j, aux, k;

    for (i = 1; i <= size_of_matrix; i++) {
        for (j = 1, k = size_of_matrix; j < k; j++, k--) {
            aux = mat[j][i];
            mat[j][i] = mat[k][i];
            mat[k][i] = aux;
        }
    }
} 
  
/*
* Functia returneaza matricea trasnpusa, primita ca parametru.
*/
void transpose_matrix(int **mat, int size_of_matrix)
{
    int i, j, aux;

    for (i = 1; i <= size_of_matrix; i++) {
        for (j = i + 1; j <= size_of_matrix; j++) {
            aux = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = aux;
        }
    }
}

/*
* Functia concateneaza doua numere intregi, pentru a obtine elementele
* matricei de forma ij, folosind 2 siruri si returneaza elementul de tip intreg.
*/
int concat_ints(int index_of_line, int index_of_col) 
{ 
    char str1[20]; 
    char str2[20]; 

    sprintf(str1, "%d", index_of_line); 
    sprintf(str2, "%d", index_of_col); 
    strcat(str1, str2); 
    return atoi(str1); 
} 

/*
* Task 1.
* Functia aloca dinamic o matrice de tip char si verifica alocarea.
* Se formeaza matricea cu elemente  de forma ij cu i, j indicii
* elementului curent (i și j pornesc de la 1) si se obtine matricea 
* rotita la dreapta prin rotrea ei la 90 de grade si traspunerea acesteia.
* Pentru ca trebuie sa returnam un sir de caractere, alocam un buffer 
* in care punem pe rand elementele matricei, prin concatenare.
*/
void *RotateMatrix(void *input)
{
	int i, j;
	int **mat;
	mat = malloc((*(int *)input + 1 ) * sizeof(int *));

	if (mat == NULL) {
		printf("Eroare la alocare\n");
		free(mat);
		return NULL;
	}

	for (i = 1; i <= *(int *)input; i++) {

		mat[i] = calloc(*(int *)input + 1, sizeof(int));
		if (mat[i] == NULL) {
			for (j = 0; j < i; j++) {
				free(mat[j]);
			}
			free(mat);
			printf("Eroare la alocare\n");
			return NULL;
		}
	}

	for (i = 1; i <= *(int *)input; i++) {
        for (j = 1; j <= *(int *)input; j++) {
            mat[i][j] = concat_ints(i,j);
        }
    }

	reverse_mat(mat, *(int *)input);
    transpose_matrix(mat, *(int *)input);
	
	char *buffer = calloc(MAX_LEN_STR_OUT, sizeof(char)); 
	if (!buffer) {
		printf("Eroare la alocare\n");
		free(buffer);
		return NULL;
	}

	for (i = 1; i <= *(int *)input; i++) {
		if (i > 1) {
			strcat(buffer, "\n"); 
		}

        for (j = 1; j <= *(int *)input; j++) {
			if (j > 1) { 
				strcat(buffer," "); 
			}

			char *str = malloc(MAX_LEN_STR_LOC);
			if (!str) {
				printf("Eroare la alocare\n");
				free(str);
				return NULL;
			}

			sprintf(str, "%d", mat[i][j]); 
            strcat(buffer, str);
			free(str);
        }
    }

	for (i = 1; i <= *(int *)input; i++) {
		free(mat[i]);
	}
	free(mat);

	return (void *)buffer;
}

/*
* Task 2.
* Functia desparte in tokeni sirul primit ca parametru si calculeaza suma 
* numerelor din sir. Pentru a returna un sir de caractere, se aloca
* un buffer de tip char, in care se pune suma de tip intreg.
*/
void *DecodeString(void *input)
{
	int sum = 0;
	char *token;
	char *array_input = (char *)input;

	token = strtok(array_input, "_");
	while (token != NULL) {
		sum += atoi(token);
		token = strtok(NULL, "_");
	}

	char *buffer = calloc(MAX_LEN_STR_OUT, sizeof(char));
	if (!buffer) {
		printf("Eroare la alocare\n");
		free(buffer);
		return NULL;
	}

	sprintf(buffer, "%d", sum);

	return (void *)buffer;
}

/*
* Functia inverseaza elementele unui vector, cu ajutorul a doi pointeri, unul
* de la inceputul vectorului si unul de la sfarsit
*/
void reverse_array(int *array_input, int dim)
{
    int *pos1, *pos2, i, aux;
    pos1 = array_input;
    pos2 = array_input + dim;
    for (i = 0; i < dim / 2; i++) {
        aux = *(pos1 + i);
        *(pos1 + i) = *(pos2 - i - 1);
        *(pos2 - i - 1) = aux;
    }
}

/*
* Task 3.
* Functia primeste un vector ca parametru, iar primul element al vectorului 
* este numărul de elemente rămase în vector. In functie de paritatea acestuia,
* functia returneaza:
* - dacă este număr par se interschimba elementele de pe pozițiile 
* 2k + 1 cu cele de pe pozițiile 2k + 2;
* - dacă este număr impar se inverseza vectorul.
* Pentru ca outputul sa fie un sir de caractere, luam un buffer in care 
* concatenam fiecare element al vectorului folosind un sir auxiliar.
*/
void *InvertArray(void *input)
{
	int *array_input = (int *)input;
	int i, array_size_left = array_input[0];

    if (array_input[0] % 2 != 0) {
        memmove(array_input, array_input + 1, sizeof(int) * (array_size_left));
        reverse_array(array_input, array_size_left);

    } else {
        memmove(array_input, array_input + 1, sizeof(int) * (array_size_left));

        for (i = 0; i < array_size_left; i += 2) {
            int aux;
            aux = array_input[i];
            array_input[i] = array_input[i + 1];
            array_input[i + 1] = aux;
        }
    }

    char *buffer = calloc(MAX_LEN_STR_OUT, sizeof(char)); 
	if (!buffer) {
		printf("Eroare la alocare\n");
		free(buffer);
		return NULL;
	}

    for (i = 0; i < array_size_left; i++) {
		char *str = malloc(MAX_LEN_STR_LOC);
		if (!str) {
			printf("Eroare la alocare\n");
			return NULL;
		}	

        sprintf(str, "%d ", array_input[i]);
        strcat(buffer, str);
		free(str);
    }

	return (void *)buffer;
}

/*
* Task 4.
* Functia aloca un pointer la o structura de tip Player si campurile name,
* color și hat, returnează referința la structura pe care o aloca.
*/
Player *allocPlayer()
{
	Player *player;

	player = malloc(sizeof(Player));
	if (!player) {
   		printf("Eroare de alocare");
		free(player);
    	return NULL;
  	}

	player->alive = 1;
	player->name = malloc(MAX_LEN_STR_ATR);
	player->color = malloc(MAX_LEN_STR_ATR);
	player->hat = malloc(MAX_LEN_STR_ATR);

	return player;
}

/*
* Task 4
* Functia aloca un pointer la o structura de tip Game si campul name si
* returneaza referinta la structura pe care o aloca.
*/
Game *allocGame()
{
	Game *game;

	game = malloc(sizeof(Game) + sizeof(Player));
	if (!game) {
   		printf("Eroare de alocare\n");
    	return NULL;
  	}

	game->name = malloc(MAX_LEN_STR_ATR);
	if (!game->name) {
   		printf("Eroare de alocare\n");
		free(game->name);
		free(game);
    	return NULL;
  	}

	return game;
}

/*
* Task 5.
* Functia citeste din fisierul de input numele, culoarea si tipul
* de palarie pentru jucator, numar de locatii. Aloca si citeste
* locatiile jucatorului in functie de numarul de locatii.
* Citeste tipul de jucator intr-un buffer de tip char, iar apoi 
* se atribuie task-ul specific din vectorul Abilities pentru fiecare
* jucator in functie de rolul sau.
*/
Player *ReadPlayer(FILE *inputFile)
{
	int i;

	Player *player = allocPlayer();
	if (!player) {
		printf("Eroare la alocare\n");
		free(player);
		return NULL;
	}

	fscanf(inputFile, "%s", player->name);
	fscanf(inputFile, "%s", player->color);
	fscanf(inputFile, "%s", player->hat);
	fscanf(inputFile, "%d\n", &player->numberOfLocations);
	
	player->locations = malloc(player->numberOfLocations 
									* sizeof(Location));
	if (!player->locations) {
		printf("Eroare la alocare\n");
		free(player->locations);
		return NULL;
	}

	for (i = 0; i < player->numberOfLocations; i++) {
		fscanf(inputFile, "(%d,%d) ", &player->locations[i].x,
									 &player->locations[i].y );
	}
	player->indexOfLocation = 0;
	fscanf(inputFile, "\n");

	char buffer[MAX_LEN_STR_ATR];
	fscanf(inputFile, "%s", buffer);

	if (strcmp(buffer, "Rotator") == 0) {
		player->ability = &RotateMatrix;
		player->playerRole = Rotator;

	} else if (strcmp(buffer, "Decoder") == 0) {
		player->ability = &DecodeString;
		player->playerRole = Decoder;

	} else if (strcmp(buffer, "Invertor") == 0) {
		player->ability = &InvertArray;
		player->playerRole = Invertor;

	} else if(strcmp(buffer, "Impostor") == 0) {
		player->ability = &KillPlayer;
		player->playerRole = Impostor;
	}

	return player;
}

/*
* Task 5
* Functia aloca o structura de tip Game si citeste din fisierul 
* de input numele jocului, killRange-ul si numarul de jucatori, 
* apoi aloca un vector de jucatori si apeleaza pentru fiecare 
* functia precedenta, pentru a le citi datele. In final, sunt citite
* si datele impstorului, care este tot un jucator.
*/
Game *ReadGame(FILE *inputFile)
{
	int i;

	Game *game = allocGame();
	if (!game) {
		printf("Eroare la alocare\n");
		free(game);
		return NULL;
	}

	fscanf(inputFile, "%s", game->name);
	fscanf(inputFile, "%d", &game->killRange);
	fscanf(inputFile, "%d\n", &game->numberOfCrewmates);

    game->crewmates = malloc(game->numberOfCrewmates 
								* sizeof(Player *));
	if (!game->crewmates) {
		printf("Eroare la alocare\n");
		free(game->crewmates);
		return NULL;
	}

	for (i = 0; i < game->numberOfCrewmates; i++) {
		game->crewmates[i] = ReadPlayer(inputFile);
	}

	fscanf(inputFile, "\n");
	game->impostor = ReadPlayer(inputFile);

	return game;
}

/*
* Task 6
* Fucntia afiseaza in fisierul de output datele fiecarui jucator
* (nume, culoare, tipul de palarie, rolul) si locatiile disponibile
* pentru joc.
*/
void WritePlayer(Player *player, FILE *outputFile)
{
	int i;
	char *PlayerRoleToStr = fromEnumtoString(player->playerRole);

	fprintf(outputFile, "Player %s with color %s, hat %s ",
			player->name, player->color, player->hat);
	fprintf(outputFile, "and role %s has entered the game.\n", PlayerRoleToStr);

	fprintf(outputFile, "Player's locations: ");
	for (i = 0; i < player->numberOfLocations; i++) {
		fprintf(outputFile, "(%d,%d) ", player->locations[i].x,
										 player->locations[i].y);
	}

	fprintf(outputFile, "\n");
	free(PlayerRoleToStr);

	return;
}

/*
* Task 6.
* Functia scrie in fisierul de output un mesaj ce anunta inceputul jocului,
* KillRange (distanța maximă de la care un Impostor poate să omoare un 
* alt jucător), numarul de jucatori, iar pentru fiecare jucator se 
* afiseaza datele, apeland functia precedenta si, in final, datele impostorului.
*/
void WriteGame(Game *game, FILE *outputFile)
{
	int i;

	fprintf(outputFile, "Game %s has just started!\n", game->name);
	fprintf(outputFile, "	Game options:\n");
	fprintf(outputFile, "Kill Range: %d\n", game->killRange);
	fprintf(outputFile, "Number of crewmates: %d\n", game->numberOfCrewmates);
	fprintf(outputFile, "\n");
	fprintf(outputFile, "	Crewmates:\n");

	for (i = 0; i < game->numberOfCrewmates; i++) {
		WritePlayer(game->crewmates[i], outputFile);
	}

	fprintf(outputFile, "\n");
	fprintf(outputFile, "	Impostor:\n");
	WritePlayer(game->impostor, outputFile);

	return;
}

/*
* Task 7.
* Functia reprezinta task-ul impostorului, de a omori pe cel mai apropiat 
* jucator. Pentru fiecare jucator, se verifica daca este viu si se 
* calculeaza distanta Manhattan fata de impostor. Daca aceasta este mai
* mica fata de killrange si jucatorul este in viata, se incearca obtinerea
* distantei minime fata de impostor si a pozitiei in vectorul de jucatori
* a acestuia, prin compararea cu distanta minima de pana atunci.
* Daca s-a obtinut o distanta mai mica decat killrange(care va fi cea minima), 
* se returneaza mesajul care anunta ca impostorul a omoarat acel jucator.
* Altfel, se afiseaza ca nu a putut omori pe nimeni.
*/
void *KillPlayer(void *input)
{
	Game *game = (Game *)input;
	int distance_to_kill = game->killRange, x_imp, y_imp;
	int i, ok = 0, pos_max = 0, dis_min = 0;

	char *buffer = malloc(MAX_LEN_STR_OUT * sizeof(char));
	if (!buffer) {
		printf("Eroare la alocare\n");
		free(buffer);
		return NULL;
	}

	x_imp = game->impostor->locations[game->impostor->indexOfLocation].x;
	y_imp = game->impostor->locations[game->impostor->indexOfLocation].y;

	for (i = 0; i < game->numberOfCrewmates; i++) {
		
		if (game->crewmates[i]->ability == 0) {
			continue;
		}

		int x1, y1;
		x1 = game->crewmates[i]->locations[game->crewmates[i]->indexOfLocation].x;
		y1 = game->crewmates[i]->locations[game->crewmates[i]->indexOfLocation].y;
		int distance = abs(x1 - x_imp) + abs(y1 - y_imp);

		if (i == 0) {
			dis_min = distance;
		}		

		if (distance <= distance_to_kill && game->crewmates[i]->alive == 1) {
			ok = 1;
			if (distance <= dis_min){
				dis_min = distance;
				pos_max = i;
			}
		}
	}

	if (ok == 1 && game->crewmates[pos_max]->alive == 1) {
		sprintf(buffer, "Impostor %s has just killed crewmate %s from distance %d.",
			game->impostor->name, game->crewmates[pos_max]->name, dis_min);
			game->crewmates[pos_max]->alive = 0;

	} else {	
		sprintf(buffer, "Impostor %s couldn't kill anybody.", game->impostor->name);
	}

	return (void *)buffer;
}

/*
* Task 8.
* Functia descrie in fisierul de output mai multe runde de joc.
* O runda consta in:
* -afisarea datelor fiecarui jucator;
* -afisarea pozitiei din vectorul de locatii spre care a inaintat;
* -afisarea task-ului specific, cu inputul din void **inputMatrix;
* La final, sunt afisatele datele, pozitia, task-ul impostorului.
* Daca impostorul reuseste sa omoare un jucator, se afiseaza la rundele
* urmatoare ca acesta este mort, fara alte date.
*/
void CalcuateNextCycleOfGame(Game *game, FILE *outputFile, void **inputMatrix)
{
	int i;
	for (i = 0; i < game->numberOfCrewmates; i++) { 
		if (game->crewmates[i]->alive == 1) {
				
			game->crewmates[i]->indexOfLocation += 1;
			int nr_of_locations = game->crewmates[i]->numberOfLocations;

			if (game->crewmates[i]->indexOfLocation == nr_of_locations) {
				game->crewmates[i]->indexOfLocation = 0;
			}

			fprintf(outputFile, "Crewmate %s went to location (%d,%d).\n",
					game->crewmates[i]->name,
					game->crewmates[i]->locations[game->crewmates[i]->indexOfLocation].x,
					game->crewmates[i]->locations[game->crewmates[i]->indexOfLocation].y);

			fprintf(outputFile, "Crewmate %s's output:\n", game->crewmates[i]->name);

			char *Player_ability = game->crewmates[i]->ability(inputMatrix[i]);
			fprintf(outputFile, "%s", Player_ability);		
			fprintf(outputFile, "\n");
			free(Player_ability);

			} else {
				fprintf(outputFile, "Crewmate %s is dead.\n", game->crewmates[i]->name);
			}
		}

	game->impostor->indexOfLocation += 1;
	if (game->impostor->indexOfLocation == game->impostor->numberOfLocations) {
		game->impostor->indexOfLocation = 0;
	}
		
	fprintf(outputFile, "Impostor %s went to location (%d,%d).\n",
					game->impostor->name, 
					game->impostor->locations[game->impostor->indexOfLocation].x,
					game->impostor->locations[game->impostor->indexOfLocation].y);
		
	fprintf(outputFile, "Impostor %s's output:\n", game->impostor->name);

	char *impostor_ability = game->impostor->ability(inputMatrix[i]);
	fprintf(outputFile, "%s\n", impostor_ability);
	free(impostor_ability);

	return;
}

/*
* Task 9.
* Functia elibereaza campurile alocate din structura Player,
* iar in final, referinta la structura.
*/
void FreePlayer(Player *player)
{
	free(player->name);
	free(player->color);
	free(player->hat);
	free(player->locations);
	free(player);
	return;
}

/*
* Task 9.
* Functia elibereaza campul nume al structurii game, iar pentru
* fiecare jucator, se elibereaza campurile si referinta prin apelul
* functiei precedente, la fel si pentru impostor, care este tot un 
* jucator. In final, se elibereaza vectorul de jucatori si referinta
* la structura de tip Game.
*/
void FreeGame(Game *game)
{
	int i;

	free(game->name);
	for (i = 0; i < game->numberOfCrewmates; i++) {
		FreePlayer(game->crewmates[i]);
	}
	
	FreePlayer(game->impostor);
	free(game->crewmates);
	free(game);
	
	return;
}