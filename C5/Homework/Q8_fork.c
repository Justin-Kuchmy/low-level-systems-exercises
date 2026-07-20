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
    
    int fds[2];
    pipe(fds);
    int rc1 = fork();
    
    if (rc1 < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc1 == 0) {
        // child (new process)
        int written = write(fds[1], "hello\n", 6);
        if (written < 0) {
            perror("write failed");
        } else {
            printf("child A write: %d bytes\n", written);
        }
        exit(0);
    }
    else {
        //this is the parent process
        int rc2 = fork();
        if (rc2 < 0) {
            // fork failed
            fprintf(stderr, "fork failed\n");
            exit(1);
        }
        else if (rc2 == 0) {
            char buf[6];
            int bytes_read = read(fds[0], buf, sizeof(buf));
            if (bytes_read < 0) {
                perror("read failed");
                exit(1);
            }
            buf[bytes_read] = '\0';
            printf("child B read: %s\n", buf);
            exit(0);
        } else {
            wait(NULL);
            printf("parent pid: %d..\t", (int) getpid());
            exit(0);
        }

    }
}