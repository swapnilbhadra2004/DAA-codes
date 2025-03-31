#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int hireAssistant(int candidates[], int n) {
    int best = INT_MIN;
    int hires = 0;
    
    for (int i = 0; i < n; i++) {
        if (candidates[i] > best) {
            best = candidates[i];
            hires++;
            printf("Hired candidate with quality %d\n", candidates[i]);
        }
    }
    return hires;
}

int main() {
    int candidates[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    int n = sizeof(candidates) / sizeof(candidates[0]);
    
    int totalHires = hireAssistant(candidates, n);
    printf("Total hires: %d\n", totalHires);
    return 0;
}

