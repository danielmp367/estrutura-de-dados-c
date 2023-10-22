#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *items;
  size_t size;
  size_t capacity;
} stack_t;

void stack_initialize(stack_t **s) {
  (*s) = malloc(sizeof(stack_t));
  (*s)->capacity = 16;
  (*s)->size = 0;
  (*s)->items = malloc(sizeof(char) * (*s)->capacity);
}

int stack_empty(stack_t *s) { return (s->size == 0); }

void stack_push(stack_t *s, char item) {
  if (s->size == s->capacity) {
    s->capacity *= 2;
    s->items = realloc(s->items, sizeof(char) * s->capacity);
  }

  s->items[s->size++] = item;
}

void stack_pop(stack_t *s) {
  if (s->size == s->capacity / 4 && s->capacity != 16) {
    s->capacity /= 2;
    s->items = realloc(s->items, sizeof(char) * s->capacity);
  }

  s->size--;
}

char stack_top(stack_t *s) {
  if (stack_empty(s)) {
    return '\0';
  }
  return s->items[s->size - 1];
}

void stack_delete(stack_t **s) {
  free((*s)->items);
  free(*s);
  *s = NULL;
}

int get_precedence(char op) {
  switch (op) {
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
    return 2;
  case '^':
    return 3;
  }
  return 0;
}

char *space_remove(const char *src) {
  long length_src = strlen(src);
  char *out = malloc(sizeof(char) * length_src);

  int i = 0;
  int k = 0;

  for (; i < length_src; i++) {
    if (src[i] == '\0') {
      break;
    }
    if (src[i] == ' ') {
      continue;
    }

    out[k] = src[i];
    k++;
  }

  out[strlen(out)] = '\0';

  return out;
}

void infix_to_postfix(char *infix) {
  stack_t *s;
  stack_initialize(&s);

  int length = strlen(infix);
  char numberBuffer[20]; // Suponha que números inteiros terão até 20 dígitos

  for (int i = 0; i < length; i++) {
    char c = infix[i];
    if (c == ' ') {
      continue;
    }

    if (isdigit(c)) {
      int j = 0;
      while (i < length && isdigit(c)) {
        numberBuffer[j++] = c;
        i++;
        c = infix[i];
      }
      numberBuffer[j] = '\0';
      printf("%s ", numberBuffer);
      i--; // Volte um passo para processar o próximo caractere
    } else if (c == '(') {
      stack_push(s, c);
    } else if (c == ')') {
      while (!stack_empty(s) && stack_top(s) != '(') {
        printf("%c ", stack_top(s));
        stack_pop(s);
      }
      stack_pop(s);
    } else {
      while (!stack_empty(s) &&
             get_precedence(stack_top(s)) >= get_precedence(c)) {
        printf("%c ", stack_top(s));
        stack_pop(s);
      }
      stack_push(s, c);
    }
  }

  while (!stack_empty(s)) {
    printf("%c ", stack_top(s));
    stack_pop(s);
  }

  // printf("\n");
  stack_delete(&s);
}

int main() {
  const int max = 100000;
  char *infix = malloc(sizeof(char) * max);

  fgets(infix, max, stdin);
  // char *out = space_remove(infix);

  // printf("%s\n", out);
  infix_to_postfix(infix);

  free(infix);
  return 0;
}