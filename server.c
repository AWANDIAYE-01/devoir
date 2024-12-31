
#include "common.h"

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int compteur = 0; // Initialisation du compteur
    char buffer[BUFFER_SIZE];

    // Création du socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        error("Erreur de création du socket");

    // Configuration de l'adresse du serveur
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Liaison du socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
        error("Erreur de liaison (bind)");

    // Écoute des connexions
    if (listen(server_fd, 3) < 0)
        error("Erreur d'écoute (listen)");

    printf("Serveur en attente de connexion...\n");

    // Acceptation d'une connexion client
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        error("Erreur d'acceptation (accept)");

    printf("Client connecté.\n");

    while (1) {
        // Envoi du compteur au client
        sprintf(buffer, "%d", compteur);
        send(new_socket, buffer, strlen(buffer), 0);
        printf("Compteur envoyé au client : %d\n", compteur);

        // Réception de la mise à jour du compteur
        memset(buffer, 0, BUFFER_SIZE);
        read(new_socket, buffer, BUFFER_SIZE);
        compteur = atoi(buffer);
        printf("Compteur reçu du client : %d\n", compteur);

        // Incrémentation du compteur
        compteur++;
        printf("Compteur incrémenté par le serveur : %d\n", compteur);

        sleep(1); // Attente de 1 seconde
    }

    close(new_socket);
    close(server_fd);
    return 0;
}