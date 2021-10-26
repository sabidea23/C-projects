#include "functii.h"

/* 
* Se citesc comenzile din fisierul de input si in 
* functie de acestea sunt citite restul datelor,
* apoi se executa comanda corespunzatoare. 
*/
int main(int argc, char **argv)
{
    FILE *in = fopen(argv[2], "rt");
    if (!in) {
        return -1;
    }

    FILE *out = fopen(argv[3], "wt");
    if (!out) {
        return -1;
    } 
    
    size_t number_of_lists = atoi(argv[1]);
    TH *hash_tabel = IniTH(number_of_lists, codHash);
    if (!hash_tabel)
        return -1;

    char option[MAX];
    while (fscanf(in, "%s", option) != EOF) {

        if (strcmp(option, "put") == 0) {
            char key[MAX];
            char value[MAX];
            fscanf(in, "%s", key);
            fscanf(in, "%s", value);
            InsTH(hash_tabel, (void *)key, (void *)value, cmp_key);
            
        } else if (strcmp(option, "get") == 0) {
            char key[MAX];
            fscanf(in, "%s", key);
            Get_key(hash_tabel, (void *)key, out, cmp_key);

        } else if (strcmp(option, "remove") == 0) { 
            char key[MAX];
            fscanf(in, "%s", key);
            Remove_key(hash_tabel, (void *)key, cmp_key, DistrInfo);

        } else if (strcmp(option, "find") == 0) {
            char key[MAX];
            fscanf(in, "%s", key);
            Find_key(hash_tabel, (void *)key, cmp_key, out);

        } else if (strcmp(option, "print_bucket") == 0) {
            char index_bucket[MAX];
            fscanf(in, "%s", index_bucket);
            Print_bucket(hash_tabel, index_bucket, out);

        } else {
            Print(hash_tabel, out);
        }
    }

    fclose(in);
    fclose(out);

    DistrTH(&hash_tabel, DistrInfo); 
    return 0;
}