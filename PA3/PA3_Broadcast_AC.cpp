#include <cstdio>
#include <cstring>

#define UNDISCOVERED 0
#define DISCOVERED 1
#define VISITED 2

struct Alist
{
    Alist *next;
    void *elem;
};

struct Vertex
{
    int fm;
    int adj;
    int state;
    Alist *list;
    Alist *last;
};

class Queue
{
public:
    Queue(int n)
    {
        capcity = n;
        size = 0;
        head = tail = 0;
        queue = new Vertex *[n];
    }
    void enque(Vertex *v)
    {
        if (size < capcity)
        {
            size++;
            queue[tail] = v;
            tail = (tail - 1 + capcity) % capcity;
        }
    }
    Vertex* deque()
    {
        if (size == 0)
            return NULL;
        size--;
        Vertex *v = queue[head];
        head = (head - 1 + capcity) % capcity;
        return v;
    }
    bool empty()
    {
        return size == 0;
    }

private:
    int size;
    int capcity;
    int head;
    int tail;
    Vertex **queue;
};

class Graph
{
public:
    bool conflict;
    int count;

    Graph(int n)
    {
        count = 0;
        vn = n;
        conflict = false;
        vs = new Vertex[vn];
        adjv = new Vertex *[vn];
        memset(adjv, 0x00, sizeof(Vertex *) * vn);
        memset(vs, 0x00, sizeof(Vertex) * vn);
    }
    void insertEdge(int fr, int to)
    {
        Vertex *vfr = &vs[fr];
        Vertex *vto = &vs[to];

        if (vfr->adj == 0)
        {
            vfr->adj = 1;
            adjv[count] = vfr;
            count++;
        }
        if (vto->adj == 0)
        {
            vto->adj = 1;
            adjv[count] = vto;
            count++;
        }

        if (vfr->list == NULL)
        {
            vfr->list = new Alist();
            vfr->last = vfr->list;
            vfr->last->elem = vto;
            vfr->last->next = NULL;
        }
        else
        {
            Alist *adj = new Alist();
            adj->elem = vto;
            adj->next = NULL;
            vfr->last->next = adj;
            vfr->last = adj;
        }
        
        if (vto->list == NULL)
        {
            vto->list = new Alist();
            vto->last = vto->list;
            vto->last->elem = vfr;
            vto->last->next = NULL;
        }
        else
        {
            Alist *adj = new Alist();
            adj->elem = vfr;
            adj->next = NULL;
            vto->last->next = adj;
            vto->last = adj;
        }
    }
    bool bfs()
    {
        for (int i = 0; i < count; i++)
        {
            if (adjv[i]->state == UNDISCOVERED)
            {
                if (!BFS(adjv[i]))
                    return false;
            }
        }
    }
    bool BFS(Vertex *r)
    {
        Queue q(vn);
        r->state = DISCOVERED;
        q.enque(r);
        while (!q.empty())
        {
            Vertex *v = q.deque();
            for (Alist *a = v->list; a != NULL; a = a->next)
            {
                Vertex *c = (Vertex *)(a->elem);
                switch (c->state)
                {
                case UNDISCOVERED:
                    c->state = DISCOVERED;
                    c->fm = !v->fm;
                    q.enque(c);
                    break;
                case DISCOVERED:
                case VISITED:
                    if (c->fm == v->fm)
                    {
                        conflict = true;
                        return false;
                    }
                    break;
                }
            }
            v->state = VISITED;
        }
        return true;
    }

private:
    Vertex *vs;
    Vertex **adjv;
    int vn;
};

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    Graph g(n);
    int fr, to;
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &fr, &to);
        g.insertEdge(fr - 1, to - 1);
    }

    g.bfs();

    if (g.conflict)
    {
        printf("%d\n", -1);
    }
    else
    {
        printf("%d\n", 1);
    }

    return 0;
}