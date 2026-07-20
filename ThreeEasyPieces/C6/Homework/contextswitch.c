#define _GNU_SOURCE
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sched.h>
#include <fcntl.h>
#include <err.h>


int main(int argc, char* argv[])
{
    int parentCPU, childCPU;
    int nloops;
    cpu_set_t set;


    int tube[2];
    int tube2[2];
    pipe(tube);
    pipe(tube2);
    if (argc != 4) {
        fprintf(stderr, "Usage: %s parent-cpu child-cpu nloops\n",
                argv[0]);
        exit(EXIT_FAILURE);
    }

    parentCPU = atoi(argv[1]);
    childCPU = atoi(argv[2]);
    nloops = atoi(argv[3]);

    CPU_ZERO(&set);
    switch (fork()) 
    {
        case -1: /* Error */
            err(EXIT_FAILURE, "fork");

        case 0: /* Child */
            CPU_SET(childCPU, &set);

            if (sched_setaffinity(getpid(), sizeof(set), &set) == -1)
                err(EXIT_FAILURE, "sched_setaffinity");
            printf("child pid %d is currently running on cpu %d\n", getpid(), sched_getcpu());

            for(int i = 0; i < nloops; i++)
            {
                int writeChild = write(tube[1], "hello from child\n", 18);
                char bufChild[18];
                int bytes_read_Child = read(tube2[0], bufChild, sizeof(bufChild));
                bufChild[bytes_read_Child] = '\0';

            }

            exit(0);
        default:  /* Parent */
            CPU_SET(parentCPU, &set);
            struct timeval pt1, pt2;
            

            if (sched_setaffinity(getpid(), sizeof(set), &set) == -1)
                err(EXIT_FAILURE, "sched_setaffinity");
                

            printf("parent pid %d is currently running on cpu %d\n", getpid(), sched_getcpu());;
            gettimeofday(&pt1, NULL);
            for(int j = 0; j < nloops; j++)
            {
                
                char bufParent[18];
                int bytes_read_Parent = read(tube[0], bufParent, sizeof(bufParent));
                bufParent[bytes_read_Parent] = '\0';
                int writtenParent = write(tube2[1], "world from parent\n", 18);
            }
            gettimeofday(&pt2, NULL);
            //wait(NULL);     /* Wait for child to terminate */
            struct timeval pres;
            timersub(&pt2,&pt1, &pres);
            printf("before %ld\tafter %ld\tdiff: %ld \n",pt1.tv_usec, pt2.tv_usec, pres.tv_usec);
            exit(0);
    }
  
}



// if(sched_getaffinity(getpid(), sizeof(set), &set) == 0)
// {
//     printf("Child Bit Mask\t");
//     for (int i = 0; i < 16; i++) {
//         printf("%d", CPU_ISSET(i, &set) ? 1 : 0);
//     }
//     printf("\n");
// }
