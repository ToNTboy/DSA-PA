#include <cstdio>

int *preorder;
int *postorder;
int *inorder;
int cur = 0;

int treeSize(int root, int lo, int hi) {
    for (int i = lo; i < hi; i++) {
        if (postorder[i] == root) return i - lo + 1;
    }
    return -1;
}

void childTreeTraversal(int prelo, int prehi, int postlo, int posthi) {
    int root = preorder[prelo];
    if (prehi - prelo == 1) {
        inorder[cur++] = root;
        return;
    }
    int lchild = preorder[prelo + 1];
    int lsize = treeSize(lchild, postlo, posthi);
    int rsize = prehi - prelo - lsize - 1;
    childTreeTraversal(prelo + 1, prelo + lsize + 1, postlo, postlo + lsize);    // left child tree
    inorder[cur++] = root;
    childTreeTraversal(prelo + lsize + 1, prehi, postlo + lsize, posthi - 1);    // right child tree
}

int main() {
    // accept input
    int n = 0;
    scanf("%d", &n);
    preorder = new int[n];
    postorder = new int[n];
    inorder = new int[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &preorder[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &postorder[i]);
    }

    // traversal
    childTreeTraversal(0, n, 0, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", inorder[i]);
    }
    printf("\n");
    return 0;
}