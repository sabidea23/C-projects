#include "utils.h"
#include "Stiva.h"
#include "Coada.h"
#include "TLG.h"
#include "Serial.h"

/*
* Se declara cate o lista pentru fiecare  categorie de seriale
* si se initializeaza stivele si cozile cu care vom lucra.
* Se deschid fisiele de input si output. Se citesc comenzile din
* fisierul de input si in functie de acestea se efectueaza operatia
* dorita. 
*/
int main(int argc, char *argv[])
{
    TLG tendinte = NULL, documentare = NULL, 
		tutoriale_C = NULL, top10 = NULL;

	AQ watch_later = InitQ(sizeof(TSerial));
	if (!watch_later) {
		return -1;
	}

	Ast currently_watching = InitS(sizeof(TSerial));
	if (!currently_watching) {
		free(watch_later);
		return -1;
	}

	Ast history = InitS(sizeof(TSerial));
	if (!history) {
		free(currently_watching);
		free(watch_later);
		return -1;
	}

	FILE *out = fopen(argv[2], "wt");
    if (!out) {
        return -1;
	}

    FILE *in = fopen(argv[1], "rt");
    if (!in) {
        return -1;
	}

	char option[MAX_LENGTH_OPTION];
	int pozitie_in_later = 1;

	while (fscanf(in, "%s", option) != EOF) {
		if (strcmp(option, "add") == 0) { 
			int total_seriale = 0;
			total_seriale = Cardinal_lista(tendinte) + Cardinal_lista(documentare)
						+ Cardinal_lista(tutoriale_C) + Cardinal_lista(top10);
			if (total_seriale >= MAX_SERIES) {
				continue;
			}

			int id = 0;
			fscanf(in, "%d", &id);
			if (id == 1) {
				Inserare_TLG(&tendinte, in, id, cmp_rating, cmp_name, out);
			} else if (id == 2) {
				Inserare_TLG(&documentare, in, id, cmp_rating, cmp_name, out);
			} else if (id == 3) {
				Inserare_TLG(&tutoriale_C, in, id, cmp_rating, cmp_name, out);
			}

		} else if (strcmp(option, "show") == 0) {
			
			char category[MAX_LENGTH_OPTION];
			fscanf(in,"%s", category);

			if (is_integer(category) == 1) {
				int integer = 0;
				integer = atoi(category);
				if (integer == 1) {
					Show(tendinte, out, integer, afi_serial);
				} else if (integer == 2) {
					Show(documentare, out, integer, afi_serial);
				} else if (integer == 3) {
					Show(tutoriale_C, out, integer, afi_serial);
				}

			} else {
				if (strcmp(category, "later") == 0) {
					Show_coada(watch_later, afi_serial, out);
				} else if (strcmp(category, "watching") == 0) {
					Show_stiva(currently_watching, "watching", out); 
				} else if (strcmp(category, "history") == 0) {
					Show_stiva(history, "history", out);
				} else if (strcmp(category, "top10") == 0) {
					Show_top10(top10, out, afi_serial);
				}
			}

		} else if(strcmp(option, "add_top") == 0) {
			Add_top_10(&top10, in, out, afi_serial);
			
		} else if (strcmp(option, "later") == 0) {

			char name[MAX_LENGTH_SERIAL];
			fscanf(in, "%s", name);

			int type = 0;
			type = Cauta_in_liste(tendinte, documentare, tutoriale_C,
									top10, name, compare_num);
			
			if (type == 1) {
				Add_later(&tendinte, watch_later, compare_num, 
							name, &pozitie_in_later, out);
			} else if (type == 2) {
				Add_later(&documentare, watch_later, compare_num, 
							name, &pozitie_in_later, out);
			} else if (type == 3) {
				Add_later(&tutoriale_C, watch_later, compare_num,
							name, &pozitie_in_later, out);
			} else if (type == 4) {
				Add_later(&top10, watch_later, compare_num,
							name, &pozitie_in_later, out);
			}
		} else if (strcmp(option, "add_sez") == 0) {

			char name[MAX_LENGTH_SERIAL];
			fscanf(in, "%s", name);
			if (Cauta_in_stiva(history, compare_num, name) == 0) {
				int type = 0;
				type = Cauta_in_liste(tendinte, documentare, tutoriale_C,
									top10, name, compare_num);
				
				if (type == 1) {
					Add_sez(tendinte, name, in, out, compare_num);
				} else if (type == 2) {
					Add_sez(documentare, name, in, out, compare_num);
				} else if (type == 3) {
					Add_sez(tutoriale_C, name, in, out, compare_num);
				} else if (type == 4) {
					Add_sez(top10, name, in, out, compare_num);
				} else if (Cauta_in_coada(watch_later, compare_num, name) == 1) {
					Add_sez_in_later(watch_later, name, compare_num, in, out);
				} else if (Cauta_in_stiva(currently_watching, compare_num, name) == 1) {
					Add_sez_in_watching(currently_watching, compare_num, name, in, out);
				}
			}
		
		} else if (strcmp(option, "watch") == 0) {
			char name[MAX_LENGTH_SERIAL];
			int time = 0;

			fscanf(in, "%s", name);
			fscanf(in, "%d", &time);

			int res = Cauta_in_stiva(history, compare_num, name);
			if (res == 0) { 
		
				int type = Cauta_in_liste(tendinte, documentare, tutoriale_C, 
										top10, name, compare_num);
				if (type == 1) {
					Watch_fromTLG(&tendinte, currently_watching ,history,
									compare_num, name, out, time);
				} else if (type == 2) {
					Watch_fromTLG(&documentare, currently_watching ,history,
							    	compare_num, name, out, time);
				} else if (type == 3) {
					Watch_fromTLG(&tutoriale_C, currently_watching, history,
									compare_num, name, out, time);
				} else if (type == 4) {
					Watch_fromTLG(&top10, currently_watching, history, 
									compare_num, name, out, time);
				} else if (Cauta_in_coada(watch_later, compare_num, name) == 1) {
					Watch_from_later(watch_later, currently_watching, history,
										name, out, time, compare_num);
					pozitie_in_later--;
				} else if (Cauta_in_stiva(currently_watching, compare_num, name) == 1) {
					Continue_to_watch(currently_watching, history, 
										name, out,compare_num, time);
				}
			}
		}
	}

	fclose(in);
	fclose(out);
	return 0;
}