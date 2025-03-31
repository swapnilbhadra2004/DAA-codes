#include <stdio.h>
#include <string.h>

#define d 256
#define q 101

void rabinKarp(char* text, char* pattern) {
    int M = strlen(pattern);
    int N = strlen(text);
    int i, j;
    int p = 0, t = 0, h = 1;
    
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;
    
    for (i = 0; i < M; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }
    
    for (i = 0; i <= N - M; i++) {
        if (p == t) {
            for (j = 0; j < M; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == M)
                printf("Pattern found at index %d\n", i);
        }
        if (i < N - M) {
            t = (d * (t - text[i] * h) + text[i + M]) % q;
            if (t < 0)
                t = (t + q);
        }
    }
}

int main() {
    char text[] = "ABABDABACDABABCABAB";
    char pattern[] = "ABABCABAB";
    rabinKarp(text, pattern);
    return 0;
}
