#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int makeEqualLength(char **str1, char **str2) {
    int len1 = strlen(*str1);
    int len2 = strlen(*str2);
    if (len1 < len2) {
        *str1 = (char*)realloc(*str1, len2 + 1);
        memmove(*str1 + (len2 - len1), *str1, len1 + 1);
        memset(*str1, '0', len2 - len1);
        return len2;
    } else if (len1 > len2) {
        *str2 = (char*)realloc(*str2, len1 + 1);
        memmove(*str2 + (len1 - len2), *str2, len2 + 1);
        memset(*str2, '0', len1 - len2);
        return len1;
    }
    return len1;
}

int multiplySingleDigit(char a, char b) {
    return (a - '0') * (b - '0');
}

long long int karatsuba(char *num1, char *num2) {
    int len = makeEqualLength(&num1, &num2);
    if (len == 1)
        return multiplySingleDigit(num1[0], num2[0]);
    
    int mid = len / 2;
    char *Xl = strndup(num1, mid);
    char *Xr = strdup(num1 + mid);
    char *Yl = strndup(num2, mid);
    char *Yr = strdup(num2 + mid);
    
    long long int P1 = karatsuba(Xl, Yl);
    long long int P2 = karatsuba(Xr, Yr);
    long long int P3 = karatsuba(strdup(Xl) + strdup(Xr), strdup(Yl) + strdup(Yr));
    
    free(Xl); free(Xr); free(Yl); free(Yr);
    
    return P1 * pow(10, 2 * (len - mid)) + (P3 - P1 - P2) * pow(10, len - mid) + P2;
}

int main() {
    char num1[] = "1234";
    char num2[] = "5678";
    printf("Product of %s and %s is %lld\n", num1, num2, karatsuba(num1, num2));
    return 0;
}
