#include <stdio.h>
#include <stdbool.h>

bool canDistribute(int chocolates[], int n, int m, int x) {
    long long total = 0;
    for (int i = 0; i < n; i++) {
        total += chocolates[i] / x;
    }
    return total >= m;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int chocolates[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &chocolates[i]);
    }

    int left = 1, right = m;
    int result = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (canDistribute(chocolates, n, m, mid)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("%d\n", result);
    
    return 0;
}
