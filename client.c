
#include "common.h"

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];

    // Création du socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error("Erreur de création du socket");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Conversion de l'adresse IP
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
        error("Adresse invalide / non supportée");

    // Connexion au serveur
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("Échec de la connexion");

    printf("Connecté au serveur.\n");

    while (1) {
        // Réception du compteur du serveur
        memset(buffer, 0, BUFFER_SIZE);
        read(sock, buffer, BUFFER_SIZE);
        int compteur = atoi(buffer);
        printf("Compteur reçu du serveur : %d\n", compteur);

        // Incrémentation du compteur
        compteur++;
        printf("Compteur incrémenté par le client : %d\n", compteur);

        // Envoi de la mise à jour au serveur
        sprintf(buffer, "%d", compteur);
        send(sock, buffer, strlen(buffer), 0);

        sleep(1); // Attente de 1 seconde
    }

    close(sock);
    return 0;
}
