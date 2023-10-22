#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int value;
  int index;
} element_t;

typedef struct {
  element_t *data;
  size_t capacity;
  size_t length;
} stack_t;

void stack_init(stack_t **s) {
  (*s) = malloc(sizeof(stack_t));
  (*s)->capacity = 16;
  (*s)->length = 0;
  (*s)->data = malloc(sizeof(element_t) * (*s)->capacity);
}

void stack_push(stack_t *s, element_t e) {
  if (s->length == s->capacity) {
    s->capacity *= 2;
    s->data = realloc(s->data, sizeof(element_t) * s->capacity);
  }

  s->data[s->length++] = e;
}

int stack_empty(stack_t *s) { return (s->length == 0); }

void stack_pop(stack_t *s) {
  if (s->length < (s->capacity / 4)) {
    s->capacity /= 2;
    s->data = realloc(s->data, sizeof(element_t) * s->capacity);
  }
  if (!stack_empty(s)) {
    s->length--;
  }
}

element_t stack_top(stack_t *s) { return s->data[s->length - 1]; }

void stack_delete(stack_t **s) {
  free((*s)->data);
  free(*s);
  *s = NULL;
}

void find_previous_element(int *seq, int n) {
  int *resp = malloc(sizeof(int) * n);
  stack_t *s;
  stack_init(&s);
  for (size_t i = 0; i < n; i++) {
    while (!stack_empty(s) && stack_top(s).value >= seq[i]) {
      stack_pop(s);
    }

    if (stack_empty(s)) {
      resp[i] = 0;
    } else {
      resp[i] = stack_top(s).index + 1;
    }
    element_t e = {.value = seq[i], .index = i};
    stack_push(s, e);
  }

  for (size_t i = 0; i < n; i++) {
    printf("%d ", resp[i]);
  }
  printf("\n");

  stack_delete(&s);
  free(resp);
}

int main(void) {
  int n;
  scanf("%d", &n);

  int *seq = malloc(sizeof(int) * n);

  for (size_t i = 0; i < n; i++) {
    scanf("%d", &seq[i]);
  }
  find_previous_element(seq, n);
  free(seq);

  return 0;
}
