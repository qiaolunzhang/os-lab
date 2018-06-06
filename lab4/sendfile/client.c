#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

char fname[100];
struct sockaddr_in serv_addr;

void gotoxy(int x,int y)
 {
 printf("%c[%d;%df",0x1B,y,x);
 }

int SendFileToServer(int *arg)
{
    int connfd=(int)*arg;
    printf("Connection accepted and id: %d\n",connfd);
    printf("Connected to server: %s:%d\n",inet_ntoa(serv_addr.sin_addr),ntohs(serv_addr.sin_port));
    write(connfd, fname,256);

    printf("the file is %s \n", fname);
    FILE *fp = fopen(fname,"rb");
    if(fp==NULL)
    {
        printf("File opern error");
        return 1;   
    }   

    /* Read data from file and send it */
    while(1)
    {
        /* First read file in chunks of 256 bytes */
        unsigned char buff[1024]={0};
        int nread = fread(buff,1,1024,fp);
        //printf("Bytes read %d \n", nread);        

        /* If read was success, send data. */
        if(nread > 0)
        {
            write(connfd, buff, nread);
            printf("%s", buff);
        }
        if (nread < 1024)
        {
            if (feof(fp))
		    {
                printf("End of file\n");
		        printf("File transfer completed for id: %d\n",connfd);
		    }
            if (ferror(fp)) {
                printf("Error reading\n");
                break;
            }
            return 0;
        }
    }
   return 0;
}

int main(int argc, char *argv[])
{
    system("clear");
    int sockfd = 0;
    char recvBuff[1024];
    memset(recvBuff, '0', sizeof(recvBuff));

    /* Create a socket first */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    /* Initialize sockaddr_in data structure */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); // port
    char ip[50];
    //char fname[100];
    if (argc < 3) 
    {
        printf("Enter IP address to connect: ");
        gets(ip);
        printf("Enter file to send: ");
        gets(fname);
    }
    else {
        strcpy(ip,argv[1]);
        strcpy(fname, argv[2]);
    }

    serv_addr.sin_addr.s_addr = inet_addr(ip);

    /* Attempt a connection */
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
        printf("\n Error : Connect Failed \n");
        return 1;
    }

    printf("Connected to ip: %s : %d\n",inet_ntoa(serv_addr.sin_addr),ntohs(serv_addr.sin_port));

    SendFileToServer(&sockfd);
    close(sockfd);
    shutdown(sockfd, SHUT_WR);
   return 0;
}
