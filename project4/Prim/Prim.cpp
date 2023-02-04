#include <stdio.h>
#include <iostream>

#define MAX 65535 //无穷大
#define MAX_EDGE 100
#define N 5
//邻接矩阵
int adjVex[N][N] = { 
    {MAX,8,MAX,4,MAX},
    {8,MAX,7,5,12},
    {MAX,7,MAX,11,6},
    {4,5,11,MAX,3},
    {MAX,12,6,3,MAX}
};

//保存V-U到U中最小权值的边
struct {
    int adjvex;//边依附的U中的顶点
    int lowcost;//该边的权值
}closedge[MAX_EDGE];

//存储最小生成树
struct MSTEdge {
    int vex1, vex2;
    int weight;
};

int result[N];

//prim
void prim(int adjVex[][N],int u) {
    int j = 0, k = 0, v = 0, min;
    int num = 0;
    //初始化数组closedge
    for (j = 0; j < N; j++) {
        closedge[j].adjvex = u;
        closedge[j].lowcost = adjVex[j][u];
    }
    //初始化U，u放进去
    closedge[u].lowcost = 0;
    result[num] = u;
    num++;
    for (j = 0; j < N - 1; j++) {
        min = MAX;
        //找到最小的边
        for (v = 0; v < N; v++) {
            if (closedge[v].lowcost != 0 && closedge[v].lowcost < min) {
                min = closedge[v].lowcost;
                k = v;
            }
        }
        result[num] = k;
        num++;
        //顶点k并入U
        closedge[k].lowcost = 0;
        //修改closedge中每个元素的值
        for (v = 0; v < N; v++) {
            if (adjVex[v][k] < closedge[v].lowcost) {
                 closedge[v].lowcost = adjVex[v][k];
                 closedge[v].adjvex = k;
            }
        }
    }
    return;
}

//打印最小生成树
void printMinTree(int* res) {
    for (int i = 0; i < N; i++) {
        printf("点%d加入生成树！\n", res[i]);
    }
}

void main()
{
    int start;
    printf("输入起始点：\n");
    scanf_s("%d", &start);
    prim(adjVex, start);
    printMinTree(result);
    return;
}

