// ConsoleApplication3.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <malloc.h>
#include "stdafx.h"
#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include <conio.h>
#include<cstdlib>

using namespace std;

#define MAXNUM  100
#define OK 0
#define ERROR -1

char temp[20], tmp1;


//typedef char ElemType;

typedef struct {
	string name;
}ElemType;

//顺序表
typedef struct {
	ElemType  stu[MAXNUM];
	int length;
}SqList;


//链表节点
typedef struct Lnode {
	ElemType stu;
	Lnode* next;
}Lnode;

//双向链表节点
typedef struct DoubleLinkLnode {
	ElemType stu;
	DoubleLinkLnode* pre;
	DoubleLinkLnode* next;
}DoubleLinkLnode;

//链表头指针
typedef struct {
	Lnode* firststu;
	int length;
}LinkList;

//双向链表头指针
typedef struct {
	DoubleLinkLnode* firststu;
	int length;
}DoubleLinkList;

//顺序栈（静态）
typedef struct {
	ElemType stackArray[MAXNUM];
	int top;
}SqStack;

//链栈节点
typedef struct StackNode {
	ElemType stu;
	StackNode* next;
}StackNode;

//静态顺序队列
typedef struct SqQueue {
	ElemType queueArray[MAXNUM];
	int front;
	int rear;
};

//链队的节点
typedef struct Qnode {
	ElemType stu;
	Qnode* next;
};

//链队的指针节点
typedef struct Qpoint {
	Qnode* front, * rear;
};

//顺序表初始化
int  InitSqList(SqList* list)
{
	int i;
	list->length = 0;
	for (i = 0; i < MAXNUM; i++)
		list->stu[i].name = "";
	return OK;
}


//链表初始化
int  InitLinkList(LinkList* list)
{
	list->length = 0;
	list->firststu = NULL;
	return OK;
}

//双向链表初始化
int  InitDoubleLinkList(DoubleLinkList* list)
{
	list->length = 0;
	list->firststu = NULL;
	return OK;
}


//顺序栈初始化
int InitSeqStack(SqStack* stack) {
	stack->top = 0;
	return OK;
}

//链栈初始化
int InitLinkStack(StackNode* node) {
	node->next = NULL;
	node->stu.name = "";
	return OK;
}

//循环队列初始化
int InitCirQueue(SqQueue* q) {
	q->front = q->rear = 0;
	return OK;
}

//链队的初始化
int InitLinkQueue(Qpoint* q, Qnode* queue) {
	q->front = q->rear = queue;
	return OK;
}

//顺序表顺序插入
int SeqInsertSqList(SqList* list, ElemType ele) {
	if (list->length == MAXNUM) {
		printf("顺序表已满，不能再插入！\n");
		return ERROR;
	}
	int i = list->length - 1;
	//顺序表为空直接插入
	if (list->length == 0)
	{
		list->stu[0] = ele;
		list->length++;
		printf("%s 插入完成！\n", ele.name.c_str());
		return OK;
	}
	//从尾部开始遍历
	//匹配到了尾部元素
	if ((i == (list->length - 1)) && (ele.name > (list->stu[i].name))) {
		list->stu[i + 1] = ele;
		list->length++;
		printf("%s 插入完成！\n", ele.name.c_str());
		return OK;
	}
	//不是尾部元素
	else {
		//插入
		ElemType temp1, temp2;
		for (int n = 0; n < MAXNUM - 1; n++)
		{
			if (ele.name < (list->stu[n].name)) {
				temp1 = list->stu[n];
				list->stu[n] = ele;
				list->length++;
				for (int j = n + 1; j < list->length; j++) {
					temp2 = list->stu[j];
					list->stu[j] = temp1;
					temp1 = temp2;
				}
				break;
			}
		};
		printf("%s 插入完成！\n", ele.name.c_str());
		return OK;
	}
}

//链表字母顺序插入
int SeqInsertLinkList(LinkList* list, ElemType ele)
{
	Lnode* newLnode, * preLnode;
	newLnode = new Lnode;
	newLnode->stu.name = ele.name;
	newLnode->next = NULL;
	if (list->firststu == NULL) {
		list->firststu = newLnode;
		list->length++;
		printf("%s 插入完成！\n", ele.name.c_str());
		return OK;
	}
	//从第0个Lnode进行查询，比较每一个Lnode的stu的name和待插入的name，找到一个位置，完成插入
	//如果是第一个元素
	if ((list->firststu->stu.name) > (newLnode->stu.name)) {
		newLnode->next = list->firststu;
		list->firststu = newLnode;
		list->length++;
		printf("%s 插入完成！\n", ele.name.c_str());
		return OK;
	}
	//如果不是第一个元素
	else {
		preLnode = list->firststu;
		//遍历
		while ((preLnode->stu.name) < (newLnode->stu.name))
		{
			//限制顶多插入到末尾
			if ((preLnode->next == NULL) || ((preLnode->next->stu.name) > (newLnode->stu.name))) {
				break;
			}
			preLnode = preLnode->next;
		}
		//执行插入
		newLnode->next = preLnode->next;
		preLnode->next = newLnode;
		list->length++;
		printf("%s 插入完成！\n", ele.name.c_str());
		return OK;
	}
}

