#include "../tlpi_hdr.h"

int main(int argc, char *argv[]) //number of args and list of args
{
    int j;
    for (j = 0; j < argc; j++)
    printf("argv[%d] = %s\n", j, argv[j]);
    exit(EXIT_SUCCESS);
}