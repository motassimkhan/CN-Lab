#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PORT 5600
#define BUFFER_SIZE 100

int main() {
    struct sockaddr_in server_addr;
    int sockfd, num_bytes;
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully\n");

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }
    printf("Connected to server\n");

    if ((num_bytes = read(sockfd, buffer, sizeof(buffer))) < 0) {
        perror("Error reading from socket");
        exit(EXIT_FAILURE);
    }
    buffer[num_bytes] = '\0'; 

    printf("Message from server: %s\n", buffer);
    close(sockfd);
    return 0;
}
