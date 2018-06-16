#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int main()
{
    FILE *fp_read, *fp_write;
    fp_read = fopen("./test.txt", "r"); 
    fp_write = fopen("./test_getc.txt", "w+");
    if (fp_read == NULL) {
        printf("Cannot open file test.txt\n");
    }
    if (fp_write == NULL) {
        printf("Cannot open file test_fread_fwrite.txt\n");
    }
    char buf;


    buf = fgetc(fp_read);
    while (buf != EOF) {
        fputc(buf, fp_write);
        buf = fgetc(fp_read);
    }

    fclose(fp_read);
    fclose(fp_write);
    return 0;
}
