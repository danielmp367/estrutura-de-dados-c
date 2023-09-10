#include <stdio.h>
#include <stdlib.h>


static void heapfy(int *v, size_t i, size_t size) {
	int left;
	int right;
	int largest;
	while(i < size) {
		left  = (i * 2) + 1;
		right = (i * 2) + 2;
		largest = i;
		
		if(left < size && v[left] > v[largest]) {
			largest = left;
		}
		if(right < size && v[right] > v[largest]) {
			largest = right;
		}
		
		if( i == largest) {
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
	for(i = size / 2; i >= 0; i--) {
		heapfy(v, i, size);
	}
}

void heap_sort(int *v, size_t size) {
	int i;
	make_heap(v, size);
	for(i = size - 1; i > 0; i--) {
		int aux = v[i];
		v[i] = v[0];
		v[0] = aux;
		heapfy(v, 0, i);
	}
}



int main() {
  const int max = 1000000;
  int *v = malloc(sizeof(int) * max);
  for(int i = 0; i < max; i++) {
    v[i] = rand() % max;
  }

  heap_sort(v, max);
  

return 0;
}