//双向链表顺序插入
int SeqInsertDoubleLinkList(DoubleLinkList* list, ElemType ele) {
	DoubleLinkLnode* newLnode, * preLnode;
	newLnode = new DoubleLinkLnode;
	newLnode->stu.name = ele.name;
	newLnode->next = NULL;
	newLnode->pre == NULL;
	if (list->firststu == NULL) {
		list->firststu = newLnode;
		list->length++;
		printf("%s 插入完成！\n", ele.name.c_str());
		return OK;
	}
	//从第0个Lnode进行查询，比较每一个Lnode的stu的name和待插入的name，找到一个位置，完成插入
	//如果是第一个元素
	if ((list->firststu->stu.name) > (newLnode->stu.name)) {
		newLnode->next = list->firststu;
		list->firststu->pre = newLnode;
		list->firststu = newLnode;
		list->length++;
		printf("%s 插入完成！\n", ele.name.c_str());
		return OK;
	}
	//如果不是第一个元素
	else {
		preLnode = list->firststu;
		//遍历
		while ((preLnode->stu.name) < (newLnode->stu.name))
		{
			//限制顶多插入到末尾
			if ((preLnode->next == NULL) || ((preLnode->next->stu.name) > (newLnode->stu.name))) {
				break;
			}
			preLnode = preLnode->next;
		}
		//执行插入
		newLnode->next = preLnode->next;
		if (preLnode->next != NULL) {
			preLnode->next->pre = newLnode;
			newLnode->pre = preLnode;
		}
		else {
			newLnode->pre = preLnode;
		}
		preLnode->next = newLnode;
		list->length++;
		printf("%s 插入完成！\n", ele.name.c_str());
		return OK;
	}
}


//循环链表顺序插入
int SeqInsertCircularLinkList(LinkList* list, ElemType ele) {
	Lnode* newLnode, * preLnode;
	newLnode = new Lnode;
	newLnode->stu.name = ele.name;
	newLnode->next = NULL;
	int count = 1;
	//如果链表为空
	if (list->firststu == NULL) {
		list->firststu = newLnode;
		newLnode->next = list->firststu;
		list->length++;
		printf("%s 插入完成！\n", ele.name.c_str());
		return OK;
	}
	//从第0个Lnode进行查询，比较每一个Lnode的stu的name和待插入的name，找到一个位置，完成插入
	//如果是第一个元素
	if ((list->firststu->stu.name) > (newLnode->stu.name)) {
		newLnode->next = list->firststu;
		list->firststu = newLnode;
		list->length++;
		printf("%s 插入完成！\n", ele.name.c_str());
		return OK;
	}
	//如果不是第一个元素
	else {
		preLnode = list->firststu;
		//遍历
		while ((preLnode->stu.name) < (newLnode->stu.name))
		{
			//限制顶多插入到末尾
			if ((count == list->length) || ((preLnode->next->stu.name) > (newLnode->stu.name))) {
				break;
			}
			preLnode = preLnode->next;
			count++;
		}
		//执行插入
		if (count == list->length) {
			preLnode->next = newLnode;
			newLnode->next = list->firststu;
		}
		else {
			newLnode->next = preLnode->next;
			preLnode->next = newLnode;
		}
		list->length++;
		printf("%s 插入完成！\n", ele.name.c_str());
		return OK;
	}
}

//顺序栈入栈
int pushSqStack(SqStack* s, ElemType ele) {
	if (s->top == MAXNUM - 1) {
		printf("栈已满！\n");
		return ERROR;
	}
	s->stackArray[s->top] = ele;
	s->top++;
	printf("%s 插入完成！\n", ele.name.c_str());
	return OK;
}

//顺序栈出栈
ElemType* popSqStack(SqStack* s) {
	if (s->top == 0) {
		printf("栈已经空了！\n");
		return NULL;
	}
	ElemType* temp = new ElemType;
	temp->name = s->stackArray[s->top - 1].name;
	s->stackArray[s->top - 1].name = "";
	s->top--;
	printf("%s出栈成功！\n", temp->name.c_str());
	return temp;
}


//链栈入栈
int pushLinkStack(StackNode* top, ElemType ele) {
	if (top == NULL) {
		printf("链栈不存在！\n");
	}
	StackNode* tempStack = new StackNode;
	tempStack->stu = ele;
	tempStack->next = top->next;
	top->next = tempStack;
	printf("%s 插入完成！\n", ele.name.c_str());
	return OK;
}

