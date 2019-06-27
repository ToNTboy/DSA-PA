#include "temperature.h"
#include <cstdio>

#define VERTICAL 0
#define HORIZONTAL 1

long long tempSum;
int count;

struct Node
{
    Node *lc;
    Node *rc;
    long long temp;
    int x;
    int y;
    int tl;
    int bl;
    int splitDirection;
};

void mergeByX(Node **nodes, int &lo, int &mi, int &hi)
{
    Node **A = nodes + lo;
    int lb = mi - lo;
    int lc = hi - mi;
    Node **B = new Node *[lb];
    for (int i = 0; i < lb; i++)
    {
        B[i] = A[i];
    }
    Node **C = nodes + mi;
    for (int i = 0, j = 0, k = 0; j < lb;)
    {
        if (k < lc && C[k]->x < B[j]->x)
            A[i++] = C[k++];
        if (lc <= k || B[j]->x <= C[k]->x)
            A[i++] = B[j++];
    }
    delete B;
}

void mergeByY(Node **nodes, int &lo, int &mi, int &hi)
{
    Node **A = nodes + lo;
    int lb = mi - lo;
    int lc = hi - mi;
    Node **B = new Node *[lb];
    for (int i = 0; i < lb; i++)
    {
        B[i] = A[i];
    }
    Node **C = nodes + mi;
    for (int i = 0, j = 0, k = 0; j < lb;)
    {
        if (k < lc && C[k]->y < B[j]->y)
            A[i++] = C[k++];
        if (lc <= k || B[j]->y <= C[k]->y)
            A[i++] = B[j++];
    }
    delete B;
}

void sortNodes(Node **nodes, int &lo, int &hi, int &by)
{
    if (hi - lo < 2)
        return;
    int mi = (lo + hi) >> 1;
    sortNodes(nodes, lo, mi, by);
    sortNodes(nodes, mi, hi, by);
    if (by)
    {
        mergeByX(nodes, lo, mi, hi);
    }
    else
    {
        mergeByY(nodes, lo, mi, hi);
    }
}

Node *buildKdTree(Node **nodes, int lo, int hi, int depth)
{
    int dir = (depth % 2 ? VERTICAL : HORIZONTAL);
    if (hi - lo == 1)
    {
        Node *node = nodes[lo];
        node->bl = (dir == HORIZONTAL ? node->x : node->y);
        node->tl = node->bl;
        return node;
    }
    sortNodes(nodes, lo, hi, dir);
    int mi = (lo + hi) >> 1;
    nodes[mi]->splitDirection = dir;
    nodes[mi]->tl = (dir == HORIZONTAL ? nodes[hi - 1]->x : nodes[hi - 1]->y);
    nodes[mi]->bl = (dir == HORIZONTAL ? nodes[lo]->x : nodes[lo]->y);
    nodes[mi]->lc = buildKdTree(nodes, lo, mi, depth + 1);
    nodes[mi]->rc = buildKdTree(nodes, mi, hi, depth + 1);
    return nodes[mi];
}

void reportTree(Node *root)
{
    tempSum += root->temp;
    count++;
    if (root->lc != NULL)
    {
        reportTree(root->lc);
        reportTree(root->rc);
    }
}

void kdSearch(Node *tree, int &x1, int &y1, int &x2, int &y2)
{
    if (x1 <= tree->x && tree->x <= x2 && y1 <= tree->y && tree->y <= y2)
    {
        tempSum += tree->temp;
        count++;
    }

    if (tree->lc == NULL)
    {
        return;
    }

    if (tree->splitDirection == HORIZONTAL)
    {
        if (x1 <= tree->bl && tree->x <= x2 && y1 <= tree->lc->bl && tree->lc->tl <= y2)
        {
            reportTree(tree->lc);
        }
        else if (!tree->x < x1 && !x2 < tree->bl && !tree->lc->tl < y1 && !y2 < tree->lc->bl)
        {
            kdSearch(tree->lc, x1, y1, x2, y2);
        }

        if (tree->tl <= x2 && x1 <= tree->x && y1 <= tree->rc->bl && tree->rc->tl <= y2)
        {
            reportTree(tree->rc);
        }
        else if (!x2 < tree->x && !tree->tl < x1 && !tree->rc->tl < y1 && !y2 < tree->rc->bl)
        {
            kdSearch(tree->rc, x1, y1, x2, y2);
        }
    }
    else
    {
        if (y1 <= tree->bl && tree->y <= y2 && x1 <= tree->lc->bl && tree->lc->tl <= x2)
        {
            reportTree(tree->lc);
        }
        else if (!tree->y < y1 && !y2 < tree->bl && !tree->lc->tl < x1 && !x2 < tree->lc->bl)
        {
            kdSearch(tree->lc, x1, y1, x2, y2);
        }

        if (tree->tl <= y2 && y1 <= tree->y && x1 <= tree->rc->bl && tree->rc->tl <= x2)
        {
            reportTree(tree->rc);
        }
        else if (!y2 < tree->y && !tree->tl < y1 && !tree->rc->tl < x1 && !x2 < tree->rc->bl)
        {
            kdSearch(tree->rc, x1, y1, x2, y2);
        }
    }
}

int main(void)
{
    int n = GetNumOfStation();
    Node **nodes = new Node *[n];
    int x, y, temp;

    for (int i = 0; i < n; i++)
    {
        GetStationInfo(i, &x, &y, &temp);
        nodes[i] = new Node();
        nodes[i]->temp = (long long)temp;
        nodes[i]->x = x;
        nodes[i]->y = y;
        nodes[i]->lc = NULL;
        nodes[i]->rc = NULL;
    }
    Node *tree = buildKdTree(nodes, 0, n, 0);

    int x1, y1, x2, y2;
    while (GetQuery(&x1, &y1, &x2, &y2))
    {
        tempSum = 0;
        count = 0;
        kdSearch(tree, x1, y1, x2, y2);
        Response(count == 0 ? 0 : tempSum / count);
    }

    return 0;
}