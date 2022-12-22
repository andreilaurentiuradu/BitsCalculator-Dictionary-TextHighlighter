#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char simplu[][100] = {"from", "in",    "unit",   "or",    "while",
                            "int",  "float", "double", "string"};
const char combo[][100] = {"for",  "each", "is",    "a",
                           "list", "of",   "first", "of"};
// cuvant combo = este o combinatie de doua cuvinte alaturate din combo, primul
// aflandu-se pe pozitie para cautam cuvintele in vectorul de cuvinte simplu
bool search_simple(char *s) {
    int i;
    for (i = 0; i < 9; ++i) {
        if (strcmp(s, simplu[i]) == 0) {
            return true;
        }
    }
    return false;
}

// functie pentru sublinierea unui cuvant simplu(nu contine spatii)
void modify(char *s, int nr) {
    int i, j;
    if (nr == 1) {
        // daca e primul
        for (i = 0; i < strlen(s) && s[i] != ' '; ++i) {
            s[i] = '_';
        }
    } else {
        // daca nu e primul numaram cate grupari de tipul spatiu si ceva diferit
        // de spatiu avem pentru a ajunge la cuvantul de pe pozitia nr
        --nr;
        for (i = 1; i < strlen(s); ++i) {
            if (s[i - 1] == ' ' && s[i] != ' ') {
                --nr;
                if (!nr) {
                    // daca am ajuns la cuvantul de pe pozitia cautata il
                    // subliniem
                    for (j = i; j < strlen(s) && s[j] != ' '; ++j) {
                        s[j] = '_';
                    }
                    break;
                }
            }
        }
    }
}

// functie pentru sublinierea pentru combouri
void complex_modify(char *s, int nr) {
    int cuv = 1, i, j;
    if (nr == 2) {
        // daca primele doua formeaza un combo si trebuie sa le subliniem
        // portiunea din sir(cu tot cu spatiu)
        // pentru primul cuvant
        for (i = 0; i < strlen(s) && s[i] != ' '; ++i) {
            s[i] = '_';
        }
        // pentru spatii
        for (; i < strlen(s) && s[i] == ' '; ++i) {
            s[i] = '_';
        }
        // pentru al doilea cuvant
        for (; i < strlen(s) && s[i] != ' '; ++i) {
            s[i] = '_';
        }
    } else {
        for (i = 1; i < strlen(s); ++i) {
            if (s[i - 1] == ' ' && s[i] != ' ') {
                cuv++;
                if (cuv == nr - 1) {
                    // cuvantul anterior
                    for (j = i; j < strlen(s) && s[j] != ' '; ++j) {
                        s[j] = '_';
                    }
                    // spatiile
                    for (; j < strlen(s) && s[j] == ' '; ++j) {
                        s[j] = '_';
                    }
                    // cuvantul curent
                    for (; j < strlen(s) && s[j] != ' '; ++j) {
                        s[j] = '_';
                    }
                    break;
                }
            }
        }
    }
}

void underline(char *s) {
    // facem o copie sirului initial pentru a putea lua cuvintele
    char *copie_sir = malloc((strlen(s) + 1) * sizeof(char));
    strcpy(copie_sir, s);
    copie_sir[strlen(s)] = '\0';

    // cream doua tablouri in care vom retine cuvantul curent, respectiv
    // cuvantul anterior
    char *cuv_curent = malloc((strlen(copie_sir) + 1) * sizeof(char));
    char *cuv_anterior = malloc((strlen(copie_sir) + 1) * sizeof(char));
    cuv_anterior[0] = '\0';

    // spargem in cuvinte textul din copie_sir
    cuv_curent = strtok(copie_sir, " ");
    int nr = 0, i;
    while (cuv_curent != NULL) {
        ++nr;
        if (search_simple(cuv_curent)) {
            // daca e cuvant simplu
            modify(s, nr);
        }

        // combouri
        for (i = 0; i < 7; i += 2) {
            if (strcmp(cuv_anterior, combo[i]) == 0 &&
                strcmp(cuv_curent, combo[i + 1]) == 0) {
                // daca am gasit un cuvant combo
                complex_modify(s, nr);
                nr--;  // dispare un cuvant prin unirea a doua
            }
        }

        // daca gasim un cuvant care e in componenta unui combo dar nu formeaza
        // combo si este si cuvant care trebuie subliniat
        for (i = 0; i < 3; i += 2) {
            if (strcmp(cuv_anterior, combo[i]) == 0 &&
                strcmp(cuv_curent, combo[i + 1]) != 0) {
                modify(s, nr - 1);
            }
        }

        // daca ultimul cuvant trebuie subliniat si nu e in vectorul simplu
        // (face parte dintr-un combo dar se subliniaza si separat)
        if (strcmp(cuv_curent, combo[0]) == 0 ||
            strcmp(cuv_curent, combo[2]) == 0) {
            modify(s, nr);
        }

        // trecem la urmatorul cuvant de pe rand
        strcpy(cuv_anterior, cuv_curent);
        cuv_anterior[strlen(cuv_curent)] = '\0';
        cuv_curent = strtok(NULL, " ");
    }

    // afisam cuvantul subliniat
    for (i = 0; i < strlen(s); ++i) {
        if (s[i] == '_')
            printf("_");
        else
            printf(" ");
    }
    printf("\n");
}

int main() {
    int n, i;
    // tabloul in care retinem cate o linie de text
    char *linie = malloc(102 * sizeof(char));
    scanf("%d", &n);
    // scapam de enterul de dupa n
    getchar();

    // tabloul in care retinem liniile textului
    char **sir_linie = malloc(n * sizeof(char *));

    for (i = 0; i < n; ++i) {
        fgets(linie, 102, stdin);
        // scapam de enter
        linie[strlen(linie) - 1] = '\0';
        sir_linie[i] = malloc((strlen(linie) + 1) * sizeof(char));
        // copiem linia in tabloul alocat dinamic
        strcpy(sir_linie[i], linie);
    }

    for (i = 0; i < n; ++i) {
        printf("%s\n", sir_linie[i]);
        underline(sir_linie[i]);
    }

    return 0;
}
