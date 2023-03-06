#include "queue.h"
// Arthur Silva Maloyama- 082190039
// Victor Assagra- 082190021
int queue_size(queue_t *queue)
{
  int size = 0;
  queue_t *current = queue;
  while (current != NULL)
  {
    size++;
    current = current->next;
    if (current == queue)
      break; // evita loop infinito
  }
  return size;
}

void queue_print(char *name, queue_t *queue, void print_elem(void *))
{
  printf("%s: [", name);
  queue_t *current = queue;
  while (current != NULL)
  {
    print_elem(current);
    current = current->next;
    if (current != NULL)
      printf(" ");
    if (current == queue)
      break; // evita loop infinito
  }
  printf("]\n");
}

int queue_append(queue_t **queue, queue_t *elem)
{
  if (queue == NULL || elem == NULL)
    return -1;
  if (elem->next != NULL || elem->prev != NULL)
    return -1; // ele já está em outra fila
  if (*queue == NULL)
  {
    *queue = elem;
    elem->next = elem->prev = elem;
  }
  else
  {
    elem->prev = (*queue)->prev;
    elem->next = *queue;
    (*queue)->prev->next = elem;
    (*queue)->prev = elem;
  }
  return 0;
}

int queue_remove(queue_t **queue, queue_t *elem)
{
  if (queue == NULL || elem == NULL)
    return -1;
  if (*queue == NULL)
    return -1; // fila vazia
  if (elem->next == NULL || elem->prev == NULL)
    return -1; // ele não está em nenhuma fila
  if (elem->next == elem || elem->prev == elem)
  { // elem é o único na fila
    if (*queue != elem)
      return -1; // ele não pertence à fila indicada
    *queue = NULL;
  }
  else
  {
    if (elem->prev->next != elem || elem->next->prev != elem)
      return -1; // ele não pertence à fila indicada
    elem->prev->next = elem->next;
    elem->next->prev = elem->prev;
    if (*queue == elem)
      *queue = elem->next; // atualiza início da fila
  }
  elem->prev = elem->next = NULL;
  return 0;
}