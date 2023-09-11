#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long int int64t;

void calcule_fib(int64t *v, int n) {
  int64t prev = 0;
  int64t curr = 1;
  int64t next;
  int i = 0;
  while (i < n) {
    v[i++] = prev;
    next = curr + prev;
    prev = curr;
    curr = next;
  }
}

int ingredientes(int64t *fib, int64t n) {
  int i = 89;
  int cont = 0;
  while (i >= 0 && n != 0) {
    if (n >= fib[i]) {
      n -= fib[i];
      cont++;
      i--;
    }
    i--;
  }
  return cont;
}

int main() {

  int n;
  scanf("%d", &n);

  int64t *v = malloc(sizeof(int64t) * n);
  int64t *fib = malloc(sizeof(int64t) * 90);

  calcule_fib(fib, 90);

  for (size_t i = 0; i < n; i++) {
    scanf("%llu", &v[i]);
  }

  for (size_t i = 0; i < n; i++) {
    printf("%d\n", ingredientes(fib, v[i]));
  }

  free(fib);
  free(v);
  return 0;
}
