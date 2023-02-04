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

struct ENode {
    int ivex, jvex;   /*   边所依附的两个顶点  */
    int weight;       /*   边的权值   */
};    /*  边表元素类型定义   */


struct ELGraph {
    int  vexnum, edgenum;     /*   顶点数和边数    */
    int  vexlist[N];    /*   顶点表    */
    ENode  edgelist[MAX_EDGE];     /*   边表    */
};


//建立边表
ELGraph* EdgG = new ELGraph;
void initEdg(ELGraph*& edg) {
    edg->vexnum = N;
    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N ; j++) {
            if (adjVex[i][j] != MAX) {
                edg->edgelist[count].ivex = i;
                edg->edgelist[count].jvex = j;
                edg->edgelist[count].weight = adjVex[i][j];
                count++;
            }
        }
    }
    edg->edgenum = count;
    for (int i = 0; i < N; i++) {
        edg->vexlist[i] = i;
    }
}


//对边表从小到大排序
void sort(ELGraph* G) {
    int len = G->edgenum;
    for (int i = 0; i < len-1 ; i++) {
        for (int j = 0; j < len- i - 1; j++) {
            if (G->edgelist[j].weight > G->edgelist[j+1].weight) {
                ENode temp = G->edgelist[j];
                G->edgelist[j] = G->edgelist[j+1];
                G->edgelist[j+1] = temp;
            }
        }
    }
}


ENode result[MAX_EDGE];
int Vset[N] = {};

//kruskal
void Kruskal(ELGraph* G) {
    int j = 0, k = 0, v, s1, s2;
    int flag = 0;
    int pos = 0;
    //初始化数组vest
    for (j = 0; j < N; j++) {
        Vset[j] = j;
    }
    j = 0;
    sort(G);
    while (j < G->vexnum-1) {
        s1 = Vset[G->edgelist[j].ivex];
        s2 = Vset[G->edgelist[j].jvex];
        if (Vset[s1] != Vset[s2]) {
            result[pos] = G->edgelist[j];
            Vset[s2] = Vset[s1];
            pos++;
        }
        j++;
    }
    return;
}

//按加入顺序打印边
void displayEdg(ENode* res) {
    int len = EdgG->vexnum-1;
    for (int i = 0; i < len; i++) {
        printf("点%d和点%d的边加入生成树，权值为%d\n", res->ivex, res->jvex, res->weight);
        res++;
    }
}

void main()
{
    initEdg(EdgG);
    Kruskal(EdgG);
    displayEdg(result);
    printf("生成树完成！\n");
    return;
}


