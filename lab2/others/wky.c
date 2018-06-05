#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define SHMKEY 18001 /* 共享内存关键字 */
#define SIZE 2048 /* 共享内存长度 */
#define SEMKEY1 19001 /* 信号灯组1关键字 */
#define SEMKEY2 19002 /* 信号灯组2关键字 */

static void semcall(sid,op)
int sid,op;
{
struct sembuf sb;
sb.sem_num = 0;     /* 信号灯编号0 */
sb.sem_op = op;     /* 信号灯操作数加1或减1 */
sb.sem_flg = 0;     /* 操作标志 */
if(semop(sid,&sb,1) == -1)
perror("semop"); /* 出错处理 */
};

int creatsem(key) /* 信号灯组创建及初始化程序 */
key_t key;
{
int sid;
union semun { /* 如sem.h中已定义，则省略 */
int val;
struct semid_ds *buf;
unsigned short *array;
} arg; 
if((sid=semget(key,1,0666|IPC_CREAT))==-1)     /* 创建1个关键字为1的信号灯组,访问控制权限为0666 */
perror("semget"); /* 出错处理 */
arg.val=1;     /* 初值为1 */
if(semctl(sid,0,SETVAL,arg)==-1)     /* 将信号灯组的第一个信号灯的初值置1 */
perror("semctl"); /* 出错处理 */
return(sid);
}

void P(sid)
int sid;
{
semcall(sid,-1); /*对关键字为sid信号灯组值减1，相当于wait */
}

void V(sid)
int sid;
{
semcall(sid,1); /*对关键字为sid信号灯组值加1，相当于signal */
}

int main()
{
char *segaddr;
int segid,sid1,sid2; 
if((segid=shmget(SHMKEY,SIZE,IPC_CREAT|0666))==-1) /* 创建共享内存段 */
perror("shmget"); /* 出错处理 */
segaddr=shmat(segid,0,0); /* 将共享内存映射到进程数据空间 */

sid1=creatsem(SEMKEY1); /* 创建2个信号灯，初值为1 */
sid2=creatsem(SEMKEY2);

P(sid2); /* 置信号灯2值为0，表示缓冲区空 */

if(fork()){
     while(1) {              /* 父进程，输入和存储 */
     FILE *fo1 = fopen("input.txt","a");
     if(fo1){
         P(sid1);
         printf("Input some information: ");
           scanf("%s",segaddr);
         fputs(segaddr,fo1);/* segaddr信息放入fo1 */
         fputc('\n',fo1);/* 换行 */
           V(sid2);
         fclose(fo1);
     }
     else exit(1);
      }
}
else{
      while(1){           /* 子进程，接收和输出 */
     FILE *fo2 = fopen("output.txt","a");
     if(fo2){
         P(sid2);
         fputs(segaddr,fo2);/* segaddr信息放入fo2 */
         fputc('\n',fo2);/* 换行 */
         printf("Received ");
         printf("Received from Parent: %s\n",segaddr);
           V(sid1);
         fclose(fo2);
     }
     else exit(1); 
       }

     }
}
