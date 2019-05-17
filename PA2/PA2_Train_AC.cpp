#include <cstdio>

#define PUSH 1
#define POP  0

class Stack {
public:
    Stack(int n) {
        stack = new int[n];
        oprs = new int[n << 1];
        size = 0;
        opri = 0;
    }
    ~Stack() {
        delete stack;
        delete oprs;
    }
    void push(int begin, int end) {
        for (; begin <= end; begin++) {
            stack[size++] = begin;
            oprs[opri++] = PUSH;
        }
    }
    int pop() {
        --size;
        oprs[opri++] = POP;
        return size < 0? -1: stack[size];
    }
    void printOprs() {
        for (int i = 0; i < opri; i++) {
            switch (oprs[i])
            {
            case PUSH:
                printf("push\n");
                break;
            case POP:
                printf("pop\n");
                break;
            default:
                break;
            }
        }
    }
private:
    int *stack;
    int *oprs;
    int size;
    int opri;
};

int main () {
    int slen = 0, si = 0;
    int *seq;
    int n, m;

    scanf("%d %d", &n, &m);
    Stack s(n);
    seq = new int[n];
    for (int i = 0; i < n; i++) scanf("%d", &seq[i]);

    int max = 0;
    do {
        if (seq[si] > max) {
            s.push(max + 1, seq[si]);
            slen += (seq[si]- max);
            if (slen > m) {
                printf("No\n");
                return 0;
            }
            s.pop();
            slen--;
            max = seq[si];
        } else if (seq[si] == s.pop()) {
            slen--;
        } else {
            printf("No\n");
            return 0;
        }
        si++;
    } while (si < n);

    s.printOprs();

    return 0;
}