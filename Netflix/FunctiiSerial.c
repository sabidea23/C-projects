#include "Serial.h"

/*
* Functia aloca un sezon dintr-un serial. Se initializeaza
* coada de episoade, implementata cu liste simplu inlantuite.
* Se citeste numarul de episoade ale serialului, iar pentru
* fiecare sezon se citeste durata, care reprezinta informaia 
* celulor de lista din coada de episoade. Durata fiecarui episod
* se adauga la durata totala a serialului, primita ca parametru.
*/
void *Citeste_sezon(FILE *in, int *durata_totala)
{    
    TSezon *sezon = (TSezon *)malloc(sizeof(TSezon));
    if (!sezon)
        return NULL;
    
    fscanf(in, "%d", &sezon->nr_episoade);
	
    if (sezon->nr_episoade > MAX_EPISODES 
							|| sezon->nr_episoade < MIN_EPISODES) {
        free(sezon);
        return NULL;
    }

    sezon->episoade = InitQ(sizeof(int));
    int i = 0;

    while (i < sezon->nr_episoade) {
        int durata_episod = 0;
        fscanf(in, "%d", &durata_episod);
        if (durata_episod >= MIN_TIME && durata_episod <= MAX_TIME) {
            IntrQ((void *)sezon->episoade, &durata_episod);
			*durata_totala += durata_episod;
        }
        i++;
    }
    return (void *)sezon;
}

/*
* Functia aloca un serial si initializeaza coada de sezoane.
* Se initializeaza campurile serialului si coada de sezoane, 
* implementata cu liste simplu inlantuite, fiecare celula
* de lista avand ca informatie un sezon. Se determina durata
* totala a serialului ca fiind suma duratelor tuturor episoadelor,
* initial serialul fiind total nevizionat.
*/
void *Citeste_serial(FILE *in, char *nume, float rating, int id)
{
    TSerial *serial = malloc(sizeof(TSerial));
	if (!serial) 
		return NULL;

    serial->id = id;
    if (rating <= MAX_RATING && rating >= MIN_RATING) {
        serial->rating = rating;
    }

    fscanf(in, "%d", &serial->nr_sezoane);
	
    if (serial->nr_sezoane < MIN_SEZONS 
							|| serial->nr_sezoane > MAX_SEZONS) {
        free(serial);
        return NULL;
    }

    serial->nume = malloc(MAX_LENGTH_SERIAL);
    if (!serial->nume) {
        free(serial);
        return NULL;
    }
    strcpy(serial->nume, nume);
    
    serial->sezoane = InitQ(sizeof(TSezon));
    if (!serial->sezoane) {
        free(serial->nume);
        free(serial);
        return NULL;
    }

    int i = 0;
	int durata_totala_serial = 0;
    while (i < serial->nr_sezoane) {
        void *episoade = Citeste_sezon(in, &durata_totala_serial);
        IntrQ((void *)serial->sezoane, episoade);
		i++;
    }

	serial->already_watched = 0;
	serial->total_minutes = durata_totala_serial;
    return (void *)serial;
}

/*
* Functia afiseaza numele si ratingul tuturor serialelor
* unei liste primite ca parametru in fisierul de output.
*/
void Show(TLG lista, FILE *out, int id, TF afi_serial)
{
	fprintf(out, "Categoria %d: [", id);

	while (lista != NULL) {
		afi_serial(lista->info, out);
		if (Cardinal_lista(lista) > 1) 
			fprintf(out, ", ");
		lista = lista->urm;
	}
	fprintf(out, "].\n");
}

/*
* Functia afiseaza numele si ratingul tuturor serialelor
* listei top10 in fisierul de output.
*/
void Show_top10(TLG lista, FILE *out, TF afi_serial)
{
	fprintf(out, "Categoria top10: [");

	while (lista != NULL) {
		afi_serial(lista->info, out);
		if (Cardinal_lista(lista) > 1) 
			fprintf(out, ", ");
		lista = lista->urm;
	}
	fprintf(out, "].\n");
}

