#include <stdio.h>
#include <stdlib.h>

// Structure for a Huffman tree node
typedef struct HuffmanNode {
    char data;
    int freq;
    struct HuffmanNode *left, *right;
} HuffmanNode;

// Structure for a Min Heap
typedef struct {
    int size;
    int capacity;
    HuffmanNode **array;
} MinHeap;

HuffmanNode* createNode(char data, int freq) {
    HuffmanNode* node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (HuffmanNode**)malloc(capacity * sizeof(HuffmanNode*));
    return minHeap;
}

void swapNodes(HuffmanNode** a, HuffmanNode** b) {
    HuffmanNode* temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;
    if (smallest != idx) {
        swapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

HuffmanNode* extractMin(MinHeap* minHeap) {
    HuffmanNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(MinHeap* minHeap, HuffmanNode* node) {
    int i = minHeap->size++;
    while (i && node->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

MinHeap* buildMinHeap(char data[], int freq[], int size) {
    MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = createNode(data[i], freq[i]);
    minHeap->size = size;
    for (int i = (minHeap->size - 2) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
    return minHeap;
}

HuffmanNode* buildHuffmanTree(char data[], int freq[], int size) {
    MinHeap* minHeap = buildMinHeap(data, freq, size);
    while (minHeap->size > 1) {
        HuffmanNode* left = extractMin(minHeap);
        HuffmanNode* right = extractMin(minHeap);
        HuffmanNode* top = createNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

void printCodes(HuffmanNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (!root->left && !root->right) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; i++)
            printf("%d", arr[i]);
        printf("\n");
    }
}

void HuffmanCodes(char data[], int freq[], int size) {
    HuffmanNode* root = buildHuffmanTree(data, freq, size);
    int arr[100], top = 0;
    printCodes(root, arr, top);
}

int main() {
    char data[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(data) / sizeof(data[0]);
    
    HuffmanCodes(data, freq, size);
    return 0;
}
