#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define TARGET_IP "127.0.0.1" // Adresse IP cible
#define START_PORT 0          // Port de départ
#define END_PORT 3000         // Port de fin

int main() {
    int sock;
    struct sockaddr_in target_addr;

    // Initialisation de l'adresse cible
    memset(&target_addr, 0, sizeof(target_addr));
    target_addr.sin_family = AF_INET;
    target_addr.sin_addr.s_addr = inet_addr(TARGET_IP);

    printf("Scan des ports TCP ouverts sur %s (de %d à %d)...\n", TARGET_IP, START_PORT, END_PORT);

    for (int port = START_PORT; port <= END_PORT; port++) {
        // Création d'un socket
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            perror("Erreur de création du socket");
            exit(EXIT_FAILURE);
        }

        // Configuration du port cible
        target_addr.sin_port = htons(port);

        // Tentative de connexion
        if (connect(sock, (struct sockaddr *)&target_addr, sizeof(target_addr)) == 0) {
            printf("Port ouvert : %d\n", port);
        }

        // Fermeture du socket
        close(sock);
    }

    printf("Scan terminé.\n");
    return 0;
}
