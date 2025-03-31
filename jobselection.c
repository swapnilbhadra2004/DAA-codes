#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id, deadline, profit;
} Job;

int compare(const void *a, const void *b) {
    return ((Job *)b)->profit - ((Job *)a)->profit;
}

void jobScheduling(Job jobs[], int n) {
    qsort(jobs, n, sizeof(Job), compare);
    
    int max_deadline = 0;
    for (int i = 0; i < n; i++)
        if (jobs[i].deadline > max_deadline)
            max_deadline = jobs[i].deadline;
    
    int slot[max_deadline];
    for (int i = 0; i < max_deadline; i++)
        slot[i] = -1;
    
    int total_profit = 0;
    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline - 1; j >= 0; j--) {
            if (slot[j] == -1) {
                slot[j] = jobs[i].id;
                total_profit += jobs[i].profit;
                break;
            }
        }
    }
    
    printf("Selected Jobs: ");
    for (int i = 0; i < max_deadline; i++)
        if (slot[i] != -1)
            printf("J%d ", slot[i]);
    printf("\nTotal Profit: %d\n", total_profit);
}

int main() {
    Job jobs[] = {{1, 2, 100}, {2, 1, 50}, {3, 2, 10}, {4, 1, 20}, {5, 3, 30}};
    int n = sizeof(jobs) / sizeof(jobs[0]);
    jobScheduling(jobs, n);
    return 0;
}
