#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
  char *items;
  size_t capacity;
  size_t length;
} stack_t;

void stack_init(stack_t **s) {
  (*s) = malloc(sizeof(stack_t));
  (*s)->capacity = 16;
  (*s)->length = 0;
  (*s)->items = malloc(sizeof(char) * (*s)->capacity);
}

void stack_push(stack_t *s, char c) {
  if (s->length == s->capacity) {
    s->capacity *= 2;
    s->items = realloc(s->items, sizeof(char) * s->capacity);
  }

  s->items[s->length++] = c;
}

int stack_empty(stack_t *s) { return (s->length == 0); }

void stack_pop(stack_t *s) {
  if (s->length < (s->capacity / 4)) {
    s->capacity /= 2;
    s->items = realloc(s->items, sizeof(char) * s->capacity);
  }
  if (!stack_empty(s)) {
    s->length--;
  }
}

char stack_top(stack_t *s) { return s->items[s->length - 1]; }

void stack_delete(stack_t **s) {
  free((*s)->items);
  free(*s);
  *s = NULL;
}


void remove_digits(char *seq, int n, int d) {
  int qtd_items = d;
  stack_t *s;
  stack_init(&s);
  for (size_t i = 0; i < n; i++) {
    char c = seq[i];
    while (!stack_empty(s) && qtd_items > 0 && c > stack_top(s)) {
      stack_pop(s);
      qtd_items --;
    }
    stack_push(s, c);
  }
  s->length = n - d;

  for (size_t i = 0; i < s->length; i++) {
    printf("%c", s->items[i]);
  }
  printf("\n");

  stack_delete(&s);
  
}


int main() {
  char *buffer;
  int n = 0;
  int d = 0;

  while (1) {
    scanf("%d %d", &n, &d);
    if (n == 0 || d == 0) {
      break;
    }
    if (d >= n) {
      //fprintf(stderr, "Erro: d deve ser menor que n.\n");
      continue;
    }
    buffer = malloc(sizeof(char) * (n + 1));
    if (buffer == NULL) {
      //fprintf(stderr, "Erro de alocação de memória\n");
      exit(1);
    }
    scanf("%s", buffer);
    remove_digits(buffer, n, d);
    free(buffer);
  }

  return 0;
}