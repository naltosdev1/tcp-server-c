#include <WinSock2.h>
#include <stdio.h>
#include <string.h>

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET server = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(server, (struct sockaddr*)&addr, sizeof(addr));
    listen(server, 1);

    printf("En attente d'un client...\n");
    SOCKET client = accept(server, NULL, NULL);
    printf("Client connecté !\n");

    char buffer[512];
    char message[512];

    while(1) {
        int bytes = recv(client, buffer, sizeof(buffer)-1, 0);
        if(bytes <= 0) break;
        buffer[bytes] = '\0';
        printf("[Client] %s\n", buffer);

        printf("Votre message: ");
        if(!fgets(message, sizeof(message), stdin)) break;

        // enlever '\n'
        size_t len = strlen(message);
        if(len > 0 && message[len-1] == '\n')
            message[len-1] = '\0';

        send(client, message, strlen(message), 0);
    }

    closesocket(client);
    closesocket(server);
    WSACleanup();
    return 0;
}
