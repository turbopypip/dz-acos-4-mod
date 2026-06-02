#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define THREAD_COUNT 4

typedef struct {
    int *array;
    int left;
    int right;
} ThreadData;

static long long sum = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void *worker(void *arg)
{
    ThreadData *data = arg;
    long long part_sum = 0;

    for (int i = data->left; i < data->right; ++i) {
        part_sum += data->array[i];
    }

    pthread_mutex_lock(&mutex);
    sum += part_sum;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(void)
{
    int n;

    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    int *array = malloc((size_t)n * sizeof(*array));
    if (array == NULL) {
        return 1;
    }

    srand(1);
    for (int i = 0; i < n; ++i) {
        array[i] = rand() % 100;
    }

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", array[i]);
    }
    printf("\n");

    pthread_t threads[THREAD_COUNT];
    ThreadData data[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; ++i) {
        data[i].array = array;
        data[i].left = n * i / THREAD_COUNT;
        data[i].right = n * (i + 1) / THREAD_COUNT;

        if (pthread_create(&threads[i], NULL, worker, &data[i]) != 0) {
            free(array);
            return 1;
        }
    }

    for (int i = 0; i < THREAD_COUNT; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("%lld\n", sum);

    pthread_mutex_destroy(&mutex);
    free(array);
    return 0;
}
