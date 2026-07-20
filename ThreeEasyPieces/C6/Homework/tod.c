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

int main(int argc, char* arg[])
{
    int count = 10000;
    int trials = 10;
    double arr[trials];

    for (int i = 0; i < trials; i++)
    {

        struct timeval t1, t2;
        gettimeofday(&t1, NULL);
        
        for (int j = 0; j < count; j++)
        {
            char buf[0];
            int bytes_read = read(STDIN_FILENO, buf, sizeof(buf));
            
            
            if (bytes_read < 0) {
                perror("read failed");
                exit(1);
            }
        }
        
        gettimeofday(&t2, NULL);
        struct timeval res;
        timersub(&t2,&t1, &res);
        printf("before %ld\tafter %ld\tdiff: %ld \n",t1.tv_usec, t2.tv_usec, res.tv_usec);
        double cost = (double) (res.tv_sec * 1000000 + res.tv_usec) / count;
        arr[i] = cost;
        
    }
    double sum = 0.0; 
    int size = (sizeof(arr) / sizeof(double));
    for (int k = 0; k < size; k++)
    {
        sum+= arr[k];
    }
    printf("avg cost per syscall: %f microseconds\n", sum/trials);
};