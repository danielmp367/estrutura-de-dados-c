#include <stdio.h>
#include <stdlib.h>

typedef struct Autor {
  char nome[31];
  int publicacoes;
  int *citacoes;
  int indice_h;
} Autor;

void get(Autor *a) {
  scanf("%s %d", a->nome, &a->publicacoes);
  a->citacoes = malloc(sizeof(int) * (a->publicacoes));
  for (size_t i = 0; i < a->publicacoes; i++) {
    scanf("%d", &a->citacoes[i]);
  }
}

void delete(Autor *a) { free(a->citacoes); }

static void swap(int *v, int i, int j) {
  int swp = v[i];
  v[i] = v[j];
  v[j] = swp;
}

static void heapify(int *v, size_t i, size_t size) {
  int left, right, largest;
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

    if (largest == i) {
      break;
    }

    swap(v, i, largest);
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
    swap(v, i, 0);
    heapify(v, 0, i);
  }
}

int main() {
  int n;
  scanf("%d", &n);
  Autor *vetor = malloc(sizeof(Autor) * n);
  for (size_t i = 0; i < n; i++) {
    get(&vetor[i]);
    heap_sort(vetor[i].citacoes, vetor[i].publicacoes);
  }

  return 0;
}
