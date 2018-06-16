#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
int fd_src,fd_dst,n,chan[2];
char buff[1024];
 
fd_src= open("in_file.txt",O_RDONLY,0644);
fd_dst=open("out_file.txt",O_WRONLY|O_CREAT|O_TRUNC,0644);
pipe(chan);	//open a pipe

pid_t id = fork();
if(id == 0) {	//start a child process to send file
	close(chan[1]);
	read(chan[0],buff,1024);
	write(fd_dst,buff,strlen(buff));
}
else {		
    //in father process, receive file
    while((n=read(fd_src,buff,1024))>0) {
		close(chan[0]);
		write(chan[1],buff,n);
	}
}

close(fd_src);
close(fd_dst);
return 0;
}
