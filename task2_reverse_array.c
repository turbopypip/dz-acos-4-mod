#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1 || n < 0) {
        return 1;
    }

    int *arr = NULL;
    if (n > 0) {
        arr = malloc((size_t)n * sizeof(*arr));
        if (arr == NULL) {
            return 1;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }

    for (int i = 0, j = n - 1; i < j; ++i, --j) {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    for (int i = 0; i < n; ++i) {
        printf(i == 0 ? "%d" : " %d", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}
