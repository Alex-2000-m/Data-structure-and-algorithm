// NameTree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stdio.h>

#define MAXNUM 100

using namespace std;

int flag = 0;
int flag2 = 0;
char leftChar;
char rightChar;

struct TreeNode {
    char val = ' ';
    TreeNode* left = NULL;
    TreeNode* right = NULL;
};

//构造树
TreeNode* buildTree(char* name, TreeNode* &root) {
    //已经到了人名的末尾了
    if (name[0] == '\0') {
        return NULL;
    }
    //判断当前要插入的位置是NULL还是已经有数值占据，有数值占据要比较是否相同
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = name[0];
    node->left = NULL;
    node->right = NULL;
    //左子节点为null
    if (root->left==NULL) {
        root->left = node;
        buildTree(name + 1, root->left);
    }
    //左边被占据且不能共用，右子节点为null
    else if (root->left->val != name[0] && root->right == NULL) {
        root->right = node;
        buildTree(name + 1, root->right);
    }
    //左边被占据但可以共用
    else if (root->left->val == name[0]) {
        buildTree(name + 1, root->left);
    }
    //左右两边都满了，但右节点可以可以共用
    else if (root->left->val != name[0] && root->right->val == name[0]) {
        buildTree(name + 1, root->right);
    }
    //其他情况返回null，不能再插入了
    else {
        printf("超出二叉树限制，不能再插入了!\n");
        return NULL;
    }
}



//查找人名
int checkName(TreeNode* &node, char* name) {
    if (node == NULL) {
        if (flag == 0) {
            printf("树为空！\n");
            return 0;
        }
        else {
            return 0;
        }
    }
    //如果当前节点不匹配
    else if (node->val != name[0]) {
        //假如是根节点
        if (flag == 0) {
            flag = 1;
            flag2 = checkName(node->left, name);
            if (flag2 == 2) {
                return 2;
            }
            flag2 = checkName(node->right, name);
            if (flag2 == 2) {
                return 2;
            }
        }
        //不是根节点
        else if (node->left == NULL && node->right == NULL) {
            if ((name + 1)[0] != '\0') {
                return 0;
            }
        }
        else if (node->left != NULL && node->left->val != name[0]) {
            return 0;
        }
        else if (node->right != NULL && node->right->val == name[0]) {
            return 0;
        }
    }
    //当前节点匹配
    else if (node->val == name[0]) {
        //人名到头了
        if ((name + 1)[0] == '\0') {
                return 2;
        }
        //人名没到头
        else {
            flag2=checkName(node->left, name + 1);
            if (flag2 == 2) {
                return 2;
            }
            flag2=checkName(node->right, name + 1);
            if (flag2 == 2) {
                return 2;
            }
        }
    }
}

//先序遍历打印人名
int preorderPrint(TreeNode* &root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        printf("%c", root->val);
        printf("\n");
        return 1;
    }
    else {
        if (flag == 0) {
            flag = 1;
            preorderPrint(root->left);
            preorderPrint(root->right);
        }
        else {
            printf("%c", root->val);
            preorderPrint(root->left);
            preorderPrint(root->right);
        }
    }
}


void main()
{
    TreeNode* root = new TreeNode;
    char inputname[20];
    int result;
    printf("按0开始创建树，按1搜索人名，按2先序遍历打印人名，按q退出！\n");
    while (1) {
        char temp = getchar();
        switch (temp)
        {
        case '0':
            printf("输入要插入的名字：\n");
            do {
                scanf_s("%s", inputname, 20); //可以在一行输入多个name，每个name之间有空格
                buildTree(inputname, root);
            } while (getchar() != '\n');
            break;
        case '1':
            printf("输入要搜索的名字：\n");
            scanf_s("%s", inputname, 20);
            result = checkName(root, inputname);
            if (result == 2) {
                printf("搜索的人名存在！\n");
                flag = 0;
                break;
            }
            else if (result == 0) {
                printf("搜索的人名不存在！\n");
                flag = 0;
                break;
            }
        case '2':
            printf("遍历结果如下：\n");
            leftChar = root->left->val;
            rightChar = root->right->val;
            preorderPrint(root);
            flag = 0;
            break;
        case 'q':
            return;
        default:
            break;
        }
    }
}
