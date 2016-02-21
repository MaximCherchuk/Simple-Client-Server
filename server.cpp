#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>

int main() {
    const int LEN = 100;
    int server, client;
    sockaddr_in client_addr, server_addr;
    char message[LEN];
    char received[LEN];
    
    server = socket(AF_INET, SOCK_STREAM, 0);
    memset((char*)&server_addr, 0, sizeof (server_addr));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(10000);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(server, (sockaddr*) & server_addr, sizeof (server_addr)) == -1) {
        printf("Bind Failure\n");
    } else {
        printf("Bind Success:<%d>\n", server);
    }
    
    while (true) {
        listen(server, 5);
        socklen_t len = sizeof (sockaddr_in);
        client = accept(server, (sockaddr*) & client_addr, &len);
        if(client != -1) {
            printf("Connection accepted:<%d>\n", client);
        }
        while(true) {
            int n = read(client, received, sizeof (received));
            if ((strcmp(received, "q") == 0) || (strcmp(received, "Q") == 0)) {
                printf("Wrong place...Socket Closed of Client\n");
                close(client);
                break;
            } else {
                printf("\nUser:-%s", received);
            }
            printf("\nServer:-");
            gets(message);
            write(client, message, sizeof (message));
            if ((strcmp(message, "q") == 0) || (strcmp(message, "Q") == 0)) {
                printf("Wrong place...Socket Closed of Client\n");
                close(client);
                break;
            }
        }
    }
    close(server);
    puts("Connection closed");
}