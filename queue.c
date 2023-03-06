// Claus Alberto Bienemann --> 082190024
// Guilherme Costa Santiago --> 082190004

#include "queue.h"

int queue_size(queue_t *q) {
    int s = 0;
    queue_t *c = q;
    while (c != NULL) {
        s++;
        c = c->next;
        if (c == q) break;
    }
    return s;
}

void queue_print(char *n, queue_t *q, void print_elem(void *)) {
    printf("%s: [", n);
    queue_t *c = q;
    while (c != NULL) {
        print_elem(c);
        c = c->next;
        if (c != NULL) printf(" ");
        if (c == q) break;
    }
    printf("]\n");
}

int queue_append(queue_t **q, queue_t *e) {
    if (q == NULL || e == NULL) return -1;
    if (e->next != NULL || e->prev != NULL) return -1;
    if (*q == NULL) {
        *q = e;
        e->next = e->prev = e;
    }
    else {
        e->prev = (*q)->prev;
        e->next = *q;
        (*q)->prev->next = e;
        (*q)->prev = e;
    }
    return 0;
}

int queue_remove(queue_t **q, queue_t *e) {
    if (q == NULL || e == NULL) return -1;
    if (*q == NULL) return -1;
    if (e->next == NULL || e->prev == NULL) return -1;
    if (e->next == e || e->prev == e) {
        if (*q != e)
            return -1;
        *q = NULL;
    }
    else {
        if (e->prev->next != e || e->next->prev != e) return -1;
        e->prev->next = e->next;
        e->next->prev = e->prev;
        if (*q == e) *q = e->next;
    }
    e->prev = e->next = NULL;
    return 0;
}