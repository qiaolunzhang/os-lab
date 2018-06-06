/* Compile:
** gcc -pthread server.c -o server
*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>


struct sockaddr_in c_addr;
char fname[100];

int main(int argc, char *argv[])
{
    int bytesReceived = 0;
    char recvBuff[1024];
    int connfd = 0;
    struct sockaddr_in serv_addr;
    int listenfd = 0,ret;
    size_t clen=0;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd<0)
	{
	  printf("Error in socket creation\n");
	  exit(2);
	}

    printf("Socket retrieve success\n");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    ret=bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
    if(ret<0)
    {
      printf("Error in bind\n");
      exit(2);
    }

    if(listen(listenfd, 10) == -1)
    {
        printf("Failed to listen\n");
        return -1;
    }

    if (argc < 2) 
    {
	    printf("Enter file name to send: ");
        gets(fname);
    }
    else
        strcpy(fname,argv[1]);

    while(1)
    {
        clen=sizeof(c_addr);
        printf("Waiting...\n");
        connfd = accept(listenfd, (struct sockaddr*)&c_addr,&clen);
        if(connfd<0)
        {
	        printf("Error in accept\n");
	        continue;	
	    }
	    read(connfd, fname, 256);
	    printf("File Name: %s\n",fname);
	    printf("Receiving file...");
   	    FILE *fp = fopen(fname, "ab"); 
        if(NULL == fp)
        {
            printf("Error opening file");
            return 1;
        }
    // Receive data in chunks of 256 bytes 
        while((bytesReceived = read(connfd, recvBuff, 1024)) > 0)
        { 
            fwrite(recvBuff, 1,bytesReceived,fp);
        }

        if(bytesReceived < 0)
        {
            printf("\n Read Error \n");
        }
        printf("\nFile OK....Completed\n");
        fclose(fp);
    }
    close(connfd);
    return 0;
}
