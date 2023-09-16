#include <stdio.h>
#include <stdlib.h>

typedef struct Piloto {
  char nome[30];
  int tempo;
} Piloto;

void insertion_sort(Piloto *v, size_t size) {
  int i, j;
  Piloto chosen;
  for (i = 1; i < size; i++) {
    chosen = v[i];
    for (j = i - 1; (j >= 0) && (chosen.tempo < v[j].tempo); j--) {
      v[j + 1] = v[j];
    }
    v[j + 1] = chosen;
  }
}

void print_vetor(int *v, size_t size) {
  for (size_t i = 0; i < size; i++) {
    printf("%d\n", v[i]);
  }
}

static void merge(Piloto *v, Piloto *v1, Piloto *v2, size_t size) {
  size_t size_v1 = size / 2;
  size_t size_v2 = size - size_v1;
  int i = 0; // index of v
  int j = 0; // index of v1
  int k = 0; // index of v2

  for (i = 0; (j < size_v1) && (k < size_v2); i++) {
    if (v1[j].tempo <= v2[k].tempo) {
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

void merge_sort(Piloto *v, size_t size) {
  if (size > 16) {
    size_t mid = size / 2;
    Piloto *v1 = malloc(sizeof(Piloto) * mid);
    Piloto *v2 = malloc(sizeof(Piloto) * size - mid);

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

void get_piloto(Piloto *p) {
  int t[6];
  scanf("%s", p->nome);
  scanf("%d.%d %d.%d %d.%d", &t[0], &t[1], &t[2], &t[3], &t[4], &t[5]);
  p->tempo = t[0] * 1000 + t[1] + t[2] * 1000 + t[3] + t[4] * 1000 + t[5];
}

void print_piloto(Piloto *v, size_t size) {
  int minuto = 0;
  int segundos = 0;
  int milisegundos = 0;
  for (size_t i = 0; i < size; i++) {
    minuto = v[i].tempo / 60000;
    segundos = (v[i].tempo % 60000) / 1000;
    milisegundos = ((v[i].tempo % 60000) % 1000);
    printf("%zu. %s - %1d:%02d.%03d\n", i + 1, v[i].nome, minuto, segundos,
           milisegundos);
  }
}

int main() {
  int n;
  scanf("%d", &n);
  Piloto *v = malloc(sizeof(Piloto) * n);

  for (size_t i = 0; i < n; i++) {
    get_piloto(&v[i]);
  }
  merge_sort(v, n);
  print_piloto(v, n);

  free(v);
  return 0;
}