//链栈出栈
ElemType* popLinkStack(StackNode* top) {
	if (top == NULL) {
		printf("链栈不存在！\n");
		return NULL;
	}
	if (top->next == NULL) {
		printf("链栈为空！\n");
		return NULL;
	}
	ElemType* temp = new ElemType;
	StackNode* pc = top->next;
	temp->name = pc->stu.name;
	top->next = pc->next;
	free(pc);
	printf("%s出栈成功！\n", temp->name.c_str());
	return temp;
}

//循环队列入队
int InsertCirQueue(SqQueue* q, ElemType ele) {
	if (q == NULL) {
		printf("队列还没创建！\n");
		return ERROR;
	}
	//队满
	if ((q->rear + 1) % MAXNUM == q->front) {
		printf("队列已满！\n");
		return ERROR;
	}
	q->queueArray[q->rear] = ele;
	q->rear = (q->rear + 1) % MAXNUM;
	printf("%s入队成功！\n", ele.name.c_str());
	return OK;
}

//循环队列出队
ElemType* deleteCirQueue(SqQueue* q) {
	if (q == NULL) {
		printf("循环队列不存在！\n");
		return NULL;
	}
	if (q->front == q->rear) {
		printf("循环队列为空！\n");
		return NULL;
	}
	ElemType* temp = new ElemType;
	temp->name = q->queueArray[q->front].name;
	q->front = (q->front + 1) % MAXNUM;
	printf("%s出队成功！\n", temp->name.c_str());
	return temp;
}

//链队列入队
int InsertLinkQueue(Qpoint* q, ElemType ele) {
	Qnode* temp = new Qnode;
	temp->stu = ele;
	temp->next = NULL;
	q->rear->next = temp;
	q->rear = temp;
	printf("%s入队成功！\n", ele.name.c_str());
	return OK;
}

//链队列出队
ElemType* deleteLinkQueue(Qpoint* q) {
	if (q == NULL) {
		printf("链队不存在！\n");
		return NULL;
	}
	ElemType* tem = new ElemType;
	//队空
	if (q->front == q->rear) {
		printf("链队为空！\n");
		return NULL;
	}
	Qnode* temp = q->front->next;
	tem->name = temp->stu.name;
	q->front->next = temp->next;
	//防止丢失队尾指针
	if (temp == q->rear)
		q->rear = q->front;
	free(temp);
	printf("%s出队成功！\n", tem->name.c_str());
	return tem;
}

//顺序表删除
int deleteSqList(SqList* list, ElemType ele) {
	int i;
	int flag = 0;
	//顺序表为空直接返回
	if (list == NULL || list->length == 0)
	{
		printf("顺序表为空\n");
		return ERROR;
	}
	//假如删除的元素是末尾元素
	if (list->stu[list->length - 1].name == ele.name) {
		list->stu[list->length - 1].name = "";
		printf("%s 删除完成！\n", ele.name.c_str());
	}
	//删除的不是末尾
	else {
		//先找到元素
		for (i = 0; i < list->length; i++) {
			if (list->stu[i].name == ele.name) {
				//假如顺序表没有满，正常删除
				if (list->length < MAXNUM) {
					for (int j = i; j < (list->length + 1); j++) {
						list->stu[j] = list->stu[j + 1];
					}
				}
				//假如顺序表满了，特殊删除
				else if (list->length == MAXNUM) {
					for (int j = i; j < (list->length); j++) {
						list->stu[i] = list->stu[i + 1];
					}
					list->stu[list->length - 1].name = "";
				}
				flag = 1;
				list->length--;
				printf("%s 删除完成！\n", ele.name.c_str());
				break;
			}
		}
		//遍历完了也没找到要删除的元素
		if ((i == list->length) && (flag == 0)) {
			printf("顺序表中没有要删除的的元素！\n");
		}
	}
}

