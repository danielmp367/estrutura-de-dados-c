#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

    int aux = v[i];
    v[i] = v[largest];
    v[largest] = aux;
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
    int temp = v[i];
    v[i] = v[0];
    v[0] = temp;
    heapify(v, 0, i);
  }
}

int binary_search(int *v, size_t size, int data) {
  size_t low = 0;
  size_t high = size - 1;
  int mid = 0;

  while (low <= high) {
    mid = low + (high - low) / 2;
    if (data == v[mid]) {
      return mid;
    } else if (data < v[mid]) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return -1;
}
void set_vector(int **v, size_t size) {
  srand(time(NULL));
  (*v) = malloc(sizeof(int) * size);

  for (size_t i = 0; i < size; i++) {
    (*v)[i] = rand() % 100;
  }
}

void print_soma_pares(int *v, size_t size, int k) {
  int value = 0;
  int status = 0;
  heap_sort(v, size);
  for (int i = 0; i < size; i++) {
    value = k - v[i];
    status = binary_search(v, size, value);

    if (status != -1 && i != status) {
      printf("%d %d\n", i + 1, status + 1);
      return;
    }
  }
  printf("-1\n");
}

int main() {
  int n, k;
  scanf("%d %d", &n, &k);
  int *v = malloc(sizeof(int) * n);

  for (size_t i = 0; i < n; i++) {
    scanf("%d", &v[i]);
  }

  print_soma_pares(v, n, k);
  free(v);
  return 0;
}