/*
* Functia insereaza in lista top10 un nou serial la pozitia dorita.
* Se aloca o noua celula de lista si se citesc datele serialului care
* urmeaza a fi inserat. Daca in lista top10 se afla deja 10 seriale, 
* va fi eliminat. Se parcurge lista top10 pana la pozitia dorita, 
* apoi se face inserare inaintea ei. Daca se face inserare pe prima pozitie,
* se schimba inceputul listei, iar daca lista este vidda, se insereaza primul 
* element al listei. Se afiseaza in fisierul de output numele si ratingul 
* tuturor serialelor din lista.
*/
int Add_top_10(TLG *lista, FILE *in, FILE *out, TF afi_serial)
{
	int pozitie = 0;
	fscanf(in, "%d", &pozitie);
	if (pozitie > MAX_POSITION_IN_TOP10 
							|| pozitie < MIN_POSITION_IN_TOP10)
		return -1;
		
	TLG aux = malloc(sizeof(TSerial));
	if (!aux)
		return -1;

	char nume[MAX_LENGTH_SERIAL];
	float rating = 0;
	fscanf(in, "%s", nume);
	fscanf(in,"%f", &rating);

	aux->info = Citeste_serial(in, nume, rating, pozitie);
	if (!aux->info) {
		free(aux);
		return -1;
	}
	
	if (Cardinal_lista(*lista) >= 10) {
		Elimina_ultimul(*lista);
	}

	TLG p = *lista, ant = p;
	int i = 1;
    
	if (pozitie == 1) {
		aux->urm = *lista;
		*lista = aux;
		Show_top10(*lista, out, afi_serial);
		return 1;
	} 

	for (; (p != NULL) && (i < pozitie); ant = p, p = p->urm, i++);

	if (ant == NULL) {
		aux->urm = *lista;
		*lista = aux;
	} else {
		aux->urm = p;
		ant->urm = aux;	
	}

	Show_top10(*lista, out, afi_serial);
	return 1;
}

/*
* Functia adauga un serial din lista primita ca parametru in coada later.
* Se parcurge lista pana cand se gaseste serialul cu numele primit ca 
* parametru, apoi se muta serialul din celula gasita intr-un pointer
* care va fi introdus in coada si se face avansul in lista. Daca s-a 
* reusit introducerea, se afiseaza mesajul coespunzator la output 
* si creste numarul de elemente in coada later.
*/
void Add_later(TLG *lista, AQ later, TFCmp2 cmp_name, char *name,
				int *pozitie, FILE *out)
{
	void *serial_mutat = malloc(DimEQ(later));
	if (!serial_mutat) {
		return;
	}

	TLG p = *lista, ant = NULL;
	for (; p != NULL; ant = p, p = p->urm) {
		if (cmp_name(p->info, name) == 0) {
			if (ant == NULL) {
				*lista = p->urm;
			} else {
				ant->urm = p->urm;
			}
			serial_mutat = p->info;
			break;
		}
	}

	int res = IntrQ(later, serial_mutat); 
	if (res == 1) {
		fprintf(out, "Serialul %s se afla in coada de asteptare pe pozitia %d.\n",
				name,*pozitie);
		(*pozitie)++;
	}
}

/*
* Functia adauga durata vizionata din serial la durata 
* totala vizonata. Daca aceasta este mai mare sau egala cu
* durata totata a serialului, acesta se dupa in stiva history,
* la output este afisat un mesaj corespunzator si functia
* intoarce 1. Altfel, serialul ramane in currently_watching si
* se vizioneaza in continuare, se intoarce 0.
*/
int Watching_serial(void *info, FILE* out, int time, Ast history) 
{
	TSerial *serial = (TSerial  *)info;
	serial->already_watched += time;

	if (serial->already_watched >= serial->total_minutes) {
		fprintf(out, "Serialul %s a fost vizionat integral.\n", 
					serial->nume);
		Push(history, serial);
		return 1;
	} else {
		return 0;
	}
}

/*
* Functia vizioneaza un serial dintr-o lista. Se parcurge lista 
* pana se gaseste serialul cu numele primit ca parametru. Serialul 
* este mutat din lista, apoi se face avansul. Daca a fost gasit,
* se vizioneaza un numar de minute din serial. Daca acesta nu a fost 
* terminat si mutat in stiva history, se muta in stiva currently_watching.
*/
void Watch_fromTLG(TLG *lista, Ast currently_watching,
				Ast history, TFCmp2 cmp_name, char *name, FILE* out, int time)
{
	void *serial_mutat = malloc(sizeof(TSerial)); 
	if (!serial_mutat) {
		return;
	}

	TLG p = *lista, ant = NULL;

	for (; p != NULL; ant = p, p = p->urm) {
		if (cmp_name(p->info, name) == 0) {
			if (ant == NULL) {
				*lista = p->urm;
			} else {
				ant->urm = p->urm;
			}
			serial_mutat = p->info;
			//free(p);
			break;
		}
	}

	if (serial_mutat != NULL) {
		int res = 0;
		
		res = Watching_serial(serial_mutat, out, time, history);
		if (res == 0) {
			Push(currently_watching, serial_mutat);
		}
	}
}

