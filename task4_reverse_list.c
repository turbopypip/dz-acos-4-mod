#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

static Node *reverse_list(Node *head)
{
    Node *prev = NULL;
    while (head != NULL) {
        Node *next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

int main(void)
{
    Node *head = NULL;
    Node *tail = NULL;

    while (1) {
        int x;
        if (scanf("%d", &x) != 1) {
            free_list(head);
            return 1;
        }
        if (x == 0) {
            break;
        }

        Node *node = malloc(sizeof(*node));
        if (node == NULL) {
            free_list(head);
            return 1;
        }
        node->value = x;
        node->next = NULL;

        if (tail == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    head = reverse_list(head);

    Node *cur = head;
    int first = 1;
    while (cur != NULL) {
        if (!first) {
            printf(" ");
        }
        printf("%d", cur->value);
        first = 0;
        cur = cur->next;
    }
    printf("\n");

    free_list(head);
    return 0;
}
