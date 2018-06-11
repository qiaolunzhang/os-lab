#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main()
{
int _pipe[2];
int ret=pipe(_pipe);
if(ret<0) {
    perror("pipe\n");
}

pid_t id=fork();
if(id<0) {
    perror("fork\n");
} 
else if(id==0)  {
    // child
    close(_pipe[0]);
    int i=0;
    char *mesg=NULL;
    while(i<100) {
        mesg="I am child";
        write(_pipe[1],mesg,strlen(mesg)+1);
        sleep(1);
        ++i;
    }
}
else  {
    close(_pipe[1]);
    int j=0;
    char _mesg[100];
    while(j<100) {
        memset(_mesg,'\0',sizeof(_mesg ));
        read(_pipe[0],_mesg,sizeof(_mesg));
        printf("%s\n",_mesg);
        j++;
    }
}

return 0;
}
