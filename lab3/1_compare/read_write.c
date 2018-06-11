#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
    int fp_read;
    int fp_write;
    fp_read = open("original",O_RDWR);
    char buf[100];
    int count = 100;

    // 这样子最后一个会有问题，如果没读满，但之前有数据
    while (read(fp_read, buf, count)) {
        printf("%s", buf);
    }

    return 0;
}
