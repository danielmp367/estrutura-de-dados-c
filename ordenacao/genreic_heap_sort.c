#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*fn_cmp)(const void *a, const void *b);

static void swap(void *a, void *b, size_t size) {
  void *tmp = malloc(size);
  if (tmp == NULL) {
    perror("Erro na alocação de memória");
    exit(EXIT_FAILURE);
  }
  memcpy(tmp, a, size);
  memcpy(a, b, size);
  memcpy(b, tmp, size);
  free(tmp);
}

static void heapify(void *v, size_t i, size_t size, size_t size_type, fn_cmp compare) {
  size_t left, right, largest;
  while (i < size) {
    left = (i * 2) + 1;
    right = (i * 2) + 2;
    largest = i;

    if (left < size && compare((char *)(v + left * size_type), (char *)(v + largest * size_type)) > 0) {
      largest = left;
    }

    if (right < size && compare((char *)(v + right * size_type), (char *)(v + largest * size_type)) > 0) {
      largest = right;
    }

    if (largest == i) {
      break;
    }

    swap((char *)(v + i * size_type), (char *)(v + largest * size_type), size_type);
    i = largest;
  }
}

void heap_sort(void *v, size_t size, size_t size_type, fn_cmp compare) {
  for (int i = size / 2 - 1; i >= 0; i--) {
    heapify(v, i, size, size_type, compare);
  }

  for (int i = size - 1; i > 0; i--) {
    swap((char *)(v), (char *)(v + i * size_type), size_type);
    heapify(v, 0, i, size_type, compare);
  }
}

int compare_int(const void *a, const void *b) {
  return (*(int *)a - *(int *)b);
}

int compare_str(const void *a, const void *b) {
  return strcmp(*(char **)a, *(char **)b);
}

int main() {
  int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
  int n = sizeof(arr) / sizeof(arr[0]);

  heap_sort(arr, n, sizeof(int), compare_int);

  printf("Ordenado em ordem crescente: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  char *str_arr[] = {"banana", "maça", "laranja", "uva", "abacaxi"};
  int m = sizeof(str_arr) / sizeof(str_arr[0]);

  heap_sort(str_arr, m, sizeof(char *), compare_str);

  printf("Ordenado em ordem lexicográfica: ");
  for (int i = 0; i < m; i++) {
    printf("%s ", str_arr[i]);
  }
  printf("\n");

  return 0;
}
