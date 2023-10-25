#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int conhecimento; 
  int semana;
} curso_t;

typedef struct priority_queue_t {
  curso_t *pqueue;
  size_t size;
  size_t capacity;
} priority_queue_t;

bool compare(curso_t *a, curso_t *b) {
  if (a->conhecimento > b->conhecimento) {
    return true;
  }
  if (a->conhecimento == b->conhecimento && a->semana >= b->semana) {
    return true;
  }
  return false;
}

size_t priority_queue_size(priority_queue_t *pq) { return pq->size; }

static bool priority_queue_empty(priority_queue_t *pq) {
  return priority_queue_size(pq) == 0;
}

static void priority_queue_heapify_bottom_up(priority_queue_t *pq, size_t i) {
  size_t p;
  for (p = (i - 1) / 2; i != 0; i = p, p = (p - 1) / 2) {
    if (compare(&pq->pqueue[p], &pq->pqueue[i])) {
      break;
    }
    curso_t aux = pq->pqueue[i];
    pq->pqueue[i] = pq->pqueue[p];
    pq->pqueue[p] = aux;
  }
}

static void priority_queue_heapify_top_down(priority_queue_t *pq, size_t i) {
  size_t l, r;
  size_t largest = i;
  while (i < pq->size) {
    i = largest;
    l = 2 * i + 1;
    r = 2 * i + 2;
    if (l < pq->size && compare(&pq->pqueue[l], &pq->pqueue[largest])) {
      largest = l;
    }
    if (r < pq->size && compare(&pq->pqueue[r], &pq->pqueue[largest])) {
      largest = r;
    }
    if (largest == i) {
      break;
    }
    curso_t aux = pq->pqueue[i];
    pq->pqueue[i] = pq->pqueue[largest];
    pq->pqueue[largest] = aux;
  }
}

void priority_queue_initialize(priority_queue_t **pq) {
  (*pq) = malloc(sizeof(priority_queue_t));
  (*pq)->size = 0;
  (*pq)->capacity = 4;
  (*pq)->pqueue = malloc(sizeof(curso_t) * (*pq)->capacity);
}

void priority_queue_delete(priority_queue_t **pq) {
  free((*pq)->pqueue);
  free(*pq);
  (*pq) = NULL;
}

void priority_queue_push(priority_queue_t *pq, curso_t course) {
  if (pq->size == pq->capacity) {
    pq->capacity *= 2;
    pq->pqueue = realloc(pq->pqueue, sizeof(curso_t) * pq->capacity);
  }
  pq->pqueue[pq->size++] = course;
  priority_queue_heapify_bottom_up(pq, pq->size);
  //pq->size++;
}

void priority_queue_pop(priority_queue_t *pq) {
  assert(!priority_queue_empty(pq));
  if (pq->size == pq->capacity / 4 && pq->capacity > 4) {
    pq->capacity /= 2;
    pq->pqueue = realloc(pq->pqueue, sizeof(curso_t) * pq->capacity);
  }
  pq->size--;
  if (!priority_queue_empty(pq)) {
    pq->pqueue[0] = pq->pqueue[pq->size];
    priority_queue_heapify_top_down(pq, 0);
  }
}

curso_t priority_queue_front(priority_queue_t *pq) {
  assert(!priority_queue_empty(pq));
  return pq->pqueue[0];
}

curso_t get_course() {
  curso_t c;
  scanf("%d %d", &c.semana, &c.conhecimento);
  return c;
}

int main() {
  int n, m;

  scanf("%d %d", &n, &m);

  priority_queue_t *pq;
  priority_queue_initialize(&pq);
  int *semanas = malloc(m * sizeof(int));

  for (size_t i = 0; i < n; i++) {
    semanas[i] = 0;
    curso_t c = get_course();
    priority_queue_push(pq, c);
  }

  int sum = 0;

  while (!priority_queue_empty(pq)) {
    curso_t c = priority_queue_front(pq);
    int indice = c.semana - 1;
    if (!semanas[indice]) {
      semanas[indice] = 1;
      sum += c.conhecimento;
    }
    priority_queue_pop(pq);
  }

  printf("%d\n", sum);

  priority_queue_delete(&pq);
  free(semanas);

  return 0;
}