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
    close(STDOUT_FILENO); //1 is closed so open uses 1 as the fd instead
    int fd = open("Q3_FILE.txt", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
    int rc = fork(); // child pid in parent or 0 in child.
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        dprintf(fd, "child pid: %d\t fd: %d", getpid(), fd);
    }
     else if (rc > 0) {
        //this is the parent process
        char buf[1];
        int bytes_read = 0;
        while(1)
        {
            lseek(fd, 0, SEEK_SET); //set offset to 0
            bytes_read = read(fd, buf, 1); //this changes offset to 1, reading 1 byte
            if (bytes_read > 0) //success reading means child wrote to the file
            {
                lseek(fd, 0, SEEK_END);   // move offset to the end before writing
                dprintf(fd, "\nparent pid: %d\t fd: %d", getpid(), fd);
                break;
            }
        }
     
    }
}