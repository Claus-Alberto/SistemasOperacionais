#if defined(_WIN32) || (!defined(__unix__) && !defined(__unix) && (!defined(__APPLE__) || !defined(__MACH__)))
#warning Este código foi planejado para ambientes UNIX (LInux, *BSD, MacOS). A compilação e execução em outros ambientes é responsabilidade do usuário.
#endif
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include "queue.c"
#define N 100
typedef struct filaint_t
{
   struct filaint_t *prev; 
   struct filaint_t *next; 
   int id;

} filaint_t;
filaint_t item[N];
filaint_t *fila0, *fila1, *aux, *final;
int ret;
void print_elem (void *ptr)
{
   filaint_t *elem = ptr;
   if (!elem)
      return;
   elem->prev ? printf ("%d", elem->prev->id) : printf ("*");
   printf ("<%d>", elem->id);
   elem->next ? printf ("%d", elem->next->id) : printf ("*");
}
int fila_correta (filaint_t *fila)
{
   filaint_t *aux;
   if (!fila)
      return 1;
   if ((fila->next == fila) && (fila->prev == fila))
      return 1;
   if ((fila->next == fila) || (fila->prev == fila))
   {
      printf ("ERRO: ponteiros errados na fila com um elemento\n");
      return 0;
   }
   aux = fila;
   do
   {
      if (aux->next && (aux->next->prev == aux))
        ;
      else
      {
         printf ("ERRO: ponteiros errados ->next ou ->next->prev\n");
         return 0;
      }
      if (aux->prev && (aux->prev->next == aux))
        ;
      else
      {
         printf ("ERRO: ponteiros errados ->prev ou ->prev->next\n");
         return 0;
      }
      aux = aux->next;
   }
   while (aux != fila);
   return 1;
}
int main (int argc, char **argv, char **envp)
{
   int i;
   for (i=0; i<N; i++)
   {
      item[i].id = i;
      item[i].prev = NULL;
      item[i].next = NULL;
   }
   printf ("Testando insercao de %d elementos...\n", N);
   fila0 = NULL;
   for (i=0; i<N; i++)
   {
      assert (queue_size ((queue_t*) fila0) == i);
      queue_append ((queue_t **) &fila0, (queue_t*) &item[i]);
      assert (fila_correta (fila0));
   }
   printf ("Testando tamanho da fila e ordem dos %d elementos...\n", N);
   aux = fila0;
   i=0;
   do
   {
      assert (i == aux->id);
      i++;
      aux = aux->next;
   } while (aux != fila0);
   assert (i == N);
   assert (queue_size ((queue_t*) fila0) == N);
   printf ("Testes de insercao funcionaram!\n");
   printf ("Remocao %d vezes o primeiro elemento...\n", N);
   i=0;
   while (i<N)
   {
      aux = fila0;
      queue_remove ((queue_t**) &fila0, (queue_t*) aux);
      assert (fila_correta (fila0)); 
      assert (aux->id == i);           
      assert (aux->prev == NULL);      
      assert (aux->next == NULL);      
      i++;
   }
   assert (fila0 == NULL);            
   printf ("Ok, apos %d remocoes a fila ficou vazia\n", N);
   fila0 = NULL;
   for (i=0; i<N; i++)
      queue_append ((queue_t**) &fila0, (queue_t*) &item[i]);
   printf ("Remocao %d vezes o segundo elemento...\n", N);
   i=0;
   while (i<N)
   {
      aux = fila0->next;
      queue_remove ((queue_t**) &fila0, (queue_t*) aux);
      assert (fila_correta (fila0)); 
      assert (aux->id == ((i+1)%N));   
      assert (aux->prev == NULL);      
      assert (aux->next == NULL);      
      i++;
   }
   assert (fila0 == NULL);            
   printf ("Ok, apos %d remocoes a fila ficou vazia\n", N);
   fila0 = NULL;
   for (i=0; i<N; i++)
      queue_append ((queue_t**) &fila0, (queue_t*) &item[i]);
   printf ("Remocao %d vezes o último elemento...\n", N);
   i=0;
   while (i<N)
   {
      aux = fila0->prev;
      queue_remove ((queue_t**) &fila0, (queue_t*) aux);
      assert (fila_correta (fila0)); 
      assert (aux->id+i == N-1);       
      assert (aux->prev == NULL);      
      assert (aux->next == NULL);      
      i++;
   }
   assert (fila0 == NULL);            
   printf ("Ok, apos %d remocoes a fila ficou vazia\n", N);
   fila0 = NULL;
   for (i=0; i<N; i++)
      queue_append ((queue_t**) &fila0, (queue_t*) &item[i]);
   printf ("Remocao %d vezes um elemento aleatório...\n", N);
   while (fila0)
   {
      i = rand() % queue_size ((queue_t*) fila0);
      aux = fila0;
      while (i)
      {
         i--;
         aux = aux->next;
      }
      queue_remove ((queue_t**) &fila0, (queue_t*) aux);
   }
   assert (fila0 == NULL);            
   printf ("Ok, apos %d remocoes aleatorias a fila ficou vazia\n", N);
   printf ("Testes de remocao funcionaram!\n");
   for (i=0; i<N; i++)
   {
      item[i].id = i;
      item[i].prev = NULL;
      item[i].next = NULL;
   }
   fila0 = NULL;
   fila1 = NULL;
   queue_append ((queue_t**) &fila0, (queue_t*) &item[0]);
   queue_append ((queue_t**) &fila1, (queue_t*) &item[1]);
   printf ("Testando remocao de elemento que está em outra fila...\n");
   queue_remove ((queue_t**) &fila0, (queue_t*) &item[1]);
   assert (fila0 == &item[0]);
   assert (item[0].prev == &item[0]);
   assert (item[0].next == &item[0]);
   assert (item[1].prev == &item[1]);
   assert (item[1].next == &item[1]);
   printf ("Ok, nao deixou remover um elemento de outra fila\n");
   printf ("Testando remocao de elemento que não está em nenhuma fila...\n");
   queue_remove ((queue_t**) &fila0, (queue_t*) &item[2]);
   assert (fila0 == &item[0]);
   assert (item[0].prev == &item[0]);
   assert (item[0].next == &item[0]);
   assert (item[2].prev == NULL);
   assert (item[2].next == NULL);
   printf ("Ok, nao deixou remover um elemento que não está em nenhuma fila\n");
   printf ("Testando insercao de elemento que já está na fila...\n");
   queue_append ((queue_t**) &fila0, (queue_t*) &item[0]);
   assert (fila0 == &item[0]);
   assert (item[0].prev == &item[0]);
   assert (item[0].next == &item[0]);
   printf ("Ok, não deixou inserir elemento que já estava na fila\n");
   printf ("Testando insercao de elemento que está em outra fila...\n");
   queue_append ((queue_t**) &fila0, (queue_t*) &item[1]);
   assert (fila0 == &item[0]);
   assert (item[0].prev == &item[0]);
   assert (item[0].next == &item[0]);
   assert (fila1 == &item[1]);
   assert (item[1].prev == &item[1]);
   assert (item[1].next == &item[1]);
   printf ("Ok, não deixou inserir elemento que está em outra fila\n");
   fila0 = NULL;
   for (i=0; i< N*N; i++)
   {
      aux = (filaint_t*) malloc (sizeof (filaint_t));
      aux->id = i;
      aux->prev = aux->next = NULL;
      queue_append ((queue_t**) &fila0, (queue_t*) aux);
      assert (fila_correta (fila0));
   }
   printf ("Ok, criei uma fila com %d elementos ordenados\n", N*N);
   for (i=0; i< N*N; i++)
   {
      aux = fila0;
      queue_remove ((queue_t**) &fila0, (queue_t*) fila0);
      assert (fila_correta (fila0));
      assert (aux->id == i);
      free (aux);
   }
   printf ("Ok, retirei e destrui em ordem %d elementos da fila\n", N*N);
   printf ("Testes de operações inválidas funcionaram!\n");
   printf ("Teste do queue_print...\n");
   for (i=0; i<N; i++)
   {
      item[i].id = i;
      item[i].prev = NULL;
      item[i].next = NULL;
   }
   fila0 = NULL;
   printf ("Saida esperada: []\n");
   queue_print ("Saida gerada  ", (queue_t*) fila0, print_elem);
   for (i=0; i<10;i++)
      queue_append ((queue_t**) &fila0, (queue_t*) &item[i]);
   printf ("Saida esperada: [9<0>1 0<1>2 1<2>3 2<3>4 3<4>5 4<5>6 5<6>7 6<7>8 7<8>9 8<9>0]\n");
   queue_print ("Saida gerada  ", (queue_t*) fila0, print_elem);
   printf ("Testes concluidos!!!\n");
   exit(0);
}