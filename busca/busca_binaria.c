#include <stdio.h>
#include <stdlib.h>

int busca_binaria(int *v, size_t size, int key) {
  int low = 0;
  int high = size - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (v[mid] == key) {
      return mid;
    } else if (key < v[mid]) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return -1;
}

int main() {
  const int tam = 100;
  int *v = (int *)malloc(sizeof(int) * tam);
  for (int i = 0; i < tam; i++) {
    v[i] = i;
  }

  printf("%d\n", busca_binaria(v, tam, 97));

  return 0;
}
