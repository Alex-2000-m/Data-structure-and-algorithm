#include <iostream>
#include <stdio.h>

#define ENDKEY 65535
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))

struct BSTNode {
    int key;
    BSTNode* Lchild;
    BSTNode* Rchild;
};

//排序

//递归
void  Insert_BST(BSTNode*& T, int key) {
    if (T == NULL) {
        BSTNode* x;
        x = (BSTNode*)malloc(sizeof(BSTNode));
        x->key = key;
        x->Lchild = NULL;
        x->Rchild = NULL;
        T = x;
        return;
    }
    else {
        if (EQ(T->key, key)) {
            return;
        }else if(LT(key,T->key)){
            Insert_BST(T->Lchild, key);
        }else{
            Insert_BST(T->Rchild, key);
        }
    }
}

//中序遍历二叉树
void Inorder(BSTNode* T) {
    if (T == NULL) {
        return;
    }
    if (T->key == -1) {
        printf("树为空！\n");
        return;
    }
    else {
        Inorder(T->Lchild);
        printf("%d ", T->key);
        Inorder(T->Rchild);
    }
}

//删除
void deleteNode(BSTNode*& T, int key) {
    if (T == NULL) {
        printf("BST树为空！\n");
        return;
    }
    else {
        BSTNode* front = T;
        BSTNode* later = NULL;
        //退出情况：1.没找到目标2.找到了
        while (front != NULL && !EQ(front->key, key)) {
            later = front;
            //判断走哪一条分支
            if (LT(key, front->key)) {
                front = front->Lchild;
            }
            else {
                front = front->Rchild;
            }
        }
        //判断是哪种情况
        if (front == NULL) {
            printf("要删除的目标节点不存在！\n");
            return;
        }
        //找到节点了
        //目标节点是叶子节点
        if (front->Lchild == NULL && front->Rchild == NULL) {
            if (later == NULL) {
                front->key=-1;
                return;
            }
            if (later->Lchild!=NULL && later->Lchild->key == front->key) {
                later->Lchild = NULL;
            }
            else
            {
                later->Rchild = NULL;
            }
            return;
        }
        //目标只有一个子树
        if (front->Lchild != NULL && front->Rchild == NULL) {
            if (later == NULL) {
                T = front->Lchild;
                return;
            }
            if (front->key > later->key) {
                later->Rchild = front->Lchild;
            }
            else {
                later->Lchild = front->Lchild;
            }
            return;
        }
        if (front->Lchild == NULL && front->Rchild != NULL) {
            if (later == NULL) {
                T = front->Rchild;
                return;
            }
            if (front->key > later->key) {
                later->Rchild = front->Rchild;
            }
            else {
                later->Lchild = front->Rchild;
            }
            return;
        }
        //目标有两个子树，使用前驱节点代替
        if (front->Lchild != NULL && front->Rchild != NULL) {
            later = front;
            BSTNode* s = front->Lchild;
            while (s->Rchild != NULL) {
                later = s;
                s = s->Rchild;
            }
            front->key = s->key;
            if (s->key == front->Lchild->key) {
                front->Lchild = s->Lchild;
            }
            else {
                later->Rchild = NULL;
            }
            return;
        }
    }
}




int main()
{
    int key;
    BSTNode* BSTtree = NULL;
    int temp = -1;
    while (1) {
        if (temp == -1) {
            printf("按0创建BST树，按1中序遍历BST树，按2删除BST树中节点,按q退出\n");
        }
        temp = getchar();
        switch (temp) {
        case '0':
            printf("输入树的所有节点！\n");
            do {
                scanf_s("%d", &key);
                Insert_BST(BSTtree, key);
            } while (getchar() != '\n');
            printf("BST树创建完毕！\n");
            temp = -1;
            if (BSTtree->key == -1) {
                return 0;
            }
            break;
        case '1':
            printf("中序遍历结果如下：\n");
            Inorder(BSTtree);
            printf("\n");
            temp = -1;
            if (BSTtree->key == -1) {
                return 0;
            }
            break;
        case '2':
            printf("请输入要删除的节点数值:\n");
            int Dkey;
            scanf_s("%d", &Dkey);
            deleteNode(BSTtree, Dkey);
            temp = -1;
            if (BSTtree->key == -1) {
                return 0;
            }
            break;
        case 'q':
            return 0;
        default:
            break;
        }
    }
}

