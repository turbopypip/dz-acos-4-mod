#include <stdio.h>

void bill(const char *arg)
{
    printf("bill(interposed load-time): %s\n", arg);
}

void sam(double arg)
{
    printf("sam(interposed load-time): arg=%.2f\n", arg);
}

