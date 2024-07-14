#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    struct hostent *h;
    char dom[50];
    printf("enter the domain name: ");
    scanf("%s",&dom);
    if (dom == NULL) {
        printf("Error: field cannot be empty");
        exit(1);
    }

    if ((h = gethostbyname(dom)) == NULL) {
        perror("gethostbyname");
        exit(1);
    }

    printf("Host name : %s\n", h->h_name);
    printf("IP Address : %s\n", inet_ntoa(*((struct in_addr *)h->h_addr)));

    return 0;
}
