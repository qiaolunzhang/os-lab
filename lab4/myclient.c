#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXLEN 4096

int main(int argc, char **argc)
{
    int c_socket, conn;
    int len;
    char receive_message[MAXLEN], buf[MAXLEN];
    struct sockaddr_in server_address;
    c_socket = socket(AF_INET, SOCK_STREAM, 0);
}
