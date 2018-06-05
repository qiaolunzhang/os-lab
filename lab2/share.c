#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SHMKEY 18001
#define SIZE 1024
#define SEMKEY1 19001
#define SEMKEY2 19002


int creatsem(key_t key)
{
    int sid;
    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    } arg;
    if((sid=semget(key, 1, 0666|IPC_CREAT))==-1) {
        printf("Error in semget");
        exit(-1);
    }
    arg.val = 1;
    if (semctl(sid, 0, SETVAL, arg)==-1) {
        printf("Error in semctl");
        exit(-2);
    }
    return sid;
}

static void semcall(int sid, int op)
{
    struct sembuf sb;
    sb.sem_num= 0;
    sb.sem_op = op;
    sb.sem_flg = 0;
    if(semop(sid, &sb, 1)==-1) {
        printf("Error in semop");
        exit(-3);
    }
}

void P(int sid)
{
    semcall(sid, -1);
}

void V(int sid)
{
    semcall(sid, 1);
}

int main()
{
    char *segaddr;
    int segid, sid1, sid2;

    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    } arg;

    if ((segid=shmget(SHMKEY, SIZE,
    IPC_CREAT|0666))==-1) {
        printf("Error in shmget");
        exit(-4);
    }
    segaddr=shmat(segid, 0, 0);

    sid1 = creatsem(SEMKEY1);
    sid2 = creatsem(SEMKEY2);
    P(sid2);

    if (!fork()) {
        while (1) {
        // The child
            FILE *f1 = fopen("outpu.txt", "a");
            P(sid2);
            fputs(segaddr, f1);
            fputc('\n', f1);
            printf("Received from Parent: %s\n", segaddr);
            V(sid1);
            fclose(f1);
        }
    } else {
        while (1) {
        // The parent
        P(sid1);
        printf("Input some text: ");
        scanf("%s", segaddr);
        V(sid2);
        }
    }

    return 0;
}
