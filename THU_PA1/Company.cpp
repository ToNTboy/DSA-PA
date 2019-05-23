#include <cstdio>
#include <cstring>

#define OFFLINE 0xFFFFFFFF

int main() {
    setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
    setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);

    int n, m;
    unsigned int *staff;
    int online = 0;
    long long int res = 0;

    int *onRecs;
    int rSize = 0;

    scanf("%d %d", &n, &m);
    staff = new unsigned int[n];
    memset(staff, 0xFF, sizeof(int) * n);

    onRecs = new int[m];
    
    char opr[2];
    int id;
    unsigned int code;
    for (int i = 0; i < m; i++) {
        scanf("%s", opr);
        switch (opr[0])
        {
        case 'I':
            scanf("%d %u", &id, &code);
            if (staff[id - 1] == code) {
                break;
            }
            if (staff[id - 1] == OFFLINE) {
                onRecs[rSize] = id - 1;
                rSize++;
                online++;
            }
            staff[id - 1] = code;
            break;
        case 'O':
            scanf("%d", &id);
            if (staff[id - 1] == OFFLINE) {
                break;
            }
            staff[id - 1] = OFFLINE;
            online--;
            break;
        case 'C':
            /* memset(staff, 0xFF, sizeof(int) * n);  -->  O(n*m) */
            for (int j = 0; j < rSize; j++) {
                staff[onRecs[j]] = OFFLINE;
            }
            rSize = 0;
            online = 0;
            break;
        case 'N':
            res += online;
            break;
        case 'Q':
            scanf("%d", &id);
            if (staff[id - 1] == OFFLINE) {
                res += -1;
            } else {
                res += staff[id - 1];
            }
            break;
        }
    }

    printf("%lld\n", res);

    return 0;
}