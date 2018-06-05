#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>
#include <stdio.h>

struct msg_st
{
    long int msg_type;
    char text[BUFSIZ];
};

int main()
{
    int running = 1;
    int msgid = -1;
    struct msg_st data;
    long int msgtype = 2;

    msgid = msgget((key_t)1111, 0666 | IPC_CREAT);
    if (msgid == -1) {
        printf("msgget fail\n");
        exit(-1);
    }

    while (running)
    {
        if (msgrcv(msgid, (void *)&data, BUFSIZ, msgtype, 0) == -1) {
            puts("msgrcv fail");
            exit(-2);
        }
        printf("rcv data msg_type is %ld\n", data.msg_type);
        printf("content is : %s\n", data.text);
        if (strncmp(data.text, "end", 3) == 0)
            running = 0;
    }

    if (msgctl(msgid, IPC_RMID, 0) == -1) {
        printf("msgctl failed\n");
        exit(-3);
    }
    return 0;
}
