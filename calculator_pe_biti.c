#include <stdio.h>
#include <stdlib.h>

void adunare(int poz_nr, int *numere) {
    numere[0] += numere[poz_nr];
    for (int i = 4; i <= 31; ++i)
        if (numere[0] & (1 << i)) {
            numere[0] = numere[0] & (~(1 << i));
        }
}

void xorul(int poz_nr, int *numere) { numere[0] ^= numere[poz_nr]; }

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

         //printf("da1:%d || da2:%d || poz1:%d || poz2:%d\n", da1, da2, poz1,
         //poz2);

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

int main() {
    int op;
    unsigned int a;
    scanf("%d%u", &op, &a);
    // printf("%d %u\n", op, a);
    int numere[5];
    int operatii[5];
    for (int i = op; i > 0; --i) {
        numere[i] = a % 16;
        a /= 16;
        operatii[i - 1] = a % 4;
        a /= 4;
    }
    numere[0] = a % 16;

    // printf("numerele initiale sunt:");
    // for (int i = 0; i <= op; ++i) {
    //     printf("%d ", numere[i]);
    //     afisare(numere[i]);
    //     printf("        ");
    // }
    // printf("\n");

    // afisare(numere[0]);
    for (int i = 0; i < op; ++i) {
        switch (operatii[i]) {
            case 0:
                // printf("adunare:");
                // afisare(numere[0]);
                // printf("    ");
                // afisare(numere[i + 1]);
                // printf("\n");
                adunare(i + 1, numere);
                break;
            case 1:
                // printf("interschimbare:");
                // afisare(numere[0]);
                // printf("    ");
                // afisare(numere[i + 1]);
                // printf("\n");
                interschimbare(i + 1, numere);
                break;
            case 2:
                // printf("rotire:");
                // afisare(numere[0]);
                // printf("    ");
                // afisare(numere[i + 1]);
                // printf("\n");
                numere[i + 1] %= 4;
                while (numere[i + 1]) {
                    rotire_stanga_1_bit(i + 1, numere);
                    // afisare(numere[0]);
                    numere[i + 1]--;
                }
                break;
            case 3:
                // printf("xor:");
                // afisare(numere[0]);
                // printf("    ");
                // afisare(numere[i + 1]);
                // printf("\n");
                xorul(i + 1, numere);
                break;
        }
        // printf("%d    ", numere[0]);
    }

    // iei numere[0], operatii[0], numere[1]
    // for (int i = 0; i <= op; ++i) {
    //     printf("%d ", numere[i]);
    //     afisare(numere[i]);
    // }
    // printf("%d\n", numere[0]);

    // for(int i = 0; i < 3; ++i) {
    //     printf("%d ", operatii[i]);
    // }

     printf("%d", numere[0]);

    return 0;
}
