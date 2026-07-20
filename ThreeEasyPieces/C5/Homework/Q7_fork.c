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
     //1 is closed so open uses 1 as the fd instead
    open("Q7_FILE.txt", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
    int rc = fork(); // child pid in parent or 0 in child.
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("child pid: %d\t", getpid());
    }
     else if (rc > 0) {
        close(STDOUT_FILENO);
        printf("\ntest out"); //if stdout is closed, this wont print and we error
        fflush(stdout);  
        if (ferror(stdout)) {
            dprintf(2, "printf ultimately failed\n");
        }
        else
        {
            printf("\nparent pid: %d\t", getpid());
        }

    }
}