/*
* Functia vizoneaza un serial dintre cele deja incepute,
* aflate in currently_watching. Se extrage fiecare element
* din stiva si se compara numele cu cel cautat. Daca s-a gasit,
* se vizioneaza serialul. Serialul nu va mai fi introdus in stiva 
* auxiliara. Daca a fost finalizat, s-a mutat direct in stiva history.
* Altfel, dupa refacerea stivei initiale prin rasturnarea celei
* auxiliare, serialul vizionat este introdus in varful stivei 
* currently_watching.
*/
void Continue_to_watch(Ast currently_watching, Ast history,
						char *name, FILE *out, TFCmp2 cmp_name, int time)
{
	void *serial = malloc(DimES(currently_watching));
	if (!serial) {
		return;
	}

	void *serial_nou_vizionat = malloc(DimEQ(currently_watching));
	if (!serial_nou_vizionat) {
		free(serial);
		return;
	}

	Ast stiva_aux = InitS(DimES(currently_watching));
	if (!stiva_aux) {
		free(serial);
		free(serial_nou_vizionat);
		return;
	}

	int res = -1;
	while (VF(currently_watching) != NULL) {
		Pop(currently_watching, serial);
		if (cmp_name(serial, name) == 0) {
			res = Watching_serial(serial, out, time, history);
			serial_nou_vizionat = serial;
			serial = malloc(DimES(currently_watching));
			if (!serial) {
				Rastoarna(stiva_aux, currently_watching);
				return;
			}	
			continue;
		}
		Push(stiva_aux, serial);
		serial = malloc(DimES(currently_watching));
		if (!serial) {
			Rastoarna(stiva_aux, currently_watching);
			return;
		}
	}

	Rastoarna(stiva_aux, currently_watching);
	if (res == 0) {
		Push(currently_watching, serial_nou_vizionat);
	}
}

/*
* Functia vizioneaza un serial din coada later. Se etrag pe rand 
* serialele din coada si se compara numele cu cel cautat. Cand a 
* fost gasit, se vizioneaza serialul. Daca a fost terminat, nu
* se mai adauga in stiva auxiliara, ci direct in history, iar daca nu 
* a fost terminat, in currently_watching.
* In final, se reface stiva auxiliara prin rasturnarea celei auxiliare.
*/
void Watch_from_later(AQ later, Ast currently_watching, Ast history, 
						char *name, FILE *out, int time, TFCmp2 cmp_name)
{
	void *serial = malloc(DimEQ(currently_watching));
	if (!serial) {
		return;
	}

	AQ coada_aux = InitQ(DimEQ(later));
	if (!coada_aux) {
		free(serial);
		return;
	}

	while (!VidaQ(later)) {
		ExtrQ(later, serial);
		if (cmp_name(serial, name) == 0) {
			int res =  Watching_serial(serial, out, time, history);
			if (res == 0) {
				Push(currently_watching, serial); 
			} 

			serial = malloc(DimEQ(later));
			if (!serial) {
				ConcatQ(coada_aux, later);
				return;
			}
			continue;
		}

		IntrQ(coada_aux, serial);
		serial = malloc(DimEQ(later));
		if (!serial) {
			ConcatQ(coada_aux, later);
			return;
		}
	}

	ConcatQ(coada_aux, later);
}

/*
* Functia aloca un nou sezon si citeste din fisierul de input
* un numar de episoade ale sezonului. Se initializeaza coada
* de episoade in care se introduc celulele ce reprezinta episoadele,
* care au ca informatie durata fiecarui episod. Aceasta se aduna la
* durata sezonului, returnat prin efect lateral.
*/
void* Create_new_sezon(int *durata_totala, FILE *in)
{
	TSezon *sezon = (TSezon *)malloc(sizeof(TSezon));
    if (sezon == NULL) {
        return NULL;
	}

	int nr_episoade = 0;
    fscanf(in, "%d", &nr_episoade);
	sezon->nr_episoade = nr_episoade;
	
    if (sezon->nr_episoade > MAX_EPISODES 
							|| sezon->nr_episoade < MIN_EPISODES) {
        free(sezon);
        return NULL;
    }

	sezon->episoade = InitQ(sizeof(TSezon));
	if (!sezon->episoade) {
		free(sezon);
		return NULL;
	}

	int i = 0;
    while (i < sezon->nr_episoade) {
        int durata_episod = 0;
        fscanf(in, "%d", &durata_episod);

        if (durata_episod >= MIN_TIME && durata_episod <= MAX_TIME) {
            IntrQ(sezon->episoade, &durata_episod);
			*durata_totala += durata_episod;
        }
        i++;
    }
	
    return (void *)sezon;
}

