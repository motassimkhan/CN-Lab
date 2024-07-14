#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    struct sockaddr_in sa = { .sin_family = AF_INET, .sin_port = htons(5600), .sin_addr.s_addr = htonl(INADDR_ANY) };
    int sockfd = socket(AF_INET, SOCK_STREAM, 0), conntfd;
    socklen_t len;
    char str[100];
    time_t tick;

    if (sockfd < 0 || bind(sockfd, (struct sockaddr*)&sa, sizeof(sa)) < 0 || listen(sockfd, 50) < 0) {
        perror("Error");
        return 1;
    }

    while (1) {
        len = sizeof(sa);
        if ((conntfd = accept(sockfd, (struct sockaddr*)&sa, &len)) >= 0) {
            tick = time(NULL);
            snprintf(str, sizeof(str), "%s", ctime(&tick));
            write(conntfd, str, strlen(str) + 1);
            close(conntfd);
        }
    }
}
