#include <stdio.h>

static void swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int main(void)
{
    int x;
    int y;
    if (scanf("%d %d", &x, &y) != 2) {
        return 1;
    }

    swap(&x, &y);
    printf("%d %d\n", x, y);
    return 0;
}
