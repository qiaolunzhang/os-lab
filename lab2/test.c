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

int main()
{
    char* segaddr;
    int segid;
    int size = 512;
    int shmkey = 6000;
    int key = 6001;
    int key2 = 6002;
    int sid1;
    int sid2;
    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    };
    union semun arg1;
    union semun arg2;
    if((sid1=semget(key, 1, 0666|IPC_CREAT))==-1) {
        printf("Error in semget");
        exit(-1);
    }
    if (semctl(sid1, 0, SETVAL, arg1)==-1) {
        printf("Error in semctl");
        exit(-2);

    if((sid2=semget(key2, 1, 0666|IPC_CREAT))==-1) {
        printf("Error in semget");
        exit(-1);
    }
    if (semctl(sid2, 0, SETVAL, arg2)==-1) {
        printf("Error in semctl");
        exit(-2);
    }
    }
    printf("sid1: %i\n", sid1);
    printf("sid2: %i\n", sid2);

    if ((segid=shmget(shmkey, size,
    IPC_CREAT|0666))==-1) {
        printf("Error in shmget");
        exit(-4);
    }
    segaddr=shmat(segid, 0, 0);
    return 0;
}