//链表删除
int deleteLinkedList(LinkList* list, ElemType ele) {
	Lnode* tempLnode, * preLnode, * temp;
	tempLnode = new Lnode;

	tempLnode->stu.name = ele.name;
	tempLnode->next = NULL;
	//从第0个Lnode进行查询，比较每一个Lnode的stu的name和待插入的name，找到一个位置，完成删除
	if (list == NULL || list->length == 0) {
		printf("链表为空！删除失败！\n");
		return ERROR;
	}//假若首节点就匹配到
	else if ((list->firststu->stu.name) == (ele.name)) {
		//只有首节点的情况
		if (list->firststu->next == NULL) {
			temp = list->firststu;
			list->firststu = NULL;
			free(temp);
			list->length--;
			printf("%s 删除完成！\n", ele.name.c_str());
			return OK;
		}
		//不止首节点的情况
		else {
			temp = list->firststu;
			list->firststu = list->firststu->next;
			free(temp);
			list->length--;
			printf("%s 删除完成！\n", ele.name.c_str());
			return OK;
		}
	}
	//不是首节点匹配
	else {
		preLnode = list->firststu;
		//寻找匹配节点，找到就停下来
		while ((preLnode->next->stu.name) != (tempLnode->stu.name))
		{
			int count = 1;
			preLnode = preLnode->next;
			count++;
			//遍历到最后了还没有找到
			if (count == list->length) {
				printf("没有要删除的元素\n");
				return OK;
			}
		}
		//要删除的不是尾节点
		if ((preLnode->next != NULL) && (preLnode->next->next != NULL)) {
			temp = preLnode->next;
			preLnode->next = preLnode->next->next;
			free(temp);
			list->length--;
			printf("%s 删除完成！\n", ele.name.c_str());
			return OK;
		}
		//要删除的是尾节点
		else if (preLnode->next->next == NULL) {
			temp = preLnode->next;
			preLnode->next = NULL;
			list->length--;
			free(temp);
			printf("%s 删除完成！\n", ele.name.c_str());
			return OK;
		}
	}
}

//顺序表查询
int myCheckSqList(SqList* list, ElemType ele) {
	if (list->length == 0 || list == NULL) {
		printf("顺序表为空！\n");
		return -1;
	}
	int i, res = 0;
	for (i = 0; i < list->length; i++) {
		if (list->stu[i].name == ele.name) {
			printf("查询的姓名为%s学生在顺序表中位置为第%d位\n", list->stu[i].name.c_str(), i + 1);
			res = 1;
		}
		if (i == list->length - 1 && res == 0) {
			printf("没有姓名为%s的学生！\n", ele.name.c_str());
			return -1;
		}
	}
	return i;
}

//链表查询
Lnode* myCheckLinkedList(LinkList* list, ElemType ele) {
	if (list == NULL || list->length == 0) {
		printf("链表为空！\n");
		return NULL;
	}
	int pos = 1, res = 0;
	if (list->firststu->stu.name == ele.name) {
		printf("查询到姓名为%s的学生，在链表中处于第%d位\n", ele.name.c_str(), pos);
		res = 1;
	}
	pos++;
	Lnode* temp = list->firststu->next;
	while (pos <= list->length) {
		if (temp->stu.name == ele.name) {
			printf("查询到姓名为%s的学生，在链表中处于第%d位\n", ele.name.c_str(), pos);
			res = 1;
		}
		if ((temp->next == NULL) && (res == 0)) {
			printf("没有姓名为%s的学生！\n", ele.name.c_str());
			return NULL;
		}
		temp = temp->next;
		pos++;
	}
	return temp;
}

//顺序表打印
int printsqlist(SqList* list) {
	if (list == NULL) {
		printf("顺序表为空！\n");
		return ERROR;
	}
	printf("....................顺序表....................\n");
	for (int i = 0; i < list->length; i++) {
		printf("%s\n", list->stu[i].name.c_str());
	}
	printf("....................顺序表....................\n");
	return OK;
}

//链表打印
int printLinkedList(LinkList* list) {
	if (list == NULL || list->firststu == NULL) {
		printf("链表为空！\n");
		return ERROR;
	}
	printf("....................链表....................\n");
	printf("%s\n", list->firststu->stu.name.c_str());
	Lnode* temp = list->firststu->next;
	for (int i = 1; i < list->length; i++) {
		printf("%s\n", temp->stu.name.c_str());
		temp = temp->next;
	}
	printf("....................链表....................\n");
	return OK;
}

//双向链表打印
int printDoubleLinkList(DoubleLinkList* list) {
	if (list == NULL || list->firststu == NULL) {
		printf("链表为空！\n");
		return ERROR;
	}
	printf("....................双向链表....................\n");
	printf("%s\n", list->firststu->stu.name.c_str());
	DoubleLinkLnode* temp = list->firststu->next;
	for (int i = 1; i < list->length; i++) {
		printf("%s\n", temp->stu.name.c_str());
		temp = temp->next;
	}
	printf("....................双向链表....................\n");
	return OK;
}

//循环链表打印
int printCircularLinkedList(LinkList* list) {
	if (list == NULL || list->firststu == NULL) {
		printf("链表为空！\n");
		return ERROR;
	}
	printf("....................循环链表....................\n");
	printf("%s\n", list->firststu->stu.name.c_str());
	Lnode* temp = list->firststu->next;
	for (int i = 1; i < list->length; i++) {
		printf("%s\n", temp->stu.name.c_str());
		temp = temp->next;
	}
	printf("....................循环链表....................\n");
	return OK;
}

//通过文件输入顺序表
void readfile(SqList* list) {
	ElemType tempnode;
	//文件指针
	FILE* fp;
	errno_t err = fopen_s(&fp, "name.txt", "r");
	int flag = 1;
	flag = fscanf_s(fp, "%s", temp, _countof(temp));
	while ((flag != 0) && (flag != EOF)) {
		tempnode.name = temp;
		//调用顺序插入
		SeqInsertSqList(list, tempnode);
		flag = fscanf_s(fp, "%s", temp, _countof(temp));
	}
	fclose(fp);
}

