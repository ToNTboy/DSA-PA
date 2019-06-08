#include "temperature.h"

#define VERTICAL 0
#define HORIZONTAL 1

long long tempSum;
int count;

struct Node {
    Node *lc;
    Node *rc;
    long long temp;
    int x;
    int y;
    int splitDirection;
};

void merge(Node **nodes, int & lo, int & mi, int & hi, int & by) {

}

void sortNodes(Node **nodes, int & lo, int & hi, int & by) {
    if (hi - lo < 2) return;
    int mi = (lo + hi) >> 1;
    sortNodes(nodes, lo, mi, by);
    sortNodes(nodes, mi, hi, by);
    merge(nodes, lo, mi, hi, by);
}

Node * buildKdTree(Node **nodes, int lo, int hi, int depth) {
    
    return 0;
}

void kdSearch(Node *tree, int & x1, int & y1, int & x2, int & y2) {

}

int main(void){
    int n = GetNumOfStation();
    Node **nodes = new Node*[n];
    int x, y, temp;

    for(int i = 0; i < n; i++) {
        GetStationInfo(i, &x, &y, &temp);
        nodes[i] = new Node();
        nodes[i]->temp = (long long)temp;
        nodes[i]->x = x;
        nodes[i]->y = y;
    }
    Node *tree = buildKdTree(nodes, 0, n, 0);

    int x1, y1, x2, y2;
    while (GetQuery(&x1, &y1, &x2, &y2)) {
        tempSum = 0;
        count = 0;
        kdSearch(tree, x1, y1, x2, y2);
        Response(count == 0? 0 : tempSum / count);
    }
    
    return 0;
}