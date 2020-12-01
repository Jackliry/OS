/*************************************************************************
	> File Name: 2.c
	> Author:siminxu
	> Mail: 
	> Created Time: 2020年12月01日 星期二 08时09分58秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <wait.h>
int main()
{
    int pid1, pid2;
    int fd[2];
    char outdata[100], indata[100];
    if (pipe(fd) < 0) {
        printf("creating pipe error!\n");
        return -1;
    }
    while ((pid1 = fork()) == -1);
    if (pid1 == 0) {
        lockf(fd[1], 1, 0);
        sprintf(outdata, "Child Process pid1 is writing data!\n");
        write(fd[1], outdata, 50);
        sleep(10);
        lockf(fd[1], 0, 0);
        exit(0);
    } else { 
    while ((pid2 = fork()) == -1);
    if (pid2 == 0) {
        lockf(fd[1], 1, 0);
        sprintf(outdata, "Child Process pid2 is writing data!\n");
        write(fd[1], outdata, 50);
        sleep(10);
        lockf(fd[1], 0, 0);
        exit(0);
    } else {
        wait(0);
        read(fd[0], indata, 50);
        printf("%s\n", indata);
        wait(0);
        read(fd[0], indata, 50);
        printf("%s\n", indata);
        close(fd[0]);
        close(fd[1]);
        exit(0);
    }

    }
    return 0;
}
