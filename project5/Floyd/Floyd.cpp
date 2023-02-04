#include <iostream>
#include <stdio.h>

#define MAX_VEX 6
#define MAX 65535 //无穷大

int A[MAX_VEX][MAX_VEX];
int Path[MAX_VEX][MAX_VEX];
//int adjVex[MAX_VEX][MAX_VEX] = {
//    {0,2,8},
//    {MAX,0,4},
//    {5,MAX,0}
//};

//带权有向图的邻接矩阵
int adjVex[MAX_VEX][MAX_VEX] = {
    {MAX,20,60,MAX,10,65},
    {MAX,MAX,30,70,MAX,MAX},
    {MAX,MAX,MAX,40,MAX,MAX},
    {MAX,MAX,MAX,MAX,35,MAX},
    {MAX,MAX,MAX,MAX,MAX,20},
    {MAX,MAX,15,80,MAX,MAX}
};


void prn_pass(int j, int k) {
    if (Path[j][k] != -1) {
        prn_pass(j, Path[j][k]);
        printf(",%d", Path[j][k]);
        prn_pass(Path[j][k], k);
    }
    return;
}

void FloydPath(int adjVex[MAX_VEX][MAX_VEX]) {
    int j, k, m;
    //初始化数组
    for (j = 0; j < MAX_VEX; j++) {
        for (k = 0; k < MAX_VEX; k++) {
            A[j][k] = adjVex[j][k];
            Path[j][k] = -1;
        }
    }
    //修改A和Path
    for (m = 0; m < MAX_VEX; m++) {
        for (j = 0; j < MAX_VEX; j++) {
            for (k = 0; k < MAX_VEX; k++) {
                if ((A[j][m] + A[m][k]) < A[j][k]) {
                    A[j][k] = A[j][m] + A[m][k];
                    Path[j][k] = m;
                }
            }
        }
    }
    //打印路径
    for (j = 0; j < MAX_VEX; j++) {
        for (k = 0; k < MAX_VEX; k++) {
            if (j != k) {
                printf("%d到%d的最短路径为：\n", j, k);
                if (A[j][k] == MAX) {
                    printf("不存在路径！\n");
                }
                else {
                    printf("{");
                    printf("%d", j);
                    //判断是否有捷径，有就打印
                    prn_pass(j, k);
                    printf(",%d", k);
                    printf("}");
                    printf("\n最短路径长度为:%d\n", A[j][k]);
                }
            }
        }
    }
    return;
}


int main()
{
    FloydPath(adjVex);
    return 0;
}

