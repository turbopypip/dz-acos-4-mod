#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    int m;
    if (scanf("%d %d", &n, &m) != 2 || n < 0 || m < 0) {
        return 1;
    }

    int *a = NULL;
    int *t = NULL;
    int size = n * m;

    if (size > 0) {
        a = malloc((size_t)size * sizeof(*a));
        t = malloc((size_t)size * sizeof(*t));
        if (a == NULL || t == NULL) {
            free(a);
            free(t);
            return 1;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (scanf("%d", &a[i * m + j]) != 1) {
                free(a);
                free(t);
                return 1;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            t[j * n + i] = a[i * m + j];
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                printf(" ");
            }
            printf("%d", t[i * n + j]);
        }
        printf("\n");
    }

    free(a);
    free(t);
    return 0;
}
