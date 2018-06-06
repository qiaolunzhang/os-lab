#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXLEN 4096

int main(int argc, char **argv)
{
    int sockid, socket_conn;
    socklen_t client_str_length;
    int message_len;
    char input_message[MAXLEN];
    char receive_message[MAXLEN];
    struct sockaddr_in server_addr, client_addr;
    sockid = socket(AF_INET, SOCK_STREAM, 0);
    if (sockid < 0) {
        printf("Failed to create socket!\n");
        exit(-1);
    }

    server_addr.sin_addr.s_addr = AF_INET;
    server_addr.sin_port = htons(5100);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockid, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Failed to bind the socket!\n");
    }
    if (listen(sockid, 5) < 0) {
        printf("Failed to listen!\n");
        exit(-2);
    }
    printf("Server is waiting...\n");
    client_str_length = sizeof(struct sockaddr_in);
    socket_conn = accept(sockid, (struct sockaddr *)&client_addr, &client_str_length);
    if (socket_conn >= 0) {
        printf("TCP连接成功!\n");
        while (1) {
            fgets(input_message, MAXLEN, stdin);
            message_len = strlen(input_message);
            if (input_message[message_len-1] == '\n') input_message[message_len-1]=0;
            send(socket_conn, input_message, strlen(input_message)+1,0);
            printf("成功发送%d个字节\n", message_len);
            recv(socket_conn, receive_message, MAXLEN, 0);
            printf("接收%ld个字符，为：%s\n", strlen(receive_message), receive_message);
        }
        close(socket_conn);
    } else {
        printf("Failed to accept!\n");
    }
    close(socket_conn);

    return 0;
}
