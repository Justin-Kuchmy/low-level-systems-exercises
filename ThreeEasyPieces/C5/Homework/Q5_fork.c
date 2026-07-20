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
    int rc = fork(); // child pid in parent or 0 in child.
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        __pid_t w = wait(NULL);
        printf("child pid: %d\t", (int) getpid());
        printf("child calling wait: %d\n", (int)w);
    }
    else {
        //this is the parent process
        __pid_t w = wait(NULL);
        printf("parent pid: %d..\t", (int) getpid());
        printf("waiting on pid(w): %d\t", (int)w);
    }
}