/*
* Functia adauga un sezon nou serialului primit ca parametru.
* Se adauga la durata totala a serialului durata noului sezon, 
* iar sezonul este introdus in coada de sezoane.
* Este incrementat numarul de sezoane ale serialului si se 
* afiseaza un mesaj corespunzator la output. 
*/
void Add_sez_for_serial(void *info, FILE *in, FILE *out) 
{
	int new_sezon_time = 0;
	TSerial *serial = (TSerial *)info;
	TSezon *sezon = Create_new_sezon(&new_sezon_time, in);
	if (!sezon) {
		return;
	}
	
	serial->total_minutes += new_sezon_time;
	serial->nr_sezoane++;
	
	if (serial->nr_sezoane > MAX_SEZONS 
				|| serial->nr_sezoane < MIN_SEZONS) {
		return;
	}

	IntrQ(serial->sezoane, sezon);
	fprintf(out, "Serialul %s are un sezon nou.\n", 
			serial->nume);
}

/*
* Functia parcurge lista primita ca parametru pana cand gaseste
* serialul cu numele cautat, caruia ii adauga un sezon nou.
*/
void Add_sez(TLG lista, char *nume, FILE* in, FILE *out,
			TFCmp2 cmp_name)
{
	TLG p = lista;
	for (; p != NULL; p = p->urm) {
		if (cmp_name(p->info, nume) == 0) {
			break; 
		}
	}

	Add_sez_for_serial(p->info, in, out);
}

/*
* Functia adauga un sezon nou pentru serialele aflate in coada later.
* Se extrage fiecare serial din coada later si se compara numele cu cel
* primit ca parametru, apoi se introduce intr-o coada auxiliara.
* Daca serialul a fost gasit, se adauga un nou sezon.
* In final, se reface coada initiala prin concatenarea celei auxiliare
* la aceasta.
*/
void Add_sez_in_later(AQ later, char *name, TFCmp2 cmp_name,
						FILE* in, FILE* out)
{
	void *serial = malloc(DimEQ(later));
	if (!serial) {
		return;
	}
	
	AQ coada_aux = InitQ(DimEQ(later));
	if (!coada_aux) {
		free(serial);
		return;
	}

	while (!VidaQ(later)) {
		ExtrQ(later, serial);
		if (cmp_name(serial, name) == 0) {
			Add_sez_for_serial(serial, in, out);
		}
		IntrQ(coada_aux, serial);
		serial = malloc(DimEQ(later)); 
		if (!serial) {
			ConcatQ(coada_aux, later);
			return;
		}
	}

	ConcatQ(coada_aux, later);
}

/*
* Functia adauga un sezon pentru un serial aflat in stiva currently
* watching. Se cauta in stiva elementul care are numele primit ca parametru,
* prin extragerea fiecarui serial din stiva initiala si introducerea lui
* intr-una auxiliara. Daca serialul a fost gasit, se adauga un sezon,
* In final este refacuta stiva initiala prin rasturnarea stivei auxiliare.
*/
void Add_sez_in_watching(Ast currently_watching, TFCmp2 cmp_name, char *name,
						FILE* in, FILE* out)
{
	void *serial = malloc(DimES(currently_watching));
	if (!serial) {
		return;
	}

	Ast stiva_aux = InitS(DimES(currently_watching));
	if (!stiva_aux) {
		free(serial);
		return;
	}

	while(VF(currently_watching) != NULL) {
		Pop(currently_watching, serial);
		Push(stiva_aux, serial);
		
		if (cmp_name(serial, name) == 0) {
			Add_sez_for_serial(serial, in, out);
		} 
		serial = malloc(DimES(currently_watching)); 
		if (!serial) {
			Rastoarna(stiva_aux, currently_watching);
			return;
		}
	}

	Rastoarna(stiva_aux, currently_watching);
}

/*
* Functia elibereaza coada de episoade
* a unui sezon si sezonul alocat.
*/
void Distruge_sezon(void *info)
{
	TSezon *sezon = (TSezon *)info;
	DistrQ(&(sezon->episoade), free);
	free(sezon);
	sezon = NULL;
}

/* 
* Functia elibereaza numele, coada de sezoane a unui
* serial si serialul alocat.
*/
void Distruge_serial(void *info, TF_free distruge_info)
{
	TSerial* serial = (TSerial *)info;
	free(serial->nume);

	DistrQ(&(serial->sezoane), distruge_info);
	
	free(serial);
	serial = NULL;
}
