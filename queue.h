#ifndef __QUEUE__
#define __QUEUE__
#ifndef NULL
#define NULL ((void *) 0)
#endif
typedef struct queue_t
{
   struct queue_t *prev;
   struct queue_t *next;
} queue_t ;
int queue_size (queue_t *queue);
void queue_print (char *name, queue_t *queue, void print_elem (void*));
int queue_append (queue_t **queue, queue_t *elem);
int queue_remove (queue_t **queue, queue_t *elem);
#endif