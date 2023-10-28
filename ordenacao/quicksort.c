#include <stdio.h>
#include <stdlib.h>

static void swap(int *v, int i, int j);
static size_t partition(int *v, int left, int right, int pivot);
static void quick_sort_helper(int *v, int left, int right);

static void swap(int *v, int i, int j) {
  int temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

static size_t partition(int *v, int left, int right, int pivot) {
  size_t pos, i;
  swap(v, pivot, right);
  pos = left;
  for (i = left; i < right; ++i) {
    if (v[i] < v[right]) {
      swap(v, i, pos);
      pos++;
    }
  }
  swap(v, right, pos);
  return pos;
}

void quick_sort_helper(int *v, int left, int right) {
  if (left < right) {
    size_t pos = partition(v, left, right, right);
    quick_sort_helper(v, left, pos - 1);
    quick_sort_helper(v, pos + 1, right);
  }
}

void quick_sort(int *v, size_t size) { quick_sort_helper(v, 0, size - 1); }