//通过文件输入链表
void readfile2(LinkList* list) {
	ElemType tempnode;
	//文件指针
	FILE* fp;
	errno_t err = fopen_s(&fp, "name.txt", "r");
	int flag = 1;
	flag = fscanf_s(fp, "%s", temp, _countof(temp));
	while ((flag != 0) && (flag != EOF)) {
		tempnode.name = temp;
		//调用顺序插入
		SeqInsertLinkList(list, tempnode);
		flag = fscanf_s(fp, "%s", temp, _countof(temp));
	}
	fclose(fp);

}

////通过文件输入链表2
//void readfile3(LinkList* list) {
//	ElemType tempnode;
//	//文件指针
//	FILE* fp;
//	errno_t err = fopen_s(&fp, "name.txt", "r");
//	int flag = 1;
//	flag = fscanf_s(fp, "%s", temp, _countof(temp));
//	while ((flag != 0) && (flag != EOF)) {
//		tempnode.name = temp;
//		//调用顺序插入
//		SeqInsertLinkList(list, tempnode);
//		flag = fscanf_s(fp, "%s", temp, _countof(temp));
//	}
//	fclose(fp);
//
//}


////通过文件输入链表3
//void readfile4(LinkList* list) {
//	ElemType tempnode;
//	//文件指针
//	FILE* fp;
//	errno_t err = fopen_s(&fp, "name2.txt", "r");
//	int flag = 1;
//	flag = fscanf_s(fp, "%s", temp, _countof(temp));
//	while ((flag != 0) && (flag != EOF)) {
//		tempnode.name = temp;
//		//调用顺序插入
//		SeqInsertLinkList(list, tempnode);
//		flag = fscanf_s(fp, "%s", temp, _countof(temp));
//	}
//	fclose(fp);
//
//}

//通过文件输入双向链表
void readfileDouble(DoubleLinkList* list) {
	ElemType tempnode;
	//文件指针
	FILE* fp;
	errno_t err = fopen_s(&fp, "name.txt", "r");
	int flag = 1;
	flag = fscanf_s(fp, "%s", temp, _countof(temp));
	while ((flag != 0) && (flag != EOF)) {
		tempnode.name = temp;
		//调用顺序插入
		SeqInsertDoubleLinkList(list, tempnode);
		flag = fscanf_s(fp, "%s", temp, _countof(temp));
	}
	fclose(fp);

}

//通过文件输入循环链表
void readfileCircular(LinkList* list) {
	ElemType tempnode;
	//文件指针
	FILE* fp;
	errno_t err = fopen_s(&fp, "name.txt", "r");
	int flag = 1;
	flag = fscanf_s(fp, "%s", temp, _countof(temp));
	while ((flag != 0) && (flag != EOF)) {
		tempnode.name = temp;
		//调用顺序插入
		SeqInsertCircularLinkList(list, tempnode);
		flag = fscanf_s(fp, "%s", temp, _countof(temp));
	}
	fclose(fp);

}

//通过文件输入顺序栈
void readfileSqStack(SqStack* stack) {
	ElemType tempnode;
	//文件指针
	FILE* fp;
	errno_t err = fopen_s(&fp, "name.txt", "r");
	int flag = 1;
	flag = fscanf_s(fp, "%s", temp, _countof(temp));
	while ((flag != 0) && (flag != EOF)) {
		tempnode.name = temp;
		//调用插入
		pushSqStack(stack, tempnode);
		flag = fscanf_s(fp, "%s", temp, _countof(temp));
	}
	fclose(fp);
}
//通过文件输入链栈
void readfileLinkStack(StackNode* stack) {
	ElemType tempnode;
	//文件指针
	FILE* fp;
	errno_t err = fopen_s(&fp, "name.txt", "r");
	int flag = 1;
	flag = fscanf_s(fp, "%s", temp, _countof(temp));
	while ((flag != 0) && (flag != EOF)) {
		tempnode.name = temp;
		//调用插入
		pushLinkStack(stack, tempnode);
		flag = fscanf_s(fp, "%s", temp, _countof(temp));
	}
	fclose(fp);
}
//通过文件输入循环队列
void readfileCirQueue(SqQueue* sq) {
	ElemType tempnode;
	//文件指针
	FILE* fp;
	errno_t err = fopen_s(&fp, "name.txt", "r");
	int flag = 1;
	flag = fscanf_s(fp, "%s", temp, _countof(temp));
	while ((flag != 0) && (flag != EOF)) {
		tempnode.name = temp;
		//调用插入
		InsertCirQueue(sq, tempnode);
		flag = fscanf_s(fp, "%s", temp, _countof(temp));
	}
	fclose(fp);
}
//通过文件输入链队
void readfileLinkQueue(Qpoint* lq) {
	ElemType tempnode;
	//文件指针
	FILE* fp;
	errno_t err = fopen_s(&fp, "name.txt", "r");
	int flag = 1;
	flag = fscanf_s(fp, "%s", temp, _countof(temp));
	while ((flag != 0) && (flag != EOF)) {
		tempnode.name = temp;
		//调用插入
		InsertLinkQueue(lq, tempnode);
		flag = fscanf_s(fp, "%s", temp, _countof(temp));
	}
	fclose(fp);
}

