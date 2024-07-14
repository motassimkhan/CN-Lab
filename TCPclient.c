#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PORT 5600

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr = { .sin_family = AF_INET, .sin_port = htons(PORT) };

    if (sockfd < 0 || connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    char buffer[100];
    int num_bytes = read(sockfd, buffer, sizeof(buffer) - 1);

    if (num_bytes < 0) {
        perror("Read error");
        exit(EXIT_FAILURE);
    }

    buffer[num_bytes] = '\0';
    printf("Message from server: %s\n", buffer);
    close(sockfd);
    return 0;
}
