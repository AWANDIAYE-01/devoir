#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// Définition des constantes communes
#define PORT 8080
#define BUFFER_SIZE 1024

// Fonction d'erreur commune
void error(const char *msg) {
    perror(msg);
    exit(1);
}

#endif
