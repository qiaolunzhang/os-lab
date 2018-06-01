#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    pid_t fpid;
    int count = 0;
    fpid = fork();
    if (fpid < 0)
        printf("error in fork!");
    else if (fpid == 0) {
        printf("i am the child process, my process id is %d\n", getpid());
        count++;
    }
    else {
        printf("i am the parent process, my process id is %d\n", getpid());
        count++;
    }
    printf("The count is %d\n", count);
    return 0;
}
