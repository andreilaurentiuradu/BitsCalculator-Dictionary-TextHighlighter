#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// strcutura ce va contine dictionarul
struct dictionary_entry {
    char *word;
    int priority;
};

// adaugam un cuvant in dictionar cu prioritatea prio
// poz = pozitia pe care va fi adaugat in dictionar
void add(struct dictionary_entry *d, char *cuvant, int poz, int prio) {
    d[poz].priority = prio;
    d[poz].word = malloc((strlen(cuvant) + 1) * sizeof(char));
    strcpy(d[poz].word, cuvant);
    d[poz].word[strlen(cuvant)] = '\0';
}

// cauti a in prima parte din b
bool it_is_a_match(char *a, char *b) {
    // daca primul are mai multe litere atunci nu se va afla in al doilea
    if (strlen(a) > strlen(b)) {
        return false;
    }

    // comparam caracter cu caracter
    for (int i = 0; i < strlen(a); ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

// verificam daca un cuvant face match cu un cuvant din dictionar
// n = numarul de cuvinte din dictionar
int match_in_dictionary(struct dictionary_entry *d, char *cuvant, int n) {
    int poz = -1, i;
    for (i = 0; i < n; ++i) {
        if (it_is_a_match(cuvant, d[i].word)) {
            if (poz == -1 || d[poz].priority < d[i].priority) {
                // daca este primul cuvant cu care face match sau am gasit unul
                // cu prioritate mai mare
                poz = i;
            } else {
                if (d[poz].priority == d[i].priority &&
                    strcmp(d[poz].word, d[i].word) > 0) {
                    // in caz de aceeasi prioritate il luam pe cel mai mic
                    // lexicografic
                    poz = i;
                }
            }
        }
    }
    return poz;
}

int main() {
    int n, m, i, j;
    // n = numarul de cuvinte initial din dictionar
    // m = numarul de cuvinte pentru autocomplete
    scanf("%d", &n);
    char cuvant[21];  // vectorul in care se citesc pe rand cuvintele

    // declaram un pointer de tip dictionary_entry
    struct dictionary_entry *d = malloc(n * sizeof(struct dictionary_entry));

    // adaugam cuvintele in dictionar cu prioritatea 0
    for (int i = 0; i < n; ++i) {
        // citim cuvintele de adaugat in dictionar
        scanf("%s", cuvant);

        // adaugam cuvantele in dictionar
        add(d, cuvant, i, 0);
    }

    scanf("%d", &m);

    for (i = 1; i <= m; ++i) {
        // citim cuvintele pentru autocomplete
        scanf("%s", cuvant);

        // daca e semn de punctuatie il afisam si citim in continuare
        if (strchr(",.:!?", cuvant[0])) {
            printf("%c ", cuvant[0]);
            continue;
        }

        if (cuvant[strlen(cuvant) - 1] != '*') {
            // daca nu e de tip cuvant*
            // varificam daca face match in dictionar
            int poz = match_in_dictionary(d, cuvant, n);

            if (poz == -1) {
                // daca nu face match in dictionar il adaugam
                printf("%s ", cuvant);
                d = realloc(d, (n + 1) * sizeof(struct dictionary_entry));
                add(d, cuvant, n, 1);
                ++n;
            } else {
                // daca face match crestem prioritatea
                d[poz].priority++;
                printf("%s ", d[poz].word);
            }
        } else {
            // daca e de tip cuvant* punem \0 in locul stelutei
            cuvant[strlen(cuvant) - 1] = '\0';
            // verificam daca cuvantul se afla in dictionar
            bool ok = false;
            for (j = 0; j < n; ++j) {
                if (strcmp(d[j].word, cuvant) == 0) {
                    // daca cuvantul se afla in dictionar
                    d[j].priority++;
                    ok = true;
                    break;
                }
            }
            
            // daca cuvantul nu se afla in dictionar il adaugam
            if (!ok) {
                d = realloc(d, (n + 1) * sizeof(struct dictionary_entry));
                add(d, cuvant, n, 1);
                ++n;
            }
            printf("%s ", cuvant);
        }
    }

    return 0;
}
