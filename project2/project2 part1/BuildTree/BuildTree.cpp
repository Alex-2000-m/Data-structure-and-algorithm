// BuildTree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

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

//构造二叉树
TreeNode* buildTree(char* preorder, int preorderSize, char* inorder, int inorderSize) {
    //这里是为了判断当前递归轮次传进来的有没有子树，没有就意味着当前子树的根节点是NULL
    //preorderSize和inorderSize数值是一样的，不可能一个为0另一个不为0
    if (preorderSize == 0 || inorderSize == 0) {
        return NULL;
    }
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    int index;
    //先序第一个是当前根节点，先处理
    if (preorder[0] == '\0') {
        return NULL;
    }
    else {
        root->val = preorder[0];
    }
    //在中序遍历中找当前根节点
    for (index = 0; index < inorderSize; index++) {
        if (inorder[index] == preorder[0]) {
            break;
        }
    }
    //重构左子树的先序遍历和中序遍历，递归调用
    root->left = buildTree(preorder + 1, index, inorder, index);
    //重构右子树的先序遍历和中序遍历，递归调用
    root->right = buildTree(preorder + index + 1, preorderSize - index - 1, inorder + index + 1, preorderSize - index - 1);
    //向上返回当前递归的根节点
    return root;
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
    char preorder[100];
    char inorder[100];
    TreeNode* root = new TreeNode;
    char result[100];

    printf("输入先序遍历结果：\n");
    do { 
        scanf_s("%s", preorder, 100);
    } while (getchar() != '\n');

    printf("输入中序遍历结果：\n");
    do {
        scanf_s("%s", inorder, 100); 
    } while (getchar() != '\n');

    int preorderSize = sizeof(preorder) / sizeof(preorder[0]);
    int inorderSize = sizeof(inorder) / sizeof(inorder[0]);

    if (preorderSize != inorderSize) {
        printf("输入有误！\n");
        return 0;
    }

    root = buildTree(preorder, preorderSize, inorder, inorderSize);

    display(root);
    return 0;
}

