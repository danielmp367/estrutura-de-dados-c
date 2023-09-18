#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Autor {
  char nome[31];
  int publicacoes;
  int *citacoes;
  int indice_h;
} Autor;

static void get(Autor *a) {
  scanf("%s %d", a->nome, &a->publicacoes);
  a->citacoes = malloc(sizeof(int) * (a->publicacoes));
  for (size_t i = 0; i < a->publicacoes; i++) {
    scanf("%d", &a->citacoes[i]);
  }
}
static int calcular_indice_h(Autor *a) {
  int indiceH = 0;
  for (int i = 0; i < a->publicacoes; i++) {
    if (a->citacoes[i] >= i + 1) {
      indiceH = i + 1;
    } else {
      break;
    }
  }
  return indiceH;
}
void delete(Autor **v, size_t size) {
  for (size_t i = 0; i < size; i++) {
    free((*v)[i].citacoes);
  }
  free((*v));
  *v = NULL;
}

typedef int (*fn_cmp)(const void *a, const void *b);

static void swap(Autor *v, size_t i, size_t j) {
  Autor tmp = v[i];
  v[i] = v[j];
  v[j] = tmp;
}

int compare_autor(Autor *a, Autor *b) {

  if (a->indice_h > b->indice_h) {
    return -1;
  } else if (a->indice_h < b->indice_h) {
    return 1;
  } else {
    return strcmp(a->nome, b->nome);
  }
}

void insertion_sort(int *v, int n) {
  int i, j, chosen;
  for (i = 1; i < n; i++) {
    chosen = v[i];

    for (j = i - 1; (j >= 0) && (chosen > v[j]); j--) {
      v[j + 1] = v[j];
    }
    v[j + 1] = chosen;
  }
}

static void heapify(Autor *v, size_t i, size_t size) {
  size_t left, right, largest;
  while (i < size) {
    left = (i * 2) + 1;
    right = (i * 2) + 2;
    largest = i;

    if (left < size && compare_autor(&v[left], &v[largest]) > 0) {
      largest = left;
    }

    if (right < size && compare_autor(&v[right], &v[largest]) > 0) {

      largest = right;
    }

    if (largest == i) {
      break;
    }

    swap(v, i, largest);
    i = largest;
  }
}

void heap_sort(void *v, size_t size) {
  for (int i = size / 2 - 1; i >= 0; i--) {
    heapify(v, i, size);
  }

  for (int i = size - 1; i > 0; i--) {
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
    insertion_sort(vetor[i].citacoes, vetor[i].publicacoes);
    vetor[i].indice_h = calcular_indice_h(&vetor[i]);
  }

  heap_sort(vetor, n);

  for (size_t i = 0; i < n; i++) {
    printf("%s %d\n", vetor[i].nome, vetor[i].indice_h);
  }

  free(vetor);

  return 0;
}
