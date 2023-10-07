#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t {
  char nome[31];
  struct node_t *next;
} node_t;

typedef struct list_t {
  node_t *node;
  node_t *head;
  node_t *tail;
  size_t size;
} list_t;

void list_initialize(list_t **l) {

  (*l) = malloc(sizeof(list_t));
  (*l)->node = NULL;
  (*l)->head = NULL;
  (*l)->tail = NULL;
  (*l)->size = 0;
}

size_t list_size(list_t *l) { return l->size; }

int list_empty(list_t *l) { return (l->size == 0) ? 1 : 0; }

node_t *new_node(const char *str) {
  node_t *node = malloc(sizeof(node_t));
  strcpy(node->nome, str);
  node->next = NULL;
  return node;
}

void list_append(list_t *l, const char *str) {
  if (list_empty(l) == 1) {
    l->head = new_node(str);
    l->tail = l->head;
    l->size++;
  } else {
    l->tail->next = new_node(str);
    l->tail = l->tail->next;
    l->size++;
  }
}

void list_remove_head(list_t *l) {
  if (!list_empty(l)) {
    node_t *it = l->head;
    l->head = l->head->next;
    l->size--;
    free(it);
  }
}

void list_remove(list_t *l, size_t i) {
  if (list_empty(l) == 1) {
    return;
  } else {
    if (i == 0) {
      list_remove_head(l);
    } else {
      node_t *prev = l->head;
      node_t *curr = prev->next;
      size_t count = 1;

      while (curr != NULL && count < i) {
        prev = curr;
        curr = curr->next;
        count++;
      }

      if (curr != NULL) {
        prev->next = curr->next;

        if (curr == l->tail) {
          l->tail = prev;
        }

        free(curr);
        l->size--;
      }
    }
  }
}

void print_list(list_t *l) {
  for (node_t *it = l->head; it != NULL; it = it->next) {
    printf("%s\n", it->nome);
  }
}

void list_delete(list_t **l) {
  node_t *it = (*l)->head;
  while (it != NULL) {
    (*l)->head = (*l)->head->next;
    free(it);
    it = (*l)->head;
  }
  free(*l);
  (*l) = NULL;
}

void sort_nomes(list_t *l, int x) {

  node_t *it = l->head;
  size_t pos = 0;

  while (list_size(l) > 1) {
    for (int i = 0; i < x - 1; i++) {
      it = it->next;
      pos++;
      if (it == NULL) {
        it = l->head;
        pos = 0;
      }
    }

    node_t *next = it->next;
    list_remove(l, pos);

    it = next;
    if (it == NULL) {
      it = l->head;
      pos = 0;
    }
  }

  printf("%s\n", l->head->nome);
}

int main() {

  int n, x;
  scanf("%d %d", &n, &x);

  list_t *l;
  list_initialize(&l);

  for (size_t i = 0; i < n; i++) {
    char buffer[31];
    memset(buffer, '\0', 31);
    scanf("%s", buffer);
    list_append(l, buffer);
  }
  sort_nomes(l, x);

  list_delete(&l);

  return 0;
}
