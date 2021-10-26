#include "boardUtils.h"
#include "scrabble.h"

/*
* Functia main apeleaza functiile pentru task-ul corespunzator in functie de primului input 
* primit (0-5 pentru tema, 6 pentru bonus), iar restul de date se citesc asa cum este descris 
* pentru fiecare cerinta in parte.
*/
int main()
{

    char input[MAX];
    fgets(input,MAX,stdin);

    char *token  = strtok(input, " ,.- "); 

    switch (*token) {
    case '0':
        task0();
        break;
    case '1':
        task1();
        break;
    case '2':
        task2();
        break;
    case '3':
        task3();
        break;
    case '4':
        clear_board();
        task4();
        print_board(board);
        break;
    case '5':
        clear_board();
        task5();
        break;
    case '6':
        clear_board();
        task6();
        break;
    default:
        break;
    }

    return 0;
}