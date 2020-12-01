/*************************************************************************
	> File Name: 3.c
	> Author:siminxu
	> Mail: 
	> Created Time: 2020年12月01日 星期二 09时09分41秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
int main()
{
    int shmid;
    char *shmptr;
    key_t key = 1234;
    pid_t pid;
    pid = fork();
    if (pid == 0)
    {
        shmid = shmget(key, 1024, 0600|IPC_CREAT);
        shmptr = (char *)shmat(shmid, 0, 0);
        printf("content:%s\n", shmptr);
        shmctl(shmid, IPC_RMID, 0);
        printf("Child sleep 2s\n");
        sleep(2);
        exit(0);
    } else {
        shmid = shmget(key, 1024, 0600|IPC_CREAT|IPC_EXCL);
        shmptr = (char *)shmat(shmid, 0, 0);
        memcpy(shmptr, "hello world", sizeof("hello world"));
        printf("parent sleep 2s\n");
        sleep(2);
        exit(0);
    }
    return 0;
}
