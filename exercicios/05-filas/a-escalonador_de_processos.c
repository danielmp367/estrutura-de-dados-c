#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar um processo
typedef struct process {
  int pid;
  char name[31];
  int time;
} process;

typedef struct node_t {
  process p;
  struct node_t *next;
} node_t;

typedef struct queue_t {
  node_t *front;
  node_t *rear;
  size_t size;
} queue_t;

void queue_initialize(queue_t **q) {
  (*q) = malloc(sizeof(queue_t));
  (*q)->front = NULL;
  (*q)->rear = NULL;
  (*q)->size = 0;
}

process *create_process(int pid, char *name, int time) {
  process *p = malloc(sizeof(process));
  p->pid = pid;
  strcpy(p->name, name);
  p->time = time;
  return p;
}

node_t *new_node(process *p) {
  node_t *node = malloc(sizeof(node_t));
  node->p = (*p);
  node->next = NULL;
  return node;
}

void enqueue(queue_t *q, process *p) {
  if (q->front == NULL) {
    q->front = new_node(p);
    q->rear = q->front;
    q->size++;
    return;
  }
  q->rear->next = new_node(p);
  q->rear = q->rear->next;
  q->size++;
}

// Função para remover um processo da fila
node_t *dequeue(queue_t *q) {
  if (q->front == NULL) {
    return NULL;
  }
  node_t *ptr = q->front;
  q->front = q->front->next;
  q->size--;
  return ptr;
}

int main() {
  int n, q;
  scanf("%d %d", &n, &q);
  queue_t *queue;
  queue_initialize(&queue);

  for (int i = 0; i < n; i++) {
    int pid, time;
    char name[31];
    scanf("%s %d %d", name, &pid, &time);
    process *process = create_process(pid, name, time);
    enqueue(queue, process);
  }

  int currentTime = 0;
  while (queue->front != NULL) {
    node_t *currentProcess = dequeue(queue);
    if (currentProcess->p.time <= q) {
      currentTime += currentProcess->p.time;
      printf("%s %d %d ms\n", currentProcess->p.name, currentProcess->p.pid,
             currentTime);
      free(currentProcess);
    } else {
      currentTime += q;
      currentProcess->p.time -= q;
      enqueue(queue, &currentProcess->p);
    }
  }

  return 0;
}