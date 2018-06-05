#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int sockid;
    struct sockaddr_in addrport;
    sockid = socket(AF_INET, SOCK_STREAM, 0);
    if (sockid < 0) {
        printf("Failed to create socket!\n");
        exit(-1);
    }

    addrport.sin_addr = AF_INET;
    addrport.sin_port = htons(5100);
    addrport.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockid, (struct sockaddr *)&addrport, sizeof(addrport)) != -1) {
        printf("Failed to bind the socket!\n");
    }
    return 0;
}
