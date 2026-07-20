#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) 
{
    int rc1 = fork();
    
    if (rc1 < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc1 == 0) {
        // child (new process)
        sleep(1);
        printf("child1 pid: %d\n", (int) getpid());
    }
    else {
        //this is the parent process
        int rc2 = fork();
        if (rc2 == 0) {
            // child2
            printf("child2 pid: %d\n", (int) getpid());
        } else {
            // real parent, has 2 children: rc1 and rc2
            waitpid(rc1, NULL, 0);
            waitpid(rc2, NULL, 0);
            printf("parent pid: %d..\t", (int) getpid());
        }

    }
}