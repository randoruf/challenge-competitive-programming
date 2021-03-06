#include<iostream>
#include<cstdio>
using namespace std;
const int MAX = 100005;
struct Node {
    int key;
    Node *parent, *left, *right;
};
Node *root, *NIL;

//前序排序
void PreorderTreeWalk(Node *u) {
    if (u == NIL)
        return;
    printf(" %d", u->key);
    PreorderTreeWalk(u->left);
    PreorderTreeWalk(u->right);
}
//中序排序
void InorderTreeWalk(Node *u) {
    if (u == NIL)
        return;
    InorderTreeWalk(u->left);
    printf(" %d", u->key);
    InorderTreeWalk(u->right);
}


void insert(int value) {
    Node *y = NIL, *x = root;
    Node *z = new Node();
    z->key = value;
    z->left = z->right = NIL;

    // 从根结点往下遍历
    while (x != NIL) {
        y = x;
        // z 比 x 小， 则从x的左侧遍历
        // z 比 x 大， 则从x的右侧遍历
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    // 没有父结点的是root
    if (y == NIL) {
        root = z;
    }
    else {
        // z 比 y 小， 则在y的左侧
        // z 比 y 大， 则在y的右侧
        if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
    }
}

Node * find(Node *u, int value) {

    // 从根结点开始遍历下去
    while (u != NIL && u->key != value) {
        if (value < u->key)
            u = u->left;
        else
            u = u->right;
    }
    return u;
}

// 树的最小值
Node *treeMinimum(Node * x) {
    while (x->left != NIL)
        x = x->left;
    return x;
}

// case 3 ,搜索后一个结点
Node *treeSuccessor(Node *x) {
    if (x->right != NIL)
        return treeMinimum(x->right);

    Node *y = x->parent;
    while (y != NIL && x == y->right) {
        x = y;
        x = y->parent;
    }
    return y;
}

void treeDelete(Node * z) {
    Node *y, *x;  // 要删除的对象和y的子结点

    // 确定要删除的结点
    if (z->left == NIL || z->right == NIL)
        y = z;
    else
        y = treeSuccessor(z);

    // 确定y的子结点x
    if (y->left != NIL)
        x = y->left;
    else
        x = y->right;

    // 让子结点链接父结点
    if (x != NIL)
        x->parent = y->parent;

    // 让父结点链接子结点
    if (y->parent == NIL)
        root = x;
    else {
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }

    // case 3
    if (y != z)
        z->key = y->key;

    delete y;
}

int main() {
    int n, value;
    Node * f;
    char s[200];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        if (s[0] == 'i') {
            scanf("%d", &value);
            insert(value);
        }
        else if (s[0] == 'f') {
            scanf("%d", &value);
            f = find(root, value);
            if (f != NIL)
                printf("yes\n");
            else
                printf("no\n");
        }
        else if (s[0] == 'd') {
            scanf("%d", &value);
            treeDelete(find(root, value));
        }
        else {
            InorderTreeWalk(root);
            printf("\n");
            PreorderTreeWalk(root);
            printf("\n");
        }
    }

    return 0;
}
