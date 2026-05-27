#include <stdio.h>

void fred(int arg)
{
    printf("fred(interposed link-time): arg=%d\n", arg);
}

void john(int arg)
{
    printf("john(interposed link-time): arg=%d\n", arg);
}

