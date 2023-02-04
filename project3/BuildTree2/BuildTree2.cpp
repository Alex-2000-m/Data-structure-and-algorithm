#include <stdio.h>
#include <malloc.h>
#include <iostream>
#include <cstring>

using namespace std;

struct TreeNode {
    char val;
    TreeNode* left;
    TreeNode* right;
};

int num = 0;


//构造二叉树
//left和right表示当前递归的子树的左右边界

struct TreeNode* buildTree(char* inorder, int inorderSize, char* postorder, int postorderSize) {    //自顶向下递归法
    if (inorderSize < 1) {
        return NULL;
    }
    int size = inorderSize; //两个数组大小相等
    char tmp = postorder[postorderSize - 1];
    int i;
    for (i = 0; i < inorderSize; i++)
    {
        if (inorder[i] == tmp)
            break;
    }
    //size值的更新
    int leftSize = i; 
    int rightSize = size - i - 1;
    //传递数组的指针
    char* left = inorder; 
    char* right = inorder + i + 1;  
    char* leftPos = postorder; 
    char* rightPos = postorder + i;
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->val = tmp;
    root->left = buildTree(left, leftSize, leftPos, leftSize);
    root->right = buildTree(right, rightSize, rightPos, rightSize);
    return root;
}



//计算二叉树高度
int treeHight(TreeNode* root) {
    int left = 1;
    int right = 1;
    if (root == NULL || root->val == ' ') {
        return 0;
    }
    left += treeHight(root->left);
    right += treeHight(root->right); 
    return left > right ? left : right;
}



//计算叶子节点
int countLeave(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        num++;
    }
    countLeave(root->left);
    countLeave(root->right);
    return num;
}


//输出二叉树广义表
void display(TreeNode* root)
{
    printf("%c", root->val);
    if (root->left == NULL && root->right == NULL)
        return;
    printf("(");
    if (root->left == NULL)
        printf("Null,");
    else
    {
        display(root->left);
        printf(",");
    }
    if (root->right == NULL)
        printf("Null");
    else
        display(root->right);
    printf(")");
}



int main()
{
    char inorder[100];
    char postorder[100];
    /*char postorder[] = {'B','H','E','C','I','G','F','A','D','\0'};
    char inorder[] = {'D','C','B','E','H','A','G','I','F','\0'};*/
    TreeNode* root = new TreeNode;

    printf("输入中序遍历结果：\n");
    do {
        scanf_s("%s", inorder, 100);
    } while (getchar() != '\n');

    printf("输入后序遍历结果：\n");
    do {
        scanf_s("%s", postorder, 100);
    } while (getchar() != '\n');

    int inorderSize = 0;
    int postorderSize = 0;
    for (int i = 0; i < 100; i++) {
        if (inorder[i] == '\0') {
            break;
        }
        else {
            inorderSize++;
        }
    }

    for (int i = 0; i < 100; i++) {
        if (postorder[i] == '\0') {
            break;
        }
        else {
            postorderSize++;
        }
    }

    if (postorderSize != inorderSize) {
        printf("输入有误！\n");
        return 0;
    }

    root = buildTree(inorder, inorderSize, postorder, postorderSize);
    int TreeHight = treeHight(root);
    printf("树的高度为%d\n", TreeHight);
    int LeaveNum = countLeave(root);
    printf("树的叶子节点个数为%d\n", LeaveNum);
    display(root);
    return 0;
}