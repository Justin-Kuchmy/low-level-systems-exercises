#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

int main(int argc, char *argv[]) 
{
    int rc = fork(); // child pid in parent or 0 in child.
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("this shoudlnt run: %d\t ", getpid());
        char *args[] = {strdup("ls"), strdup("."), NULL};
        execv("/bin/ls", args); //char *args[];
        //execvp("ls", args); //char *args[];
        //execve("/bin/ls", args, environ); //needs extern environ
        //const char *args2[] = {strdup("ls"), strdup(".")};
        //execl("/bin/ls", args2[0], args2[1], NULL); //const char *args2[3];
        //execlp("ls", args2[0], args2[1], NULL);
        //execle("/bin/ls", args2[0], args2[1], NULL, environ); //needs extern environ
        
        printf("this shoudlnt either: %d\t ", getpid());

    }
     else if (rc > 0) {
        wait(NULL);
        printf("finished...\n");
    }
}