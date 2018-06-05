#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

void func();
int main()
{
    int status;
    pid_t pid;
    signal(SIGUSR1, func);
    if (pid=fork()){
        printf("Parent: will send signal.\n");
        kill(pid, SIGUSR1);
        wait(& status);
        printf("status=%d: Parent finished:\n", status);
    } else {
        sleep(10);
        printf("Child: signal is received.\n");
        exit(0);
    }
    return 0;
}

void func()
{
    printf("It is signal processing function.\n");
}
