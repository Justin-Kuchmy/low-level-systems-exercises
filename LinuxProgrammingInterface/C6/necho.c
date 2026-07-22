#define _GNU_SOURCE
#include "../tlpi_hdr.h"


int main(int argc, char *argv[]) //number of args and list of args
{
    //printing program_invocation_name (errno.h) is the same as argv[0]


    //printing all the arguments
    int j;
    for (j = 0; j < argc; j++)
        printf("argv[%d] = %s\n", j, argv[j]);


    //alternate way
    char **p;
    for (p = argv; *p != NULL; p++)
        puts(*p);

    //printing all the environment variables. we could just puts(*ep) but this shows that getenv is a key value lookup
    char **ep;
    char* result;
    for (ep = environ; *ep != NULL; ep++)
    {

        //hacky form of substring. SHELL=/bin/bash -> SHELL stopping at =
        char *walk = *ep; 
        char *delim = strchr(*ep, '=');
        char name[256];
        int i = 0;
        while(walk != delim) //go from start of the string to the == to just get the key
        {
            name[i] = *walk; //add each letter
            i++;
            walk++; //walk forward
        }
        name[i] = '\0'; //end of string


      
        result = getenv(name); //look up key (SHELL) to get the value (/bin/bash)
        //int setenv(const char *name, const char *value, int overwrite); //also useful to add
        printf("%s=%s\n", name, result);  //results the same way   puts(*ep) would have it 
    }
    exit(EXIT_SUCCESS);
}