#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <unistd.h>

int main() {
    const int LEN = 100;
    int client;
    sockaddr_in server_addr;
    hostent host;
    char message[LEN];
    char received[LEN];

    client = socket(AF_INET, SOCK_STREAM, 0);
    memset((char*) &server_addr, 0, sizeof (server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(10000);

    host = *gethostbyname("192.168.1.13");
    memcpy(&server_addr.sin_addr, host.h_addr, host.h_length);

    if (connect(client, (sockaddr*) &server_addr, sizeof (server_addr)) == -1) {
        printf("\nServer is not ready\n");
        return 1;
    }

    while (true) {
        printf("\nUser: ");
        gets(message);
        int n = write(client, message, strlen(message) + 1);
        if ((strcmp(message, "q") == 0) || (strcmp(message, "Q") == 0)) {
            printf("Wrong place...Socket Closed\n");
            close(client);
            break;
        }
        read(client, received, sizeof (received));
        if ((strcmp(received, "q") == 0) || (strcmp(received, "Q") == 0)) {
            printf("Wrong place...Socket Closed\n");
            close(client);
            return 0;
        } else {
            printf("Server: %s\n", received);
        }
    }
}
