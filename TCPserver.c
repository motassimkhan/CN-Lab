#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    struct sockaddr_in sa, cli;
    int sockfd, conntfd;
    socklen_t len;
    char str[100];
    time_t tick;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(1);
    }

    bzero(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(5600);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr*)&sa, sizeof(sa)) < 0) {
        perror("Error in binding");
        close(sockfd);
        exit(1);
    }

    if (listen(sockfd, 50) < 0) {
        perror("Error in listen");
        close(sockfd);
        exit(1);
    }

    for (;;) {
        len = sizeof(cli);
        conntfd = accept(sockfd, (struct sockaddr*)&cli, &len);
        if (conntfd < 0) {
            perror("Error in accept");
            continue;
        }

        tick = time(NULL);
        snprintf(str, sizeof(str), "%s", ctime(&tick));
        write(conntfd, str, strlen(str) + 1);

        close(conntfd);
    }

    close(sockfd);
    return 0;
}
