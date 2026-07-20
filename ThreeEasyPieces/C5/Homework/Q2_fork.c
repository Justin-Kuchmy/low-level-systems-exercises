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
    close(STDOUT_FILENO);
    int fd = open("Q2_FILE.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    int rc = fork(); // child pid in parent or 0 in child.
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("child pid: %d\t fd: %d\n", (int) getpid(), fd);
    }
    else {
        //this is the parent process
        printf("parent pid: %d\t fd: %d\n", (int) getpid(), fd);
    }
}