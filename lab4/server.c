#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#define MAXN 4096 

int main(int argc ,char **argv){
	struct sockaddr_in A ,B ;
	char meg[MAXN] ;
	char rev[MAXN] ;
	socklen_t len;
	int s_socket,socket_conn;
	s_socket = socket(AF_INET,SOCK_STREAM,0);	
	if(s_socket < 0){
		printf("Faile to socket!\n");
		return 1;
	}						
	A.sin_family = AF_INET ;
	if(argv[1]){
		A.sin_port = htons(atoi(argv[1])) ;
	}
		else
	A.sin_port = htons(1234);
	A.sin_addr.s_addr = htonl(INADDR_ANY) ;	
	bind(s_socket ,(struct sockaddr *)&A,sizeof(A));		
	listen(s_socket,5);								
	printf("Server is Waiting ...\n");			
	len = sizeof(struct sockaddr_in) ;	
	socket_conn = accept(s_socket,(struct sockaddr *)&B ,&len);
	if(socket_conn >= 0){
			printf("连接成功，开始通信！\n");
			while(1){										
				fgets(meg,MAXN,stdin);	//inet_ntoa(B.sin_addr);	
				len = strlen(meg);
				if(meg[len-1] == '\n')	meg[len-1] = 0 ;
				send(socket_conn,meg,strlen(meg)+1,0);			
				printf("已经成功发送%d个字节\n",len);
				if(strcmp(meg,"quit") == 0){
					printf("Server is cancelling the communication!\n");
					break ;
				}
				recv(socket_conn,rev,MAXN,0);						
				if(strcmp(rev,"quit")==0){
					printf("Client is cancelling the communication!\n");
					break ;
				}
				printf("成功接受%d个字符，字符为：%s\n",strlen(rev),rev);
	
			}
			close(socket_conn) ;						
	}
	else{
		printf("Faile to aceept!\n");
	}
	close(s_socket);								
	return 0;
}
