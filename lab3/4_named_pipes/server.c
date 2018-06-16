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
    FILE *fp_read;
    int count_read;
    int ret = mkfifo(PATH_NAME, S_IFIFO|0666);
    if (ret==-1) {
        printf("make fifo error\n");
        return 1;
    }

    fp_read = fopen("./server.txt", "r");
    if (fp_read == NULL) {
        printf("Cannot open file server.txt");
    }

    char buf[BUF_SIZE];
    memset(buf, '\0', sizeof(buf));

    int fd=open(PATH_NAME, O_WRONLY);
    count_read = fread(buf, sizeof(char), 1024, fp_read);
    while (count_read > 0) {
        int ret = write(fd, buf, strlen(buf));
        if (ret<0) {
            printf("write error");
            break;
        }
        count_read = fread(buf, sizeof(char), 1024, fp_read);
    }
    close(fd);
    return 0;
}
