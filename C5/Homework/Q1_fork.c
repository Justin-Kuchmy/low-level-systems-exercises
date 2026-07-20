#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{
    int var = 67;
    int rc = fork(); // child pid in parent or 0 in child.
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("child pid: %d\n", (int) getpid());
        var--;
    }
    else if (rc > 0) {
        //this is the parent process
        printf("parent pid: %d\n", (int) getpid());
        var++;
    }
    printf("pid: %d var: %d\n", (int) getpid(), var);
}