#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dictionary_entry {
    char *word;
    int priority;
};

// adaugam un cuvant in dictionar cu prioritatea prio
void add(struct dictionary_entry *d, char *cuvant, int poz, int prio) {
    d[poz].priority = prio;
    d[poz].word = malloc((strlen(cuvant) + 1) * sizeof(char));
    strcpy(d[poz].word, cuvant);
    d[poz].word[strlen(cuvant)] = '\0';
}

// cauti a in prima parte din b
bool it_is_a_match(char *a, char *b) {
    if (strlen(a) > strlen(b)) return false;
    for (int i = 0; i < strlen(a); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

// nu face match cu niciunul din dictionar
int in_dictionary(struct dictionary_entry *d, char *cuvant, int n) {
    int poz = -1;
    for (int i = 0; i < n; ++i) {
        if (it_is_a_match(cuvant, d[i].word)) {
            if (poz == -1 || d[poz].priority < d[i].priority) {
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

// int cmp(struct dictionary_entry *a, struct dictionary_entry *b) {
//     if (strcmp((*a).word, (*b).word) > 0) return 1;
//     if (strcmp((*a).word, (*b).word) < 0) return -1;
//     return 0;
// }

int main() {
    int n;  // cuvinte initial in dictionar
    scanf("%d", &n);
    char cuvant[21];
    struct dictionary_entry *d = malloc(n * sizeof(struct dictionary_entry));

    // adaugam cuvintele in dictionar cu prioritatea 0
    for (int i = 0; i < n; ++i) {
        scanf("%s", cuvant);
        add(d, cuvant, i, 0);
        // printf("cuvant:%s   prio:%d\n", d[i].word, d[i].priority);
    }

    int m;
    scanf("%d", &m);

    for (int i = 1; i <= m; ++i) {
        scanf("%s", cuvant);

        // daca e semn de punctuatie
        if (strchr(",.:!?", cuvant[0])) {
            printf("%c ", cuvant[0]);
            continue;
        }

        // verificam daca e de tip *
        if (cuvant[strlen(cuvant) - 1] != '*') {
            int poz = in_dictionary(d, cuvant, n);
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
            // daca e cu * la final punem \0 in locul stelutei
            cuvant[strlen(cuvant) - 1] = '\0';
            bool ok = false;
            for (int i = 0; i < n; ++i) {
                if (strcmp(d[i].word, cuvant) == 0) {
                    // daca cuvantul se afla in dictionar
                    d[i].priority++;
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

// qsort(d, n, sizeof(struct dictionary_entry), cmp);
    // printf("\n");
    // for (int i = 0; i < n; ++i) {
    //     if(d[i].priority != 0)
    //         printf("cuvant:%s   prio:%d\n", d[i].word, d[i].priority);
    // }
    // printf("%d\n", nr);
