#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
int sfd,dfd,n,chan[2];
char buff[1024];
 
sfd= open("in.txt",O_RDONLY,0644);
dfd=open("out.txt",O_WRONLY|O_CREAT|O_TRUNC,0644);
pipe(chan);	//open a pipe

pid_t id = fork();
if(id == 0) {	//start a child process to send file
	close(chan[1]);
	read(chan[0],buff,1024);
	write(dfd,buff,strlen(buff));
}
else {		
    //in father process, receive file
    while((n=read(sfd,buff,1024))>0) {
		close(chan[0]);
		write(chan[1],buff,n);
	}
}

close(sfd);
close(dfd);
return 0;
}
