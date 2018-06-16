#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PATH_NAME "./tmp_file"                                
#define BUF_SIZE 50

int main()
{
    FILE * fp_write;
    int fd = open(PATH_NAME, O_RDONLY);
    if (fd<0) {
        printf("open file error");
    }
    fp_write = fopen("./client.txt", "w+");
    char buf[BUF_SIZE];
    memset(buf, '\0', sizeof(buf));
    int ret = read(fd, buf, sizeof(buf));
    if (ret<0) {
        printf("read end or error\n");
    }
    printf("%s", buf);
    int len = 0;
    for (len = 0; len < BUF_SIZE; len++) {
        if (buf[len] == '\0')
            break;
    }
    fwrite(buf, sizeof(char), len, fp_write);
    fclose(fp_write);
    close(fd);
    return 0;
}
