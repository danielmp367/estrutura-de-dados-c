#include <stdio.h>
#include <stdlib.h>

static void heapfy(int *v, size_t i, size_t size) {
  int left;
  int right;
  int largest;
  while (i < size) {
    left = (i * 2) + 1;
    right = (i * 2) + 2;
    largest = i;

    if (left < size && v[left] > v[largest]) {
      largest = left;
    }
    if (right < size && v[right] > v[largest]) {
      largest = right;
    }

    if (i == largest) {
      break;
    }
    int aux = v[i];
    v[i] = v[largest];
    v[largest] = aux;
    i = largest;
  }
}

static void make_heap(int *v, size_t size) {
  int i;
  for (i = size / 2; i >= 0; i--) {
    heapfy(v, i, size);
  }
}

void heap_sort(int *v, size_t size) {
  int i;
  make_heap(v, size);
  for (i = size - 1; i > 0; i--) {
    int aux = v[i];
    v[i] = v[0];
    v[0] = aux;
    heapfy(v, 0, i);
  }
}

int cont_numeros_distintos(int *v, size_t size) {
  heap_sort(v, size);
  int cont = 1;
  for (size_t i = 0; i < size - 1; i++) {
    if (v[i] != v[i + 1]) {
      cont++;
    }
  }
  return cont;
}

int main() {
  int n;
  scanf("%d", &n);
  int *v = malloc(sizeof(int) * n);

  for (size_t i = 0; i < n; i++) {
    scanf("%d", &v[i]);
  }

  int numeros_distintos = cont_numeros_distintos(v, n);

  printf("%d\n", numeros_distintos);

  free(v);

  return 0;
}
