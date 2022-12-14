#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// IDEEE DE IMPLEMENTARE(DACA GASESTI CUVANTUL DIN LISTA SI URMATORUL E TOT DIN
// LISTA ATUNCI LE UNESTI CU _) first of, for, for each, from, in, is, is a,
// list of, unit, or, while, int, float, double, string

const char simplu[][100] = {"from", "in",    "unit",   "or",    "while",
                            "int",  "float", "double", "string"};
// first of, for each, is a, list of, for, is
bool search_simple(char *s) {
    for (int i = 0; i < 9; ++i) {
        // printf("simplu[%d] : %s     ", i, simplu[i]);
        if (strcmp(s, simplu[i]) == 0) {
            // printf("\n");
            return true;
        }
    }
    return false;
}

void modify(char *s, int nr) {
    int cuv = 1;
    if (nr == 1) {
        for (int i = 0; i < strlen(s) && s[i] != ' '; ++i) {
            s[i] = '_';
        }
    } else {
        for (int i = 1; i < strlen(s); ++i) {
            if (s[i - 1] == ' ' && s[i] != ' ') {
                cuv++;
                if (cuv == nr) {
                    for (int j = i; j < strlen(s) && s[j] != ' '; ++j) {
                        s[j] = '_';
                    }
                }
            }
        }
    }
}

// pentru combouri
void complex_modify(char *s, int nr) {
    int cuv = 1;
    for (int i = 1; i < strlen(s); ++i) {
        if (s[i - 1] == ' ' && s[i] != ' ') {
            cuv++;
            if (cuv == nr - 1) {
                // cuvantul anterior
                for (int j = i; j < strlen(s) && s[j] != ' '; ++j) {
                    s[j] = '_';
                }
            }
            if (cuv == nr) {
                // cuvantul curent
                for (int j = i; j < strlen(s) && s[j] != ' '; ++j) {
                    s[j] = '_';
                }
                // spatiile dintre cuvinte
                for (int j = i - 1; j >= 0 && s[j] == ' '; --j) {
                    s[j] = '_';
                }
            }
        }
    }
}
void underline(char *s) {
    printf("%s\n", s);
    char *copie_sir = malloc((strlen(s) + 1) * sizeof(char));
    strcpy(copie_sir, s);
    copie_sir[strlen(s)] = '\0';
    // printf("copie:%s\n", copie_sir);
    char *cuv_curent = malloc((strlen(copie_sir) + 1) * sizeof(char));
    char *cuv_anterior = malloc((strlen(copie_sir) + 1) * sizeof(char));
    cuv_anterior[0] = '\0';
    cuv_curent = strtok(copie_sir, " ");
    int nr = 0;
    while (cuv_curent != NULL) {
        ++nr;
        // printf("cuv_anterior:%s      cuv_curent:%s nr:%d\n", cuv_anterior,
        //        cuv_curent, nr);
        //  int w = strlen(cuv_curent);
        if (search_simple(cuv_curent)) {  // daca e cuvant simplu
            // printf("intra %s: nr:%d\n", cuv_curent, nr);
            modify(s, nr);
        }

        // printf("cuv_anterior:%s      cuv_curent:%s nr:%d\n", cuv_anterior,
        //  cuv_curent, nr);

        // combouri
        if (strcmp(cuv_anterior, "first") == 0 &&
            strcmp(cuv_curent, "of") == 0) {
            complex_modify(s, nr);
            nr--;  // dispare un cuvant prin unirea a doua
        }
        if (strcmp(cuv_anterior, "for") == 0 &&
            strcmp(cuv_curent, "each") == 0) {
            complex_modify(s, nr);
            nr--;  // dispare un cuvant prin unirea a doua
        }
        if (strcmp(cuv_anterior, "is") == 0 && strcmp(cuv_curent, "a") == 0) {
            complex_modify(s, nr);
            nr--;  // dispare un cuvant prin unirea a doua
        }
        if (strcmp(cuv_anterior, "list") == 0 &&
            strcmp(cuv_curent, "of") == 0) {
            complex_modify(s, nr);
            nr--;  // dispare un cuvant prin unirea a doua
        }
        if (strcmp(cuv_anterior, "for") == 0 &&
            strcmp(cuv_curent, "each") != 0) {
            modify(s, nr - 1);
        }
        if (strcmp(cuv_anterior, "is") == 0 && strcmp(cuv_curent, "a") != 0) {
            modify(s, nr - 1);
        }

        // daca ultimul cuvant e rezervat si nu e in vectorul simple
        if (strcmp(cuv_curent, "for") == 0 || strcmp(cuv_curent, "is") == 0) {
            modify(s, nr);
        }

        strcpy(cuv_anterior, cuv_curent);
        cuv_anterior[strlen(cuv_curent)] = '\0';
        cuv_curent = strtok(NULL, " ");
    }
    int i;
    for (i = 0; i < strlen(s); ++i) {
        if (s[i] == '_' || s[i] == ' ') break;
    }

    if (i < strlen(s) && s[i] != ' ') {
        for (int j = 0; j < i; ++j) {
            s[j] = '_';
        }
    }
    // printf("%s\n", s);

    for (int k = 0; k < strlen(s); ++k) {
        if (s[k] == '_')
            printf("_");
        else
            printf(" ");
    }
    printf("\n");
}

int main() {
    int n;
    char *linie = malloc(1000 * sizeof(char));
    scanf("%d", &n);
    getchar();

    // int lungime = 0;
    char *sir = malloc(1 * sizeof(char));
    for (int i = 0; i < n; ++i) {
        fgets(linie, 1001, stdin);
        // lungime += strlen(linie) + 1;
        // sir = realloc(sir, lungime * sizeof(char));
        sir = realloc(sir, (strlen(linie) + 1) * sizeof(char));
        strcpy(sir, linie);
        sir[strlen(linie) - 1] = '\0';
        underline(sir);
        // printf("initial:%s", sir);
        // strcat(sir, linie);
    }
    // citim sirul
    // printf("%s", sir);

    // separam liniile in functie de \n
    // linie = strtok(sir, "\n");

    // while (linie != NULL) {
    //     underline(linie);
    //     linie = strtok(NULL, "\n");
    // }
}
