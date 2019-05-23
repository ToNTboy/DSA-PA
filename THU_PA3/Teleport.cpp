#include <cstdio>
#include <cstring>

#define UNDISCOVERED 0
#define DISCOVERED 1
#define VISITED 2
#define LOOP 3

struct Alist {
    Alist *next;
    void *elem;
};

struct Vertex {
    int cur;
    int after;
    bool core;
    int state;
    Alist *list;
    Alist *last;
};

class Graph {
public:
    Graph(int n, char *cores) {
        max = 0;
        vn = n;
        vs = new Vertex[vn];
        for (int i = 0; i < vn; i++) {
            vs[i].cur = 0;
            vs[i].after = 0;
            vs[i].core = (cores[i] == 'm'? true : false);
            vs[i].state = UNDISCOVERED;
            vs[i].list = NULL;
            vs[i].last = NULL;
        }
    }
    void insertEdge(int fr, int to) {
        Vertex *vfr = &vs[fr];
        Vertex *vto = &vs[to];
        if (vfr->list == NULL) {
            vfr->list = new Alist();
            vfr->last = vfr->list;
            vfr->last->elem = vto;
            vfr->last->next = NULL;
        } else {
            Alist *adj = new Alist();
            adj->elem = vto;
            adj->next = NULL;
            vfr->last->next = adj;
            vfr->last = adj;
        }
    }
    int dfs(Vertex *r) {
        r->state = DISCOVERED;
        if (r->list != NULL) {
            for (Alist *a = r->list; a != NULL; a = a->next) {
                Vertex *c = (Vertex*)(a->elem);
                switch (c->state)
                {
                case UNDISCOVERED:
                    r->after += dfs(c);
                    break;
                case DISCOVERED:
                case LOOP:
                    c->state = LOOP;
                    break;
                case VISITED: // 0
                    break;
                }
            }
        }
        if (r->state == LOOP) {
            
        }
        r->state = VISITED;
        return 0;
    }
private:
    Vertex *vs;
    int vn;
    int max;
};

int main() {
    setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
    setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);

    return 0;
}