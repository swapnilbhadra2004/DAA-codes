#include <stdio.h>
#include <limits.h>

#define NUM_STATIONS 4

int assemblyLineScheduling(int a[2][NUM_STATIONS], int t[2][NUM_STATIONS - 1], int e[2], int x[2]) {
    int T1[NUM_STATIONS], T2[NUM_STATIONS];
    
    T1[0] = e[0] + a[0][0];
    T2[0] = e[1] + a[1][0];
    
    for (int i = 1; i < NUM_STATIONS; i++) {
        T1[i] = (T1[i - 1] + a[0][i]) < (T2[i - 1] + t[1][i - 1] + a[0][i]) ? (T1[i - 1] + a[0][i]) : (T2[i - 1] + t[1][i - 1] + a[0][i]);
        T2[i] = (T2[i - 1] + a[1][i]) < (T1[i - 1] + t[0][i - 1] + a[1][i]) ? (T2[i - 1] + a[1][i]) : (T1[i - 1] + t[0][i - 1] + a[1][i]);
    }
    
    return (T1[NUM_STATIONS - 1] + x[0]) < (T2[NUM_STATIONS - 1] + x[1]) ? (T1[NUM_STATIONS - 1] + x[0]) : (T2[NUM_STATIONS - 1] + x[1]);
}

int main() {
    int a[2][NUM_STATIONS] = {{4, 5, 3, 2}, {2, 10, 1, 4}};
    int t[2][NUM_STATIONS - 1] = {{7, 4, 5}, {9, 2, 8}};
    int e[2] = {10, 12};
    int x[2] = {18, 7};
    
    printf("Minimum time required = %d\n", assemblyLineScheduling(a, t, e, x));
    
    return 0;
}
