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
    int count = 30;

    if (read(fp_read, buf, count)) {
        printf("%s\n", buf);
    }
    return 0;
}
