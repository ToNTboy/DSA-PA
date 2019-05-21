#include <cstdio>

int main() {
    // accept input
    int n, k;
    int *m;
    int *A, *B, *C;
    scanf("%d", &n);
    m = new int[n];
    A = new int[n + 1]; A[n] = 0;
    B = new int[n + 1]; B[n] = 0;
    C = new int[n + 1]; C[n] = 0;
    for (int i = 0; i < n; i++) {
        m[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &B[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &C[i]);
    }
    scanf("%d", &k);

    // judge
    int *prefer[3];
    prefer[0] = A;
    prefer[1] = B;
    prefer[2] = C;
    for (int i = 0; i < n; i++) {
        int *cur = prefer[i % 3];
        int *ci = &cur[n];
        while (m[cur[*ci] - 1] != 0) {
            (*ci)++;
        }

        if (cur[*ci] == k) {    // output result
            char coach;
            switch (i % 3)
            {
                case 0:
                    coach = 'A';
                    break;
                case 1:
                    coach = 'B';
                    break;
                case 2:
                    coach = 'C';
                    break;
                default:
                    break;
            }
            printf("%c\n", coach);
            break;
        }

        m[cur[*ci] - 1] = -1;
        (*ci)++;
    }
    
    return 0;
}