#include <cstdio>
#include <cstring>

/* error answer, fix later */

#define UNITSIZE 16

struct Entity
{
    char *cs;
    char size;
    Entity *pre;
    Entity *next;
};

struct Cursor
{
    Entity *e;
    int pos;
};

Cursor lc;
Cursor rc;
Entity head;
Entity tail;
int n;

Entity *text;

void prePos(Cursor *c)
{
    if (c->pos > 0)
    {
        c->pos--;
    }
    else if (c->e->pre != &head)
    {
        c->e = c->e->pre;
        c->pos = c->e->size - 1;
    }
}

void nextPos(Cursor *c)
{
    if (c->pos < c->e->size - 1)
    {
        c->pos++;
    }
    else if (c->e->next != &tail)
    {
        c->e = c->e->next;
        c->pos = 0;
    }
}

int main()
{
    char *str = NULL;
    size_t capcity = 0;
    ssize_t size;

    int read = getline(&str, &capcity, stdin);
    size = (read == 0 ? 0 : read - 1);

    // init linked list

    head.size = 0;
    tail.size = 0;
    Entity *pre = &head;
    if (size == 0)
    {
        Entity *e = new Entity();
        e->cs = str;
        e->size = 0;
        e->pre = pre;
        pre->next = e;
        pre = e;
    }
    else
    {
        for (int i = 0; i < (size / UNITSIZE); i++)
        {
            Entity *e = new Entity();
            e->cs = str + i * UNITSIZE;
            e->size = UNITSIZE;
            e->pre = pre;
            pre->next = e;
            pre = e;
        }
        int extra = size % UNITSIZE;
        if (extra)
        {
            Entity *e = new Entity();
            e->cs = str + size - extra;
            e->size = extra;
            e->pre = pre;
            pre->next = e;
            pre = e;
        }
    }
    pre->next = &tail;
    tail.pre = pre;

    lc.e = head.next;
    rc.e = &tail;
    lc.pos = 0;
    rc.pos = 0;

    scanf("%d", &n);

    char opr[2];
    char w[2];
    char ch[2];
    Cursor *cur;
    Cursor *ocur;
    Entity *entity;
    int iPos;
    bool coincide;
    Cursor *lPos = new Cursor();
    Cursor *rPos = new Cursor();
    int lrOrder = (lc.e == rc.e ? (lc.pos == rc.pos ? 0 : 1) : 1);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", opr);
        switch (opr[0])
        {
        case '<':
            scanf("%s", w);
            cur = &(w[0] == 'L' ? lc : rc);
            if (lc.e == rc.e && lc.pos == rc.pos)
            {
                if (cur == &rc)
                {
                    lrOrder = 0;
                }
            }
            if (cur->pos == 0)
            {
                if (cur->e == head.next)
                {
                    printf("F\n");
                    break;
                }
                else
                {
                    cur->e = cur->e->pre;
                    cur->pos = cur->e->size - 1;
                }
            }
            else
            {
                cur->pos--;
            }
            printf("T\n");
            break;
        case '>':
            scanf("%s", w);
            cur = &(w[0] == 'L' ? lc : rc);
            if (lc.e == rc.e && lc.pos == rc.pos)
            {
                if (cur == &lc)
                {
                    lrOrder = 0;
                }
            }
            if (cur->e == &tail)
            {
                printf("F\n");
                break;
            }
            if (cur->pos < cur->e->size - 1)
            {
                cur->pos++;
            }
            else
            {
                cur->e = cur->e->next;
                cur->pos = 0;
            }
            printf("T\n");
            break;
        case 'I':
            scanf("%s", w);
            scanf("%s", ch);
            coincide = (lc.e == rc.e && lc.pos == rc.pos);
            cur = &(w[0] == 'L' ? lc : rc);
            if (cur->e == &tail)
            {
                entity = cur->e->pre;
                iPos = entity->size;
            }
            else
            {
                entity = cur->e;
                iPos = cur->pos;
            }

            if (entity->size == UNITSIZE)
            {
                Entity *ne = new Entity();
                ne->cs = new char[UNITSIZE];
                ne->cs[0] = (iPos == entity->size ? ch[0] : entity->cs[UNITSIZE - 1]);
                ne->size = 1;
                ne->pre = entity;
                ne->next = entity->next;
                entity->next->pre = ne;
                ne->pre->next = ne;
                for (int j = UNITSIZE - 1; j > iPos; j--)
                {
                    entity->cs[j] = entity->cs[j - 1];
                }
                if (iPos == UNITSIZE - 1)
                {
                    entity->cs[iPos] = ch[0];
                    cur->e = entity->next;
                    cur->pos = 0;
                }
                else if (iPos < UNITSIZE - 1)
                {
                    entity->cs[iPos] = ch[0];
                    cur->pos++;
                }
            }
            else
            {
                for (int j = entity->size; j > (iPos); j--)
                {
                    entity->cs[j] = entity->cs[j - 1];
                }
                entity->cs[iPos] = ch[0];
                entity->size++;
                cur->pos += (cur->e == &tail ? 0 : 1);
            }
            if (coincide)
            {
                ocur = (cur == &lc ? &rc : &lc);
                ocur->e = cur->e;
                ocur->pos = cur->pos;
            }
            printf("T\n");
            break;
        case 'D':
            scanf("%s", w);
            coincide = (lc.e == rc.e && lc.pos == rc.pos);
            cur = &(w[0] == 'L' ? lc : rc);
            ocur = (cur == &lc ? &rc : &lc);
            if (cur->e == &tail)
            {
                printf("F\n");
                break;
            }
            entity = cur->e;
            iPos = cur->pos;

            if (ocur->e == cur->e && ocur->pos > cur->pos)
            {
                ocur->pos--;
            }

            for (int j = iPos; j < cur->e->size - 1; j++)
            {
                entity->cs[j] = entity->cs[j + 1];
            }
            entity->size--;
            if (entity->size == 0 && (!(entity->next == &tail && entity->pre == &head)))
            {
                cur->e = cur->e->next;
                cur->pos = 0;
                entity->next->pre = entity->pre;
                entity->pre->next = entity->next;
                delete entity;
            }
            else if (cur->pos == entity->size)
            {
                cur->e = cur->e->next;
                cur->pos = 0;
            }
            if (coincide)
            {
                ocur->e = cur->e;
                ocur->pos = cur->pos;
            }
            printf("T\n");
            break;
        case 'R':
            if (!lrOrder)
            {
                printf("F\n");
                break;
            }
            lPos->e = lc.e;
            lPos->pos = lc.pos;
            rPos->e = rc.e;
            rPos->pos = rc.pos;
            prePos(rPos);
            while ((lPos->e == rPos->e && lPos->pos < rPos->pos) || (lPos->e != rPos->e && rPos->e->next != lPos->e))
            {
                char *l = &(lPos->e->cs[lPos->pos]);
                char *r = &(rPos->e->cs[rPos->pos]);
                *l = *l ^ *r;
                *r = *l ^ *r;
                *l = *l ^ *r;
                nextPos(lPos);
                prePos(rPos);
            }
            printf("T\n");
            break;
        case 'S':
            entity = head.next;
            while (entity != &tail)
            {
                for (int j = 0; j < entity->size; j++)
                {
                    printf("%c", entity->cs[j]);
                }
                entity = entity->next;
            }
            printf("\n");
            break;
        case 'A':
            printf("head->");
            entity = head.next;
            while (entity != &tail)
            {
                printf("%d:", entity->size);
                for (int j = 0; j < entity->size; j++)
                {
                    printf("%c", entity->cs[j]);
                }
                entity = entity->next;
                printf("->");
            }
            printf("tail");
            printf("\n");
            printf("lc=%d,%d;rc=%d,%d;\n", lc.e == &tail, lc.pos, rc.e == &tail, rc.pos);
            break;
        }
    }

    return 0;
}