//基于原来两个链表合并链表
void mergeLinkedList(LinkList* list1, LinkList* list2, LinkList*& rest) {
	if ((list1 == NULL || list1->firststu == NULL) && (list2 == NULL || list2->firststu == NULL)) {
		printf("要合并的俩个链表都是空的！\n");
		rest = NULL;
		return;
	}
	if (list1->firststu == NULL || list1 == NULL) {
		rest = list2;
		rest->length = list1->length + list2->length;
	}
	else {
		rest = list1;
		rest->length = list1->length + list2->length;
	}
	Lnode* p1;
	Lnode* p2;
	Lnode* pc;
	if (list1->firststu->stu.name < list2->firststu->stu.name) {
		pc = list1->firststu;
		p2 = list2->firststu;
		p1 = pc->next;
		rest->firststu = list1->firststu;
	}
	else if (list1->firststu->stu.name > list2->firststu->stu.name) {
		pc = list2->firststu;
		p2 = list1->firststu;
		p1 = pc->next;
		rest->firststu = list2->firststu;
	}
	else {
		pc = list1->firststu;
		p2 = list2->firststu;
		p1 = pc->next;
		p2 = p2->next;
		rest = list1;
		rest->length--;
	}
	while (p1 && p2) {
		if (p1->stu.name < p2->stu.name) {
			pc->next = p1;
			pc = p1;
			p1 = p1->next;
		}
		else if (p1->stu.name > p2->stu.name) {
			pc->next = p2;
			pc = p2;
			p2 = p2->next;
		}
		else {
			pc->next = p1;
			pc = p1;
			p1 = p1->next;
			p2 = p2->next;
			rest->length--;
		}
	}
	if (p1 == NULL) {
		pc->next = p2;

	}
	else {
		pc->next = p1;
	}
}

//顺序链表去除重名
void removeRepeat(LinkList* list) {
	if (!list->firststu) {
		return;
	}
	Lnode* cur = list->firststu;
	while (cur->next) {
		if (cur->stu.name == cur->next->stu.name) {
			cur->next = cur->next->next;
			list->length--;
		}
		else {
			cur = cur->next;
		}
	}
	return;
}


//拷贝两个链表
void mergeLinkedList2(LinkList* list1, LinkList* list2, LinkList* res) {
	if ((list1 == NULL || list1->firststu == NULL) && (list2 == NULL || list2->firststu == NULL)) {
		printf("要合并的俩个链表都是空的！\n");
		return;
	}
	res->length = list1->length + list2->length;
	Lnode* p1 = list1->firststu;
	Lnode* p2 = list2->firststu;
	Lnode* pc;
	Lnode* temp = new Lnode;
	temp->next = NULL;
	if (p1->stu.name < p2->stu.name) {
		temp->stu.name = p1->stu.name;
		res->firststu = temp;
		pc = res->firststu;
		p1 = p1->next;
	}
	else if (p1->stu.name > p2->stu.name) {
		temp->stu.name = p2->stu.name;
		res->firststu = temp;
		pc = res->firststu;
		p2 = p2->next;
	}
	else {
		temp->stu.name = p1->stu.name;
		res->firststu = temp;
		pc = res->firststu;
		p1 = p1->next;
		p2 = p2->next;
		res->length--;
	}
	while (p1 && p2) {
		temp = new Lnode;
		if (p1->stu.name < p2->stu.name) {
			temp->stu.name = p1->stu.name;
			pc->next = temp;
			pc = pc->next;
			p1 = p1->next;
		}
		else if (p1->stu.name > p2->stu.name) {
			temp->stu.name = p2->stu.name;
			pc->next = temp;
			pc = pc->next;
			p2 = p2->next;
		}
		else {
			temp->stu.name = p1->stu.name;
			pc->next = temp;
			pc = pc->next;
			p1 = p1->next;
			p2 = p2->next;
			res->length--;
		}
	}
	temp = new Lnode;
	if (p1 == NULL && p2 == NULL) {
		return;
	}
	if (p1 == NULL) {
		temp->stu.name = p2->stu.name;
		temp->next = p2->next;
		pc->next = temp;
	}
	else if (p2 == NULL) {
		temp->stu.name = p1->stu.name;
		temp->next = p1->next;
		pc->next = temp;
	}
	printf("%d\n", res->length);
}



