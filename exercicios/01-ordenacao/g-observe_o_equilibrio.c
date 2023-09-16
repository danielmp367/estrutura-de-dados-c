#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static void heapify(int *v, size_t i, size_t size) {
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

    int tmp = v[i];
    v[i] = v[largest];
    v[largest] = tmp;
    i = largest;
  }
}

static void make_heap(int *v, size_t size) {
  int i;
  for (i = size / 2; i >= 0; i--) {
    heapify(v, i, size);
  }
}

void heap_sort(int *v, size_t size) {
  int i;
  make_heap(v, size);
  for (i = size - 1; i > 0; i--) {
    int tmp = v[i];
    v[i] = v[0];
    v[0] = tmp;
    heapify(v, 0, i);
  }
}

void print_vetor(int *v, int n) {
  for (size_t i = 0; i < n; i++) {
    printf("%d\n", v[i]);
  }
}

int dividi(int a, int b) { return b ? (a % b) != 0 : 0; }

int sequencia_equilibrada_max_min(int *v, int n) {
  int min = INT_MAX;
  int max = INT_MIN;

  for (size_t i = 0; i < n; i++) {
    if (v[i] < min) {
      min = v[i];
    }
    if (v[i] > max) {
      max = v[i];
    }
  }
  return max % min == 0;
}

int sequencia_equilibrada(int *v, int n) {
  int equilibrada = 1; // assume verdadeiro
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      if (i != j && dividi(v[j], v[i]) && dividi(v[i], v[j])) {
        equilibrada = 0;
        break;
      }
    }
  }
  return equilibrada;
}

int main() {
  int n;
  scanf("%d", &n);

  int *v = malloc(sizeof(int) * n);

  for (size_t i = 0; i < n; i++) {
    scanf("%d", &v[i]);
  }

  heap_sort(v, n);

  int equilibrada = sequencia_equilibrada_max_min(v, n);
  printf("%s\n", equilibrada ? "Sim" : "Nao");

  free(v);

  return 0;
}
