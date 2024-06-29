#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

#define MAX_MSG 512
#define PORT 8000

void errExit(char *str) {
    puts(str);
    exit(1);
}

int main() {
    unsigned long t;
    char *st, buffer[MAX_MSG];
    int sockfd, n, cliLen;
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        errExit("Error opening socket");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        errExit("Error in binding");
    }

    cliLen = sizeof(cli_addr);

    n = recvfrom(sockfd, buffer, MAX_MSG, 0, (struct sockaddr*)&cli_addr, &cliLen);
    if (n < 0) {
        errExit("Error receiving message");
    }
    buffer[n] = '\0'; 
    printf("\nMessage received from client: %s", buffer);

    t = time(NULL);
    st = ctime(&t);
    if (st == NULL) {
        errExit("Error getting time");
    }

    strncpy(buffer, st, MAX_MSG);
    n = strlen(buffer); 
    if (sendto(sockfd, buffer, n, 0, (struct sockaddr *)&cli_addr, cliLen) != n) {
        errExit("Error sending time");
    }
    printf("Time sent\n");

    return 0;
}
