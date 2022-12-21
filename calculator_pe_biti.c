#include <stdio.h>
#include <stdlib.h>

struct calculator {
    void (*function)(int, int *);
};

// functie pentru implementarea adunarii cu trunchiere la 4 biti
void adunare(int poz_nr, int *numere) {
    int tr = 0, nr_biti = 0, i;
    /*nr_biti poate fi 0, 1, 2, 3 in functie de tr si bitii de pe pozitia pe
     * care ne aflam*/
    for (i = 0; i < 4; ++i) {
        nr_biti = tr;

        // daca bitul din primul numar e 1
        if (numere[0] & (1 << i)) {
            nr_biti++;
        }

        // daca bitul din al doilea numar e 1
        if (numere[poz_nr] & (1 << i)) {
            nr_biti++;
        }

        /* daca numarul de biti este impar atunci pe pozitia noastra vom avea
           bitul setat pe 1, in caz contrar il resetam la 0 */
        if (nr_biti & 1) {
            numere[0] = numere[0] | (1 << i);  // setezi bitul pe 1
        } else {
            numere[0] = numere[0] & (~(1 << i));  // resetam bitul la 0
        }

        /* daca numarul de biti este mai mare decat 1, atunci vom pastra unul
         * pentru urmatoarea pozitie*/

        if (nr_biti > 1) {
            // se pastreaza transportul
            tr = 1;
        } else {
            tr = 0;
        }
    }
}

// implentarea functiei xor
// echivalentul instructiunii numere[0] ^= numere[poz_nr];
void xorul(int poz_nr, int *numere) {
    int i, ok1, ok2;
    for (i = 0; i < 4; ++i) {
        ok1 = ok2 = 0;
        if (numere[0] & (1 << i)) {
            ok1 = 1;
        }

        if (numere[poz_nr] & (1 << i)) {
            ok2 = 1;
        }

        // ok1 si ok2 au valorile bitilor din pozitia i a celor doua numere
        // implicate in operatie
        // daca au aceeasi valoare bitul va fi 0
        // daca au valori diferite bitul va fi 1
        if (ok1 == ok2) {
            numere[0] = numere[0] & (~(1 << i));
        } else {
            numere[0] = numere[0] | (1 << i);
        }
    }
}

// implementarea functiei de rotire la stanga a unui numar cu un bit
void rotire_stanga_1_bit(int poz_nr, int *numere) {
    int ok = numere[0] & (1 << 3);        // bitul de pus pe pozitia 0
    numere[0] <<= 1;                      // muti la stanga cu o pozitie
    numere[0] = numere[0] & (~(1 << 4));  // setezi bitul de pe pozitia 4 pe 0
    if (ok) {
        // daca bitul e 1
        numere[0] = numere[0] | 1;
        // setezi bitu 0 pe 1
    } else {
        // resetezi bitul 1 pe 0
        numere[0] = numere[0] & (~1);
    }
}

// implementarea functiei pentru rotirea la stanga cu un anumit numar de pozitii
void rotire_stanga(int poz_nr, int *numere) {
    // lucram pe 4 biti, deci orice rotire a numarului cu un nr de 4k biti va
    // lasa numarul neschimbat
    // concluzie: putem roti doar de un numar egal cu restul impartirii la 4
    numere[poz_nr] %= 4;
    while (numere[poz_nr]) {
        rotire_stanga_1_bit(poz_nr, numere);
        // afisare(numere[0]);
        numere[poz_nr]--;
    }
}

// implementarea functiei de interschimbare
void interschimbare(int poz_nr, int *numere) {
    // cream in poz1 si poz2 numerele reprezentand pozitiile bitilor ce se vor
    // interschimba
    int poz1 = 0, poz2 = 0;
    if (numere[poz_nr] & (1 << 3)) {
        poz1 = 2;
    }
    if (numere[poz_nr] & (1 << 2)) {
        poz1++;
    }

    if (numere[poz_nr] & (1 << 1)) {
        poz2 = 2;
    }
    if (numere[poz_nr] & (1 << 0)) {
        poz2++;
    }

    // daca sunt pozitii diferite(in caz contrar interschimbarea este inutila)
    if (poz1 != poz2) {
        // retinem valorile bitilor din pozitiile poz1 si poz2
        int bit1 = 0, bit2 = 0;
        if (numere[0] & (1 << (3 - poz1))) bit1 = 1;

        if (numere[0] & (1 << (3 - poz2))) bit2 = 1;

        // daca bitii sunt diferiti atunci are sens interschimbarea
        if (bit1 != bit2) {
            if (bit1 == 0) {
                // daca primul era 0 il setam pe primul pe 1 si il resetam pe al
                // doilea la 0
                numere[0] = numere[0] | (1 << (3 - poz1));
                numere[0] = numere[0] & (~(1 << (3 - poz2)));
            } else {
                // daca primul era 1 il resetam pe primul pe 0 si il setam pe al
                // doilea pe 1
                numere[0] = numere[0] | (1 << (3 - poz2));
                numere[0] = numere[0] & (~(1 << (3 - poz1)));
            }
        }
    }
}

// functie pentru calcularea operatiilor calculatorului
void calculam(struct calculator *my_operations, int op, int *numere) {
    int i;
    for (i = 0; i < op; ++i) {
        my_operations[i].function(i + 1, numere);
    }
}

int main() {
    // numarul de operatii
    int op;
    // variabila care va retine numerele si operatiile
    unsigned int a;
    scanf("%d%u", &op, &a);

    // strcutura ce va retine operatiile
    struct calculator *operatii = malloc(op * sizeof(struct calculator *));

    // vectorul ce va retine numerele pe care se executa operatiile
    int numere[5], i;

    // adaugam numerele si operatiile in tablouri
    for (i = op; i > 0; --i) {
        numere[i] = a % 16;
        a /= 16;
        switch (a % 4) {
            case 0:
                operatii[i - 1].function = adunare;
                break;
            case 1:
                operatii[i - 1].function = interschimbare;
                break;
            case 2:
                operatii[i - 1].function = rotire_stanga;
                break;
            case 3:
                operatii[i - 1].function = xorul;
                break;
        }
        a /= 4;
    }
    numere[0] = a % 16;

    // functia pentru calculul operatiilor
    calculam(operatii, op, numere);

    // afisam numarul obtinut
    printf("%d", numere[0]);

    return 0;
}
