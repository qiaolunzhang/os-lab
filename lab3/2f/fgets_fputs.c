#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int main()
{
    FILE *fp_read, *fp_write;
    fp_read = fopen("./test.txt", "r"); 
    fp_write = fopen("./test_fgets.txt", "w+");
    if (fp_read == NULL) {
        printf("Cannot open file test.txt\n");
    }
    if (fp_write == NULL) {
        printf("Cannot open file test_fread_fwrite.txt\n");
    }
    char buf[1024];

    memset(buf, '\0', sizeof(buf));

    while (fgets(buf, 1024, fp_read) != NULL) {
        fputs(buf, fp_write);
    }

    fclose(fp_read);
    fclose(fp_write);
    return 0;
}
