#include <cstdio>

char A[100001];
char B[100001];


bool compare(char *a, char *b) {
    return false;
}

int main(void) {
    for (;;) {
        scanf("%s %s", A, B);
        if (compare(A, B)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}