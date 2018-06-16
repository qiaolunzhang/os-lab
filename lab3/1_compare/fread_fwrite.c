#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int main()
{
    FILE *fp_read, *fp_write;
    fp_read = fopen("./test.txt", "r"); 
    fp_write = fopen("./test_fread_fwrite.txt", "w+");
    if (fp_read == NULL) {
        printf("Cannot open file test.txt\n");
    }
    if (fp_write == NULL) {
        printf("Cannot open file test_fread_fwrite.txt\n");
    }
    char buf[1024];
    int count = 1024;
    int count_read = 0;

    struct timeval tv1, tv2;
    struct timezone tz;
    long unsigned int sec, usec;

    memset(buf, '\0', sizeof(buf));

    gettimeofday(&tv1, &tz);
    printf("time1sec = %lu\n", tv1.tv_sec);
    printf("time1usec = %lu\n", tv1.tv_usec);

    while (!feof(fp_read)) {
        count_read = fread(buf, sizeof(char), count, fp_read);
        fwrite(buf, sizeof(char), count_read, fp_write);
    }

    gettimeofday(&tv2, &tz);
    printf("time2sec = %lu\n", tv2.tv_sec);
    printf("time2usec = %lu\n", tv2.tv_usec);

    sec = tv2.tv_sec - tv1.tv_sec;
    usec = tv2.tv_usec - tv1.tv_usec;
    usec = usec + sec * 1000000;
    printf("Total sec plus usec is %lu usec\n", usec);

    fclose(fp_read);
    fclose(fp_write);
    return 0;
}
