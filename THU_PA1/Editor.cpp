#include <cstdio>
#include <cstring>

int L;
int R;
int n;

int main() {
    char *str = NULL;
    size_t len = 0;
    ssize_t read;

    read = getline(&str, &len, stdin);
    scanf("%d", &n);

    char opr;
    for (int i = 0; i < n; i++) {
        scanf("%c", &opr);
        switch (opr)
        {
        case '<':
            break;
        case '>':
            break;
        case 'I':
            break;
        case 'D':
            break;
        case 'R':
            break;
        case 'S':
            break;
        }
    }

    return 0;
}