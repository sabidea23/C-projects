-> Functia reverse_mat() roteste matricea primita ca parametru
la 90 de grade. Se foloseste la task1, pentru a ajunge la 
outputul cerut.

-> Functia transpose_matrix() aduce maricea primita ca parametru
la forma ei transpusa. Se foloseste la task1, pentru a ajunge la 
outputul cerut.

-> Functia concat_ints() concateneaza indicele liniei si indicele
coloane pentru a forma elementele matricei de forma ij de la task1.
Se folosesc doua siruri, care sunt concatenate, apoi functia returneaza
elementul matricei de tip intreg prin convertire de la char, cu functia 
atoi().

-> TASK 1: functia RotateMatrix() aloca dinamic o matrice in functie de
dimensiunea sa, primita ca parametru si se verifica alocarea.
Apoi, se obtine matricea patratica cu elementele de forma ij prin 
apelul functiei  concat_ints(), cu indecele liniei si coloanei.
Matricea dorita se obtine prin rotirea celei initiale la 90 de grade, 
apoi prin traspunerea acesteia.
Pentru ca functia trebuie sa returneze un sir de caractere (convertit
la void), se aloca un char buffer Se foloseste un sir auxiliar(str),
care este alocat dinamic si retine, pe rand, elementele matricei, 
care sunt concatenate in buffer. Functia returneaza buffer-ul convertit 
la void.

-> TASK2: functia DecodeString() primeste ca parametru un sir format din
numere delimitate de caracterul "_" si calculeaza suma acestora. Numere
sunt extrase din sir cu ajutorul functiei strtok si adaugate la suma de 
tip intreg prin convertirea de la char la int, cu functia atoi. Deoarece 
functia trebuie sa returneze un sir de caractere convertit la char, 
se aloca un char buffer in care se pune suma calculata, cu ajutorul 
functiei sprintf.

-> Functia reverse_array() ivberseaza elementele vectorului primit ca 
parametru. Se folosesc doi pointeri, pos1 care retine adresa de inceput
a vectorului si pos2, adresa de la finalul acestuia. Se foloseste la task3.

-> TASK3: functia InvertArray() primeste ca parametru un vector cu cast 
la void, iar primul element al vectorului reprezinta numărul de elemente 
rămase în vector. In functie de paritate acestuia, functia returneaza:
- dacă este număr par se interschimba elementele de pe pozițiile 
2k + 1 cu cele de pe pozițiile 2k + 2;
- dacă este număr impar se inverseza vectorul.
Deoarece output-ul trebuie sa fie un sir de caracter(cu cast la void),
am alocat un char buffer si verificam alocarea, in care pun element 
cu element vectorul trasnformat, fara primul element, de lungime
array_size_left. Acest lucru se face cu ajutorul unui sir auxiliar 
str, care concateneaza fiecare element in buffer.

-> TASK4: -functia allocPlayer() aloca o structura de tipul Player si 
campurile name, color și hat ale acesteia, cu lungimea MAX_LEN_STR_ATR 
si se atribuie valoarea 1 pentru alive (la inceput, toti jucatorii sunt
in viata).
          -functia allocGame() aloca o structura de tipul Game, verifica 
alocarea si aloca campul name cu lungimea MAX_LEN_STR_ATR.

-> TASK5: -functia ReadPlayer() apeleaza functia allocPlayer() pentru a 
aloca o structua de tip Player. Apoi, se citesc din fisierul de input
numele, culoarea si tipul de palarie pentru jucator. Se citeste numarul
de elemente ale vectorului de locatii si ae aloca dinamic vectorul, apoi
se citesc pe rand locatiile posibile ale jucatorului. Se citeste din 
fisierul de input intr-un char buffer rolul jucatorului, apoi, prin 
compararea cu cele existente, se atribuie rolul corespunzator fiecarui
jucator si abilitatea,  salvate în vectorul de referințe la funcții: void*
(* Abilities[4])(void* x) = {RotateMatrix, DecodeString, InvertArray,
KillPlayer}.(se va folosi la task 7, unde jucatorii trebuie sa isi faca
task-ul in functie de rol).
        -functia ReadGame() apeleaza functia allocGame() pentru alocarea
unei structuri de tip Game. Apoi citeste din fisierul de input numele
jocului, KillRange si numarul de jucatori si aloca un vector de referinte
pentru jucatori. Apoi se citesc datele fiecarui jucator, apeland functia
anterioara, inclusiv pentru impostor, care este tot un jucator.

-> TASK 6: -functia WriteGame() scrie in fisierul de output datele
jucatorului (nume, culoare, palarie, rol) si locatiile din vectorul
de locatii ale acestuia.
          -functia WriteGame() scrie in fisierul de output datele 
jocului(nume, KillRange, numarul de jucatori), apoi citeste datele
fiecarui jucator prin apelul functiei anterioare, inclusiv pentru impostor.
Datele sunt scrise in fisierul de output, outputFile.

-> TASK 7: functia KillPlayer() reprezinta task-ul impostorului,
care incearca sa omoare cel mai aprpiat coleg de echipa, distanta 
fiind calculata ca Distanța Manhattan(doar daca este mai mica sau
egala cu KillRange) Input-ul funcției este un void *care este o
referință la o structura de tip Game. Pentru fiecare jucator, daca
este viu, se calculeaza distanta Manhattan fata de impostor. Daca este
mai mica sau egala cu KillRange, se incearca obtinerea distantei minime,
prin compararea cu distanta minima obtinuta pana la acel jucaor.
Dacă există mai mulți colegi de echipaj la aceeași distanță fată de
impostor este memorat colegul de echipaj cu indicele cel mai mare
(pos_max). Daca s-a obtinut o distanta mai mica decat KillRange,
va fi distanta minima, iar functia returneaza un mesajul prin care anunta
ca impostorul a omoaret acel jucator. Altfel, mesajul anunta ca nu a putut 
omori pe nimeni. Functia returneaza un sir de caractere cu cast la void.

-> TASK8: functia CalcuateNextCycleOfGame() descrie desfasurarea 
mai multor runde de joc. O runda se desfasoara astfel:
- daca jucatorul este in viata, se afiseaza locatia spre care acesteia
a inaintat in vectorul de locatii (fiecare jucător se mișcă circular
prin vectorul de locații). Apoi, jucatorul isi face task-ul, prin
apelul functiei corespunzatoare rolului sau, cu input-ul primit
din matricea inputMatrix, cu indicele acelui jucator din vectorul
de jucatori;
- daca jucatorul a fost omorat de impostor, se afiseaza la fiecare runda
ca acesta este mort, fara alte date;
-la final, se afiseaza datele impostorului si task-ul sau.
Toate informatiile sunt scrise in fisierul de output, outputFile.

-> TASK 9: -functia FreePlayer() elibereaza campurile alocate anterior din 
structura de tip Player si referinta la structura.
          -functia FreeGame() elibereaza campul name al structurii de 
tip Game alocate anterior, iar pentru fiecare jucator, se elibereaza
campurile si referinta prin apelul functiei precedente, la fel si
pentru impostor, care este tot un jucator. Se elibereaza referinta
la structura de tip Game.