void main()
{
	char temp;
	char inputname[20];
	temp = '0';
	SqList class1stu;
	LinkList class2stu;
	LinkList merge1;
	LinkList merge2;
	LinkList* res1 = new LinkList;
	LinkList res2;
	ElemType tempname;
	DoubleLinkList Dstu;//双链表
	LinkList Cstu;//循环链表
	LinkList noRepeat;//用于保存去重结果
	SqStack SSstu;//顺序栈
	StackNode LSstu;//链栈
	SqQueue SQstu;//循环队列
	Qpoint* QP = new Qpoint;//链队指针
	Qnode* QN = new Qnode;//链队节点
	InitSqList(&class1stu);
	InitLinkList(&merge1);
	InitLinkList(&merge2);
	InitLinkList(&res2);
	InitLinkList(&class2stu);
	InitDoubleLinkList(&Dstu);
	InitLinkList(&Cstu);
	InitLinkList(&noRepeat);
	InitSeqStack(&SSstu);
	InitLinkStack(&LSstu);
	InitCirQueue(&SQstu);
	InitLinkQueue(QP, QN);
	while (1)
	{
		if (temp == '0' || temp == '1' || temp == '2' || temp == '3' || temp == '4')
		{
		printf("---------Menu is as following--------\n");
		printf(" press 1 return to input name from name.txt into sqlist\n");
		printf(" press 2 return to input name from name.txt into linklist\n");
		printf(" press 3 return to input name from keyboard into sqlist\n");
		printf(" press 4 return to input name from keyboard into linklist\n");
		printf(" press 5 return to lookup name in sqlist\n");
		printf(" press 6 return to lookup name in linklist\n");
		printf(" press 7 return to delete name from sqlist\n");
		printf(" press 8 return to delete name from linklist\n");
		printf(" press 9 return to print all names in sqlist\n");
		printf(" press 0 return to print all names in linklist\n");
		printf("---------------合并功能---------------\n");
		printf(" press a to input from txt and print merge1\n");
		printf(" press b to input from keyboard and print merge2\n");
		printf(" press c to merge two linklist(using extra space)\n");//新增一个链表
		printf(" press d to merge two linklist(no using extra space)\n");//直接操作原来的两个链表
		printf("---------------双链表---------------\n");
		printf(" 按e从文件读入双链表！\n");
		printf("---------------循环链表---------------\n");
		printf(" 按f从文件读入循环链表！\n");
		printf("---------------去重---------------\n");
		printf(" 按g从文件读入链表并去重！\n");
		printf("---------------顺序栈---------------\n");
		printf(" 按h入栈！\n");
		printf(" 按i出栈！\n");
		printf("---------------链栈---------------\n");
		printf(" 按j入栈！\n");
		printf(" 按k出栈！\n");
		printf("---------------循环队列---------------\n");
		printf(" 按l入队！\n");
		printf(" 按m出队！\n");
		printf("---------------链队列---------------\n");
		printf(" 按n入队！\n");
		printf(" 按o出队！\n");
		printf(" press q to quit\n");
		}

		temp = getchar();//从键盘上输入一个数字后回车，getchar会返回两次，一次是数字，一次是'\n',所以要做上面的处理。
		
		switch (temp)
		{
		//文件输入顺序表
		case '1':
			// add your code 
			readfile(&class1stu);
			printf("文件读取完成！\n");
			break;
		//文件输入链表
		case '2':
			readfile2(&class2stu);
			printf("文件读取完成！\n");
			break;
		//键盘输入顺序表
		case '3':
			printf("输入要插入的名字：\n");
			do{
				scanf_s("%s", inputname, 20); //可以在一行输入多个name，每个name之间有空格，
				//add your code to insert inputname at the end of SqList and LinkList
				tempname.name = inputname;
				SeqInsertSqList(&class1stu, tempname);
			} while (getchar() != '\n');
			
			break;
		//键盘输入链表
		case '4':
			printf("输入要插入的名字：\n");
			do {
				scanf_s("%s", inputname, 20); //可以在一行输入多个name，每个name之间有空格，
				//add your code to insert inputname at the end of SqList and LinkList
				tempname.name = inputname;
				SeqInsertLinkList(&class2stu, tempname);
			} while (getchar() != '\n');

			break;
		//在顺序表中查找名字
		case '5':
			printf("输入要查找的名字：\n");
			// add your code 
			do {
				scanf_s("%s", inputname, 20); //可以在一行输入多个name，每个name之间有空格，
				//add your code to insert inputname at the end of SqList and LinkList
				tempname.name = inputname;
				myCheckSqList(&class1stu, tempname);
			} while (getchar() != '\n');
			break;
		//在链表中查找名字
		case '6':
			printf("输入要查找的名字：\n");
			// add your code
			do {
				scanf_s("%s", inputname, 20); //可以在一行输入多个name，每个name之间有空格，
				//add your code to insert inputname at the end of SqList and LinkList
				tempname.name = inputname;
				myCheckLinkedList(&class2stu, tempname);
			} while (getchar() != '\n');
			break;
		//在顺序表中删除名字
		case '7':
			printf("输入要删除的名字：\n");
			// add your code 
			do {
				scanf_s("%s", inputname, 20); //可以在一行输入多个name，每个name之间有空格，
				//add your code to insert inputname at the end of SqList and LinkList
				tempname.name = inputname;
				deleteSqList(&class1stu, tempname);
			} while (getchar() != '\n');
			break;
		//在链表中删除名字
		case '8':
			printf("输入要删除的名字：\n");
			do {
				scanf_s("%s", inputname, 20); //可以在一行输入多个name，每个name之间有空格，
				//add your code to insert inputname at the end of SqList and LinkList
				tempname.name = inputname;
				deleteLinkedList(&class2stu, tempname);
			} while (getchar() != '\n');
			break;
		//打印顺序表中的名字
		case '9':
			printsqlist(&class1stu);
			break;
		//打印链表中的名字
		case '0':
			printLinkedList(&class2stu);
			break;
		case 'a':
			readfile2(&merge1);
			printf("---------merge1----------\n");
			printLinkedList(&merge1);
			break;
		case 'b':
			printf("输入要插入的名字：\n");
			do {
				scanf_s("%s", inputname, 20); //可以在一行输入多个name，每个name之间有空格，
				tempname.name = inputname;
				SeqInsertLinkList(&merge2, tempname);
			} while (getchar() != '\n');
			printf("---------merge2----------\n");
			printLinkedList(&merge2);
			break;
		case 'c':
			mergeLinkedList2(&merge1, &merge2, &res2);
			printf("合并完成！\n");
			printf("复制原始链表的结果!原始链表没有被摧毁！\n");
			printLinkedList(&res2);
			break;
		case 'd':
			mergeLinkedList(&merge1, &merge2, res1);
			printf("直接操作原始链表的结果!请重新启动程序，因为两个原始链表已经被摧毁！\n");
			printLinkedList(res1);
			break;
		case 'e':
			printf("---------双向链表----------\n");
			readfileDouble(&Dstu);
			printf("---------双向链表----------\n");
			break;
		case 'f':
			printf("---------循环链表----------\n");
			readfileDouble(&Dstu);
			printf("---------循环链表----------\n");
			break;
		case 'g':
			readfile2(&noRepeat);
			removeRepeat(&noRepeat);
			printf("去重结果如下：\n");
			printLinkedList(&noRepeat);
			break;
		case 'h':
			printf("输入要插入的名字：\n");
			// add your code 
			do {
				scanf_s("%s", inputname, 20); //可以在一行输入多个name，每个name之间有空格，
				//add your code to insert inputname at the end of SqList and LinkList
				tempname.name = inputname;
				pushSqStack(&SSstu, tempname);
			} while (getchar() != '\n');
			break;
		case 'i':
			printf("开始弹栈：\n");
			popSqStack(&SSstu);
			printf("出栈完成！\n");
			break;
		case 'j':
			printf("输入要插入的名字：\n");
			// add your code 
			do {
				scanf_s("%s", inputname, 20); //可以在一行输入多个name，每个name之间有空格，
				//add your code to insert inputname at the end of SqList and LinkList
				tempname.name = inputname;
				pushLinkStack(&LSstu, tempname);
			} while (getchar() != '\n');
			break;
		case 'k':
			printf("开始弹栈：\n");
			popLinkStack(&LSstu);
			printf("出栈完成！\n");
			break;
		case 'l':
			printf("输入要插入的名字：\n");
			// add your code 
			do {
				scanf_s("%s", inputname, 20); //可以在一行输入多个name，每个name之间有空格，
				//add your code to insert inputname at the end of SqList and LinkList
				tempname.name = inputname;
				InsertCirQueue(&SQstu, tempname);
			} while (getchar() != '\n');
			break;
		case 'm':
			printf("开始出队：\n");
			deleteCirQueue(&SQstu);
			printf("出队完成！\n");
			break;
		case 'n':
			printf("输入要插入的名字：\n");
			// add your code 
			do {
				scanf_s("%s", inputname, 20); //可以在一行输入多个name，每个name之间有空格，
				//add your code to insert inputname at the end of SqList and LinkList
				tempname.name = inputname;
				InsertLinkQueue(QP, tempname);
			} while (getchar() != '\n');
			break;
		case 'o':
			printf("开始出队：\n");
			deleteLinkQueue(QP);
			printf("出队完成！\n");
			break;
		case 'q':
			return;
		default:
			break;
		}

	}

	return;
}
