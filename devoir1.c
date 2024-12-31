#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void usage(const char *prog_name) {
    printf("Usage : %s -f <entier> | -g <entier> | -f <entier> -g | -g <entier> -f\n", prog_name);
    exit(EXIT_FAILURE);
}

int f(int n) {
    return pow(2, n); // 2^n
}

int g(int n) {
    return 2 * n; // 2*n
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        usage(argv[0]);
    }

    int n = 0, f_flag = 0, g_flag = 0;
    int f_result = 0, g_result = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            if (i + 1 < argc) {
                n = atoi(argv[++i]);
                f_result = f(n);
                f_flag = 1;
            } else {
                fprintf(stderr, "Erreur : L'option -f nécessite un entier.\n");
                usage(argv[0]);
            }
        } else if (strcmp(argv[i], "-g") == 0) {
            if (i + 1 < argc) {
                n = atoi(argv[++i]);
                g_result = g(n);
                g_flag = 1;
            } else {
                fprintf(stderr, "Erreur : L'option -g nécessite un entier.\n");
                usage(argv[0]);
            }
        }
    }

    if (f_flag && g_flag) {
        // Composition de fonctions
        if (strcmp(argv[1], "-f") == 0) {
            printf("fog(%d) = f(g(%d)) = %d\n", n, n, f(g_result));
        } else if (strcmp(argv[1], "-g") == 0) {
            printf("gof(%d) = g(f(%d)) = %d\n", n, n, g(f_result));
        }
    } else if (f_flag) {
        printf("f(%d) = 2^%d = %d\n", n, n, f_result);
    } else if (g_flag) {
        printf("g(%d) = 2*%d = %d\n", n, n, g_result);
    } else {
        fprintf(stderr, "Erreur : Options invalides.\n");
        usage(argv[0]);
    }

    return 0;
}
