#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>

#define MAX_INPUT 1024

struct msg_st
{
    long int msg_type;
    char text[MAX_INPUT];
};

int main()
{
    int running = 1;
    struct msg_st data;
    char buffer[BUFSIZ];
    printf("Buffer size is: %d\n", BUFSIZ);
    printf("MAX_INPUT is: %d\n", MAX_INPUT);
    int msgid = -1;

    msgid = msgget((key_t)1111, 0666 | IPC_CREAT);
    if (msgid == -1) {
        printf("msgget error\n");
        exit(-1);
    }

    while (running) {
        // get the data
        puts("input data: ");
        fgets(buffer, BUFSIZ, stdin);
        data.msg_type = 2;
        strcpy(data.text, buffer);
        if (msgsnd(msgid, (void *)&data, MAX_INPUT, 0) == -1) {
            puts("msgsnd fail\n");
            exit(-2);
        }

        if (strncmp(buffer, "end", 3) == 0)
            running = 0;
        sleep(1);
    }
    puts("exit success");

    return 0;
}
