#include <WinSock2.h>
#include <stdio.h>
#include <string.h>

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost

    connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    printf("Connecté au serveur !\n");

    char buffer[512];
    char message[512];

    while(1) {
        printf("Votre message: ");
        if(!fgets(message, sizeof(message), stdin)) break;

        size_t len = strlen(message);
        if(len > 0 && message[len-1] == '\n')
            message[len-1] = '\0';

        send(sock, message, strlen(message), 0);

        int bytes = recv(sock, buffer, sizeof(buffer)-1, 0);
        if(bytes <= 0) break;
        buffer[bytes] = '\0';
        printf("[Serveur] %s\n", buffer);
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
