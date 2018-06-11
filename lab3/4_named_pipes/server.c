#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#define PATH_NAME "./tmp_file"
#define BUF_SIZE 50

int main()
{
    int ret = mkfifo(PATH_NAME, S_IFIFO|0666);
    if (ret==-1) {
        printf("make fifo error\n");
        return 1;
    }

    char buf[BUF_SIZE];
    memset(buf, '\0', sizeof(buf));

    int fd=open(PATH_NAME, O_WRONLY);
    while (1) {
        fgets(buf, sizeof(buf)-1, stdin);
        int ret = write(fd, buf, strlen(buf)+1);
        if (ret<0) {
            printf("write error");
            break;
        }
    }
    close(fd);
    return 0;
}
