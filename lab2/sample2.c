#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

void func();

int main(int argc, char const *argv[])
{
    int status;
    pid_t pid;
    signal(SIGUSR1, func);
    pid = fork();
    if (pid) {
        printf("Parent: will send the signal.\n");
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

void func() {
    printf("It is signal processing function.\n");
}
