#include <stdio.h>
#include <stdlib.h>

static void heapify(int *v, size_t i, size_t size) {
  int left, right, largest;
  while (i < size) {
    left = (i * 2) + 2;
    right = (i * 2) + 1;
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
    int temp = v[i];
    v[i] = v[largest];
    v[largest] = temp;
    largest = i;
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

static int string_to_seconds(const char *str) {
  int hh, mm, ss;

  sscanf(str, "%d:%d:%d", &hh, &mm, &ss);

  return (hh * 3600) + (mm * 60) + ss;
}

static void get(int *data1, int *data2) {
  char s1[9] = {'\0'};
  char s2[9] = {'\0'};
  scanf("%s %s", s1, s2);
  (*data1) = string_to_seconds(s1);
  (*data2) = string_to_seconds(s2);
}

int barbosinha_chair_count(int *entry, int *departure, size_t size) {
  int count = 0;
  int maior = 0;
  size_t i = 0;
  size_t j = 0;

  while (i < size && j < size) {
    if (entry[i] <= departure[j]) {
      count++;
      i++;
    } else {
      j++;
      count--;
    }
    if (maior < count) {
      maior = count;
    }
  }
  return maior;
}

int main() {
  int n;
  scanf("%d", &n);

  int *entry = malloc(sizeof(int) * n);
  int *departure = malloc(sizeof(int) * n);

  for (size_t i = 0; i < n; i++) {
    get(&entry[i], &departure[i]);
  }

  heap_sort(entry, n);
  heap_sort(departure, n);

  int chairs = barbosinha_chair_count(entry, departure, n);

  printf("%d\n", chairs);

  free(entry);
  free(departure);
  return 0;
}
