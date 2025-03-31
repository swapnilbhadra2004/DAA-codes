#include <stdio.h>
#include <stdlib.h>

// Structure for an item
typedef struct {
    int value;
    int weight;
} Item;

// Comparison function to sort items by value-to-weight ratio in descending order
int compare(const void *a, const void *b) {
    double r1 = ((Item*)a)->value / (double)((Item*)a)->weight;
    double r2 = ((Item*)b)->value / (double)((Item*)b)->weight;
    return (r2 > r1) - (r2 < r1);
}

double fractional_knapsack(int capacity, Item items[], int n) {
    // Sort items based on value-to-weight ratio
    qsort(items, n, sizeof(Item), compare);
    
    double total_value = 0.0;
    for (int i = 0; i < n; i++) {
        if (capacity >= items[i].weight) {
            // Take the whole item
            capacity -= items[i].weight;
            total_value += items[i].value;
        } else {
            // Take a fraction of the item
            total_value += items[i].value * ((double)capacity / items[i].weight);
            break;
        }
    }
    return total_value;
}

int main() {
    Item items[] = {{60, 10}, {100, 20}, {120, 30}};
    int capacity = 50;
    int n = sizeof(items) / sizeof(items[0]);
    
    double max_value = fractional_knapsack(capacity, items, n);
    printf("Maximum value in Knapsack = %.2f\n", max_value);
    
    return 0;
}
