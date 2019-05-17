#include <cstdio>

#define UNDISCOVERED 0
#define VISITED 1

struct Alist {
    Alist *next;
    void *v;
};

struct Vertex {
    int inDegree;
    int after;
    int state;
    Alist *list;
    Alist *last;
};

class Graph {
public:
    int max;
    Graph(int n) {
        vn = n;
        vs = new Vertex[vn];
        for (int i = 0; i < vn; i++) {
            vs[i].inDegree = 0;
            vs[i].after = 0;
            vs[i].state = UNDISCOVERED;
            vs[i].list = NULL;
            vs[i].last = NULL;
        }
        max = 0;
        cur = 0;
    }
    ~Graph() {
    }
    void insertEdge(int fr, int to) {
        vs[to].inDegree++;
        if (vs[fr].list == NULL) {
            vs[fr].list = new struct Alist();
            vs[fr].list->next = NULL;
            vs[fr].list->v = &vs[to];
            vs[fr].last = vs[fr].list;
        } else {
            struct Alist *node = new Alist();
            node->next = NULL;
            node->v = &vs[to];
            vs[fr].last->next = node;
            vs[fr].last = node;
        }
    }
    void reset() {
        cur = 0;
    }
    void dfs(Vertex *v) {
        ++cur;
        if (cur > max) max = cur;
        for (Alist *a = v->list; a != NULL; a = a->next) {
            Vertex *nextv = ((Vertex*)a->v);
            switch (nextv->state) {
                case UNDISCOVERED:
                    dfs(nextv);
                    if (v->after < (nextv->after + 1)) {
                        v->after = (nextv->after + 1);
                    }
                    break;
                case VISITED:
                    if (v->after < (nextv->after + 1)) {
                        v->after = (nextv->after + 1);
                    }
                    if ((cur + nextv->after + 1) > max) {
                        max = (cur + nextv->after + 1);
                    }
                    break;
                default:
                    /* error input */
                    break;
            }
        }
        v->state = VISITED;
        --cur;
    }
    void DFS() {
        for (int i = 0; i < vn; i++) {
            if (vs[i].inDegree == 0) {
                dfs(&vs[i]);
                reset();
            }
        }
    }
private:
    int vn;
    struct Vertex *vs;
    int cur;
};

int main() {
    setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
    setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);

    // accept input
    int n, m;
    scanf("%d %d", &n, &m);
    int edge[m << 1];
    Graph g(n);
    for (int i = 0; i < (m << 1); i += 2) {
        scanf("%d %d", &edge[i], &edge[i + 1]);
    }

    for (int i = 0; i < (m << 1); i += 2) {
        g.insertEdge(edge[i] - 1, edge[i + 1] - 1);
    }

    // DFS
    g.DFS();

    printf("%d\n", g.max);

    return 0;
}