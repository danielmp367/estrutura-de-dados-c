#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string {
  char str[11];
  size_t size;
} string;

void insertion_sort(string *v, int n) {
  int i, j;
  string chosen;

  for (i = 1; i < n; i++) {
    chosen = v[i];
    for (j = i - 1; (j >= 0) && (chosen.size < v[j].size); j--) {
      v[j + 1] = v[j];
    }
    v[j + 1] = chosen;
  }
}

void merge(string *v, string *v1, string *v2, size_t size) {
  size_t size_v1 = size / 2;
  size_t size_v2 = size - size_v1;
  int i = 0; // index of v
  int j = 0; // index of v1
  int k = 0; // index of v2

  for (i = 0; (j < size_v1) && (k < size_v2); i++) {
    if (v1[j].size <= v2[k].size) {
      v[i] = v1[j++];
    } else {
      v[i] = v2[k++];
    }
  }

  while (j < size_v1) {
    v[i++] = v1[j++];
  }

  while (k < size_v2) {
    v[i++] = v2[k++];
  }
}

void merge_sort(string *v, size_t size) {
  if (size > 16) {
    size_t mid = size / 2;
    string *v1 = malloc(sizeof(string) * mid);
    string *v2 = malloc(sizeof(string) * size - mid);

    for (size_t i = 0; i < mid; i++) {
      v1[i] = v[i];
    }

    for (size_t i = mid; i < size; i++) {
      v2[i - mid] = v[i];
    }

    merge_sort(v1, mid);
    merge_sort(v2, size - mid);

    merge(v, v1, v2, size);

    free(v1);
    free(v2);
  } else {
    insertion_sort(v, size);
  }
}

void print_vetor(string *v, int n) {
  for (size_t i = 0; i < n; i++) {
    printf("%s\n", v[i].str);
  }
}

int main(int argc, char **argv) {

  int n;
  scanf("%d", &n);
  string *v = malloc(sizeof(string) * n);

  for (size_t i = 0; i < n; i++) {
    scanf("%s", v[i].str);
    v[i].size = strlen(v[i].str);
  }

  merge_sort(v, n);

  print_vetor(v, n);

  free(v);

  return 0;
}
