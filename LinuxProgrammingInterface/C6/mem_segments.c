#include <stdio.h>
#include <stdlib.h>

//memory layout of a process. 


//text segment: machine language instructions. read only.

//init data segment: global variables, and static ones that are already initalized.
//match the lifetime of the program, but static vars are still limited in scope (user init)

//uninit data segment: global and static vars, gets init to 0 when the program starts. bbs (block started by symbol).
//allocation space happens at runtime. (zero init)

//stack:dynamically growing and shrinking which has stack frames. 
//one frame for each function that is called. stores a function's local vars, args, return values.

//heap: memory to be dynamically allocated at run time. 

char globBuf[65536]; /* Uninitialized data segment */
int primes[] = { 2, 3, 5, 7 }; /* Initialized data segment */
static int square(int x) /* Allocated in frame for square() */
{
    int result; /* Allocated in frame for square() */
    result = x * x;
    return result; /* Return value passed via register */  
    
}

static void doCalc(int val) /* Allocated in frame for doCalc() */

{
    printf("The square of %d is %d\n", val, square(val));

    if (val < 1000) {
        int t; /* Allocated in frame for doCalc() */
        
        t = val * val * val;
        printf("The cube of %d is %d\n", val, t);
    }
}
int main(int argc, char *argv[]) /* Allocated in frame for main() */
{
    static int key = 999; /* Initialized data segment */
    static char mbuf[10240000]; /* Uninitialized data segment */
    char *p; /* Allocated in frame for main() */
    
    p = malloc(1024); /* Points to memory in heap segment */
    doCalc(key);
    exit(EXIT_SUCCESS);
}