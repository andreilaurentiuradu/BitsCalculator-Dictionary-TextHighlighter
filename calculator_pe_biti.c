#include <stdio.h>
#include <stdlib.h>

struct calculator {
    void (*function)(int, int *);
};

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

        if (ok1 == ok2) {
            numere[0] = numere[0] & (~(1 << i));
        } else {
            numere[0] = numere[0] | (1 << i);
        }
    }
}

void rotire_stanga_1_bit(int poz_nr, int *numere) {
    int da = numere[0] & (1 << 3);        // bitul de pus pe pozitia 0
    numere[0] <<= 1;                      // muti la stanga cu o pozitie
    numere[0] = numere[0] & (~(1 << 4));  // setezi bitul de pe pozitia 4 pe 0
    if (da) {                             // daca bitul e 1
        numere[0] = numere[0] | 1;        // setezi bitu 0 pe 1
    } else {
        numere[0] = numere[0] & (~1);
    }
}

void rotire_stanga(int poz_nr, int *numere) {
    numere[poz_nr] %= 4;
    while (numere[poz_nr]) {
        rotire_stanga_1_bit(poz_nr, numere);
        // afisare(numere[0]);
        numere[poz_nr]--;
    }
}

void interschimbare(int poz_nr, int *numere) {
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

    if (poz1 != poz2) {
        int da1 = 0, da2 = 0;

        if (numere[0] & (1 << (3 - poz1))) da1 = 1;

        if (numere[0] & (1 << (3 - poz2))) da2 = 1;

        // printf("da1:%d || da2:%d || poz1:%d || poz2:%d\n", da1, da2, poz1,
        // poz2);

        if (da1 != da2) {
            if (da1 == 0) {
                numere[0] = numere[0] |
                            (1 << (3 - poz1));  // setezi bitu de pe poz1 pe 1
                numere[0] =
                    numere[0] &
                    (~(1 << (3 - poz2)));  // resetezi bitu de pe poz2(pe 0)
            } else {
                numere[0] = numere[0] |
                            (1 << (3 - poz2));  // setezi bitu de pe poz1 pe 1
                numere[0] =
                    numere[0] &
                    (~(1 << (3 - poz1)));  // resetezi bitu de pe poz2(pe 0)
            }
        }
    }
}

void afisare(int x) {
    for (int i = 8; i >= 0; --i) {
        if (x & (1 << i)) {
            printf("1");
        } else
            printf("0");
    }
    // printf("\n");
}

void calculam(struct calculator *my_operations, int op, int *numere) {
    // afisare(numere[0]);
    int i;
    for (i = 0; i < op; ++i) {
        my_operations[i].function(i + 1, numere);
    }
}

int main() {
    int op;
    unsigned int a;
    scanf("%d%u", &op, &a);
    struct calculator *oper = malloc(op * sizeof(struct calculator *));
    int numere[5], i;
    // int operatii[5];
    for (i = op; i > 0; --i) {
        numere[i] = a % 16;
        a /= 16;
        // operatii[i - 1] = a % 4;
        switch (a % 4) {
            case 0:
                oper[i - 1].function = adunare;
                break;
            case 1:
                oper[i - 1].function = interschimbare;
                break;
            case 2:
                oper[i - 1].function = rotire_stanga;
                break;
            case 3:
                oper[i - 1].function = xorul;
                break;
        }
        a /= 4;
    }
    numere[0] = a % 16;
    calculam(oper, op, numere);
    printf("%d", numere[0]);

    return 0;
}
