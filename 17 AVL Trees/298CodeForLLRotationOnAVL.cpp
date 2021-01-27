#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node* lchild;
    struct Node* rchild;
    int data;
    int height;
}*root=NULL;

int NodeHeight(struct Node *p) {
    int hl, hr;
    hl = p && p->lchild ? p->lchild->height:0;
    hl = p && p->rchild ? p->rchild->height:0;
    return hl>hr ? hl+1 : hr+1;
}

int BalanceFactor(struct Node *p) {
    int hl, hr;
    hl = p && p->lchild ? p->lchild->height:0;
    hl = p && p->rchild ? p->rchild->height:0;
    return hl-hr;
}

struct Node* LLRotation(struct Node *p) {
    struct Node* pl= p->lchild;
    struct Node* plr= pl->rchild;

    pl->rchild = p;
    p->lchild = plr;
    p->height = NodeHeight(p);
    pl->height = NodeHeight(pl);

    if(root==p)
        root = pl;
    return pl;
}

struct Node* LRRotation(struct Node *p) {
    return NULL;
}

struct Node* RRRotation(struct Node *p) {
    return NULL;
}

struct Node* RLRotation(struct Node *p) {
    return NULL;
}

struct Node* RInsert(struct Node *p, int key) {
    struct Node* t = NULL;
    if(p==NULL) {
        t = (struct Node*)malloc(sizeof(struct Node));
        t->lchild = t->rchild = NULL;
        t->data = key;
        t->height = 1;
        return t;
    }
    if(key>p->data)
        p->rchild = RInsert(p->rchild, key);
    else if(key<p->data)
        p->lchild = RInsert(p->lchild, key);
    p->height = NodeHeight(p);
    if(BalanceFactor(p)==2 && BalanceFactor(p->lchild)==1)
        return LLRotation(p);
    else if(BalanceFactor(p)==2 && BalanceFactor(p->lchild)==-1)
        return LRRotation(p);
    else if(BalanceFactor(p)==-2 && BalanceFactor(p->rchild)==-1)
        return RRRotation(p);
    else if(BalanceFactor(p)==-2 && BalanceFactor(p->rchild)==1)
        return RLRotation(p);

    return p;
}

void PreOrder(struct Node* p) {
    if(p) {
        printf("%d ", p->data);
        PreOrder(p->lchild);
        PreOrder(p->rchild);
    }
}

int main() {
    root = RInsert(root, 10);
    RInsert(root, 5);
    RInsert(root, 2);
    PreOrder(root);
}