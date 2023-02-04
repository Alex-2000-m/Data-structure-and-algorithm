#include <iostream>
#include <stdio.h>


#define MAX 65535 //无穷大
#define MAX_EDGE 100
#define N 6

typedef enum {FALSE,TRUE} BOOLEAN;

//带权有向图的邻接矩阵
int adjVex[N][N] = {
	{MAX,20,60,MAX,10,65},
	{MAX,MAX,30,70,MAX,MAX},
	{MAX,MAX,MAX,40,MAX,MAX},
	{MAX,MAX,MAX,MAX,35,MAX},
	{MAX,MAX,MAX,MAX,MAX,20},
	{MAX,MAX,15,80,MAX,MAX}
};

int dist[N], pre[N];
//标识顶点是否加入S
BOOLEAN final[N];

void Dijkstra(int adjVex[][N], int start) {
	//初始化
	for (int i = 0; i < N; i++) {
		pre[i] = start;
		final[i] = FALSE;
		dist[i] = adjVex[start][i];
	}
	//将初始点start加入S
	dist[start] = 0;
	final[start] = TRUE;
	//处理剩下n-1个顶点
	int k;
	for (int j = 0; j < N-1; j++) {
		int min = MAX;
		//寻找最小的边
		for (int v = 0; v < N; v++) {
			if (!final[v] && dist[v] < min) {
				min = dist[v];
				k = v;
			}
		}
		//把最小的边的端点加入S
		final[k] = TRUE;
		//更新dist和pre
		for (int i = 0; i < N; i++) {
			if (!final[i] && dist[k] + adjVex[k][i] < dist[i]) {
				dist[i] = dist[k] + adjVex[k][i];
				pre[i] = k;
			}
		}
	}
	return;
}


struct RouteNode {
	int point;
	RouteNode* next;
};

struct Route {
	int cost = 0;
	RouteNode* first;
};

Route res[N-1];

int pR;
//回溯
void trace(int end) {
	RouteNode* temp = new RouteNode;
	temp->point = end;
	temp->next = NULL;
	if (pre[end] == 0) {
		if (res[pR].first == NULL) {
			res[pR].first = temp;
			res[pR].cost = res[pR].cost + adjVex[pre[end]][end];
			return;
		}
		else {
			temp->next = res[pR].first;
			res[pR].first = temp;
			res[pR].cost = res[pR].cost + adjVex[pre[end]][end];
			return;
		}
	}
	else {
		if (res[pR].first == NULL) {
			res[pR].first = temp;
			res[pR].cost = res[pR].cost + adjVex[pre[end]][end];
		}
		else {
			temp->next = res[pR].first;
			res[pR].first = temp;
			res[pR].cost = res[pR].cost + adjVex[pre[end]][end];
		}
		trace(pre[end]);
	}
}


//保存路径
void saveRoute() {
	int p = 1;
	for (p = 1; p < N; p++) {
		pR = p - 1;
		trace(p);
	}
	return;
}



//打印路径
void displayRoute(Route res[N-1]) {
	for (int i = 0; i < N-1; i++) {
		printf("0");
		RouteNode* temp = res[i].first;
		temp->next == NULL;
		while (temp != NULL) {
			printf("-%d", temp->point);
			temp = temp->next;
		}
		printf(" 路径长度为%d", res[i].cost);
		printf("\n");
	}
	return;
}



int main()
{
	Dijkstra(adjVex, 0);
	saveRoute();
	printf("最短路径为：\n");
	displayRoute(res);
	return 0;
}

