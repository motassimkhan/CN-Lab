#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

#define SRV_IP_ADRS "127.0.0.1"
#define SRV_UDP_PORT 8000
#define MAX_MSG 100

void errExit(char *str) {
    perror(str);
    exit(1);
}

int main() {
    int sockFd;
    struct sockaddr_in srvAdr;
    char txmsg[MAX_MSG];
    char rxmsg[MAX_MSG];
    int n;

    if ((sockFd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        errExit("Can't open datagram socket");
    }

    memset(&srvAdr, 0, sizeof(srvAdr));
    srvAdr.sin_family = AF_INET;
    srvAdr.sin_addr.s_addr = inet_addr(SRV_IP_ADRS);
    srvAdr.sin_port = htons(SRV_UDP_PORT);

    printf("Enter message to send:\n");
    fgets(txmsg, MAX_MSG, stdin);
    txmsg[strcspn(txmsg, "\n")] = '\0'; 

    n = strlen(txmsg) + 1; 
    if (sendto(sockFd, txmsg, n, 0, (struct sockaddr *)&srvAdr, sizeof(srvAdr)) != n) {
        errExit("sendto error");
    }

    n = recv(sockFd, rxmsg, MAX_MSG, 0);
    if (n < 0) {
        errExit("recv error");
    }
    rxmsg[n] = '\0'; 
    printf("Time received from the server: %s\n", rxmsg);

    close(sockFd);

    return 0;
}
