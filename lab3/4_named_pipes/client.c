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
    int fd = open(PATH_NAME, O_RDONLY);
    if (fd<0) {
        printf("open file error");
    }
    char buf[BUF_SIZE];
    memset(buf, '\0', sizeof(buf));
    while (1) {
        int ret = read(fd, buf, sizeof(buf));
        if (ret<0) {
            printf("read end or error\n");
            break;
        }
        printf("%s", buf);
    }
    close(fd);
    return 0;
}
