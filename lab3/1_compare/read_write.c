#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fp_read;
    int fp_write;
    fp_read = open("original",O_RDWR);
    fp_write = open("modified", O_RDWR);
    char buf[100];
    int count = 100;
    int count_read = 0;

    // 1秒(s) = 1000 000微秒(us)
    struct timeval tv1, tv2;
    struct timezone tz;
    long unsigned int sec, usec;
    time_t time1, time2;

    memset(buf, '\0', sizeof(buf));

    gettimeofday(&tv1, &tz);
    printf("time1sec = %lu\n", tv1.tv_sec);
    printf("time1usec= %lu\n", tv1.tv_usec);

    // 这样子最后一个会有问题，如果没读满，但之前有数据
    while (1) {
        count_read = read(fp_read, buf, count);
        if (count_read>0) {
            write(fp_write, buf, count_read);
        } else {
            break;
        }
    }

    gettimeofday(&tv2, &tz);
    printf("time2sec = %lu\n", tv2.tv_sec);
    printf("time2usec= %lu\n", tv2.tv_usec);

    sec = tv2.tv_sec - tv1.tv_sec;
    usec = tv2.tv_usec - tv1.tv_usec;
    printf("Total sec plus usec is %lu usec\n", usec);

    return 0;
}
