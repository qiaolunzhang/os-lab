#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main()
{
    FILE *fp_read, *fp_write;
    int pipe_fd[2];
    int ret=pipe(pipe_fd);

    fp_read = fopen("./parent.txt", "r");
    fp_write = fopen("./child.txt", "w+");
    if (fp_read == NULL) {
        printf("Cannot open file parent.txt");
    }
    if (fp_write == NULL) {
        printf("Cannot open file child.txt");
    }
    if(ret<0) {
        perror("pipe\n");
    }

    pid_t id=fork();
    if(id<0) {
        perror("fork\n");
    } 
    else if(id==0)  {
        // child
        close(pipe_fd[1]);
        char mesg_receive[100];
        memset(mesg_receive,'\0',sizeof(mesg_receive));
        read(pipe_fd[0],mesg_receive,sizeof(mesg_receive));
        fwrite(mesg_receive, 1, sizeof(mesg_receive), fp_write);
        fclose(fp_write);
    }
    else  {
        // 父进程，关闭读端
        close(pipe_fd[0]);
        char mesg_send[100];
        int  count_read;
        memset(mesg_send, '\0', sizeof(mesg_send));

        count_read = fread(mesg_send, sizeof(char), 1024, fp_read);
        while (count_read > 0) {
            write(pipe_fd[1], mesg_send, strlen(mesg_send));
            //printf("%s", mesg_send);
            count_read = fread(mesg_send, sizeof(char), 1024, fp_read);
            sleep(1);
        }
        fclose(fp_read);
    }

    return 0;
}
