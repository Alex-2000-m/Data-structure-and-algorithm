// ConsoleApplication3.cpp : �������̨Ӧ�ó������ڵ㡣
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

//˳���
typedef struct {
	ElemType  stu[MAXNUM];
	int length;
}SqList;


//����ڵ�
typedef struct Lnode {
	ElemType stu;
	Lnode* next;
}Lnode;

//˫������ڵ�
typedef struct DoubleLinkLnode {
	ElemType stu;
	DoubleLinkLnode* pre;
	DoubleLinkLnode* next;
}DoubleLinkLnode;

//����ͷָ��
typedef struct {
	Lnode* firststu;
	int length;
}LinkList;

//˫������ͷָ��
typedef struct {
	DoubleLinkLnode* firststu;
	int length;
}DoubleLinkList;

//˳��ջ����̬��
typedef struct {
	ElemType stackArray[MAXNUM];
	int top;
}SqStack;

//��ջ�ڵ�
typedef struct StackNode {
	ElemType stu;
	StackNode* next;
}StackNode;

//��̬˳�����
typedef struct SqQueue {
	ElemType queueArray[MAXNUM];
	int front;
	int rear;
};

//���ӵĽڵ�
typedef struct Qnode {
	ElemType stu;
	Qnode* next;
};

//���ӵ�ָ��ڵ�
typedef struct Qpoint {
	Qnode* front, * rear;
};

//˳����ʼ��
int  InitSqList(SqList* list)
{
	int i;
	list->length = 0;
	for (i = 0; i < MAXNUM; i++)
		list->stu[i].name = "";
	return OK;
}


//�����ʼ��
int  InitLinkList(LinkList* list)
{
	list->length = 0;
	list->firststu = NULL;
	return OK;
}

//˫�������ʼ��
int  InitDoubleLinkList(DoubleLinkList* list)
{
	list->length = 0;
	list->firststu = NULL;
	return OK;
}


//˳��ջ��ʼ��
int InitSeqStack(SqStack* stack) {
	stack->top = 0;
	return OK;
}

//��ջ��ʼ��
int InitLinkStack(StackNode* node) {
	node->next = NULL;
	node->stu.name = "";
	return OK;
}

//ѭ�����г�ʼ��
int InitCirQueue(SqQueue* q) {
	q->front = q->rear = 0;
	return OK;
}

//���ӵĳ�ʼ��
int InitLinkQueue(Qpoint* q, Qnode* queue) {
	q->front = q->rear = queue;
	return OK;
}

//˳���˳�����
int SeqInsertSqList(SqList* list, ElemType ele) {
	if (list->length == MAXNUM) {
		printf("˳��������������ٲ��룡\n");
		return ERROR;
	}
	int i = list->length - 1;
	//˳���Ϊ��ֱ�Ӳ���
	if (list->length == 0)
	{
		list->stu[0] = ele;
		list->length++;
		printf("%s ������ɣ�\n", ele.name.c_str());
		return OK;
	}
	//��β����ʼ����
	//ƥ�䵽��β��Ԫ��
	if ((i == (list->length - 1)) && (ele.name > (list->stu[i].name))) {
		list->stu[i + 1] = ele;
		list->length++;
		printf("%s ������ɣ�\n", ele.name.c_str());
		return OK;
	}
	//����β��Ԫ��
	else {
		//����
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
		printf("%s ������ɣ�\n", ele.name.c_str());
		return OK;
	}
}

//������ĸ˳�����
int SeqInsertLinkList(LinkList* list, ElemType ele)
{
	Lnode* newLnode, * preLnode;
	newLnode = new Lnode;
	newLnode->stu.name = ele.name;
	newLnode->next = NULL;
	if (list->firststu == NULL) {
		list->firststu = newLnode;
		list->length++;
		printf("%s ������ɣ�\n", ele.name.c_str());
		return OK;
	}
	//�ӵ�0��Lnode���в�ѯ���Ƚ�ÿһ��Lnode��stu��name�ʹ������name���ҵ�һ��λ�ã���ɲ���
	//����ǵ�һ��Ԫ��
	if ((list->firststu->stu.name) > (newLnode->stu.name)) {
		newLnode->next = list->firststu;
		list->firststu = newLnode;
		list->length++;
		printf("%s ������ɣ�\n", ele.name.c_str());
		return OK;
	}
	//������ǵ�һ��Ԫ��
	else {
		preLnode = list->firststu;
		//����
		while ((preLnode->stu.name) < (newLnode->stu.name))
		{
			//���ƶ�����뵽ĩβ
			if ((preLnode->next == NULL) || ((preLnode->next->stu.name) > (newLnode->stu.name))) {
				break;
			}
			preLnode = preLnode->next;
		}
		//ִ�в���
		newLnode->next = preLnode->next;
		preLnode->next = newLnode;
		list->length++;
		printf("%s ������ɣ�\n", ele.name.c_str());
		return OK;
	}
}

//˫������˳�����
int SeqInsertDoubleLinkList(DoubleLinkList* list, ElemType ele) {
	DoubleLinkLnode* newLnode, * preLnode;
	newLnode = new DoubleLinkLnode;
	newLnode->stu.name = ele.name;
	newLnode->next = NULL;
	newLnode->pre == NULL;
	if (list->firststu == NULL) {
		list->firststu = newLnode;
		list->length++;
		printf("%s ������ɣ�\n", ele.name.c_str());
		return OK;
	}
	//�ӵ�0��Lnode���в�ѯ���Ƚ�ÿһ��Lnode��stu��name�ʹ������name���ҵ�һ��λ�ã���ɲ���
	//����ǵ�һ��Ԫ��
	if ((list->firststu->stu.name) > (newLnode->stu.name)) {
		newLnode->next = list->firststu;
		list->firststu->pre = newLnode;
		list->firststu = newLnode;
		list->length++;
		printf("%s ������ɣ�\n", ele.name.c_str());
		return OK;
	}
	//������ǵ�һ��Ԫ��
	else {
		preLnode = list->firststu;
		//����
		while ((preLnode->stu.name) < (newLnode->stu.name))
		{
			//���ƶ�����뵽ĩβ
			if ((preLnode->next == NULL) || ((preLnode->next->stu.name) > (newLnode->stu.name))) {
				break;
			}
			preLnode = preLnode->next;
		}
		//ִ�в���
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
		printf("%s ������ɣ�\n", ele.name.c_str());
		return OK;
	}
}


//ѭ������˳�����
int SeqInsertCircularLinkList(LinkList* list, ElemType ele) {
	Lnode* newLnode, * preLnode;
	newLnode = new Lnode;
	newLnode->stu.name = ele.name;
	newLnode->next = NULL;
	int count = 1;
	//�������Ϊ��
	if (list->firststu == NULL) {
		list->firststu = newLnode;
		newLnode->next = list->firststu;
		list->length++;
		printf("%s ������ɣ�\n", ele.name.c_str());
		return OK;
	}
	//�ӵ�0��Lnode���в�ѯ���Ƚ�ÿһ��Lnode��stu��name�ʹ������name���ҵ�һ��λ�ã���ɲ���
	//����ǵ�һ��Ԫ��
	if ((list->firststu->stu.name) > (newLnode->stu.name)) {
		newLnode->next = list->firststu;
		list->firststu = newLnode;
		list->length++;
		printf("%s ������ɣ�\n", ele.name.c_str());
		return OK;
	}
	//������ǵ�һ��Ԫ��
	else {
		preLnode = list->firststu;
		//����
		while ((preLnode->stu.name) < (newLnode->stu.name))
		{
			//���ƶ�����뵽ĩβ
			if ((count == list->length) || ((preLnode->next->stu.name) > (newLnode->stu.name))) {
				break;
			}
			preLnode = preLnode->next;
			count++;
		}
		//ִ�в���
		if (count == list->length) {
			preLnode->next = newLnode;
			newLnode->next = list->firststu;
		}
		else {
			newLnode->next = preLnode->next;
			preLnode->next = newLnode;
		}
		list->length++;
		printf("%s ������ɣ�\n", ele.name.c_str());
		return OK;
	}
}

//˳��ջ��ջ
int pushSqStack(SqStack* s, ElemType ele) {
	if (s->top == MAXNUM - 1) {
		printf("ջ������\n");
		return ERROR;
	}
	s->stackArray[s->top] = ele;
	s->top++;
	printf("%s ������ɣ�\n", ele.name.c_str());
	return OK;
}

//˳��ջ��ջ
ElemType* popSqStack(SqStack* s) {
	if (s->top == 0) {
		printf("ջ�Ѿ����ˣ�\n");
		return NULL;
	}
	ElemType* temp = new ElemType;
	temp->name = s->stackArray[s->top - 1].name;
	s->stackArray[s->top - 1].name = "";
	s->top--;
	printf("%s��ջ�ɹ���\n", temp->name.c_str());
	return temp;
}


//��ջ��ջ
int pushLinkStack(StackNode* top, ElemType ele) {
	if (top == NULL) {
		printf("��ջ�����ڣ�\n");
	}
	StackNode* tempStack = new StackNode;
	tempStack->stu = ele;
	tempStack->next = top->next;
	top->next = tempStack;
	printf("%s ������ɣ�\n", ele.name.c_str());
	return OK;
}

//��ջ��ջ
ElemType* popLinkStack(StackNode* top) {
	if (top == NULL) {
		printf("��ջ�����ڣ�\n");
		return NULL;
	}
	if (top->next == NULL) {
		printf("��ջΪ�գ�\n");
		return NULL;
	}
	ElemType* temp = new ElemType;
	StackNode* pc = top->next;
	temp->name = pc->stu.name;
	top->next = pc->next;
	free(pc);
	printf("%s��ջ�ɹ���\n", temp->name.c_str());
	return temp;
}

//ѭ���������
int InsertCirQueue(SqQueue* q, ElemType ele) {
	if (q == NULL) {
		printf("���л�û������\n");
		return ERROR;
	}
	//����
	if ((q->rear + 1) % MAXNUM == q->front) {
		printf("����������\n");
		return ERROR;
	}
	q->queueArray[q->rear] = ele;
	q->rear = (q->rear + 1) % MAXNUM;
	printf("%s��ӳɹ���\n", ele.name.c_str());
	return OK;
}

//ѭ�����г���
ElemType* deleteCirQueue(SqQueue* q) {
	if (q == NULL) {
		printf("ѭ�����в����ڣ�\n");
		return NULL;
	}
	if (q->front == q->rear) {
		printf("ѭ������Ϊ�գ�\n");
		return NULL;
	}
	ElemType* temp = new ElemType;
	temp->name = q->queueArray[q->front].name;
	q->front = (q->front + 1) % MAXNUM;
	printf("%s���ӳɹ���\n", temp->name.c_str());
	return temp;
}

//���������
int InsertLinkQueue(Qpoint* q, ElemType ele) {
	Qnode* temp = new Qnode;
	temp->stu = ele;
	temp->next = NULL;
	q->rear->next = temp;
	q->rear = temp;
	printf("%s��ӳɹ���\n", ele.name.c_str());
	return OK;
}

//�����г���
ElemType* deleteLinkQueue(Qpoint* q) {
	if (q == NULL) {
		printf("���Ӳ����ڣ�\n");
		return NULL;
	}
	ElemType* tem = new ElemType;
	//�ӿ�
	if (q->front == q->rear) {
		printf("����Ϊ�գ�\n");
		return NULL;
	}
	Qnode* temp = q->front->next;
	tem->name = temp->stu.name;
	q->front->next = temp->next;
	//��ֹ��ʧ��βָ��
	if (temp == q->rear)
		q->rear = q->front;
	free(temp);
	printf("%s���ӳɹ���\n", tem->name.c_str());
	return tem;
}

//˳���ɾ��
int deleteSqList(SqList* list, ElemType ele) {
	int i;
	int flag = 0;
	//˳���Ϊ��ֱ�ӷ���
	if (list == NULL || list->length == 0)
	{
		printf("˳���Ϊ��\n");
		return ERROR;
	}
	//����ɾ����Ԫ����ĩβԪ��
	if (list->stu[list->length - 1].name == ele.name) {
		list->stu[list->length - 1].name = "";
		printf("%s ɾ����ɣ�\n", ele.name.c_str());
	}
	//ɾ���Ĳ���ĩβ
	else {
		//���ҵ�Ԫ��
		for (i = 0; i < list->length; i++) {
			if (list->stu[i].name == ele.name) {
				//����˳���û����������ɾ��
				if (list->length < MAXNUM) {
					for (int j = i; j < (list->length + 1); j++) {
						list->stu[j] = list->stu[j + 1];
					}
				}
				//����˳������ˣ�����ɾ��
				else if (list->length == MAXNUM) {
					for (int j = i; j < (list->length); j++) {
						list->stu[i] = list->stu[i + 1];
					}
					list->stu[list->length - 1].name = "";
				}
				flag = 1;
				list->length--;
				printf("%s ɾ����ɣ�\n", ele.name.c_str());
				break;
			}
		}
		//��������Ҳû�ҵ�Ҫɾ����Ԫ��
		if ((i == list->length) && (flag == 0)) {
			printf("˳�����û��Ҫɾ���ĵ�Ԫ�أ�\n");
		}
	}
}

//����ɾ��
int deleteLinkedList(LinkList* list, ElemType ele) {
	Lnode* tempLnode, * preLnode, * temp;
	tempLnode = new Lnode;

	tempLnode->stu.name = ele.name;
	tempLnode->next = NULL;
	//�ӵ�0��Lnode���в�ѯ���Ƚ�ÿһ��Lnode��stu��name�ʹ������name���ҵ�һ��λ�ã����ɾ��
	if (list == NULL || list->length == 0) {
		printf("����Ϊ�գ�ɾ��ʧ�ܣ�\n");
		return ERROR;
	}//�����׽ڵ��ƥ�䵽
	else if ((list->firststu->stu.name) == (ele.name)) {
		//ֻ���׽ڵ�����
		if (list->firststu->next == NULL) {
			temp = list->firststu;
			list->firststu = NULL;
			free(temp);
			list->length--;
			printf("%s ɾ����ɣ�\n", ele.name.c_str());
			return OK;
		}
		//��ֹ�׽ڵ�����
		else {
			temp = list->firststu;
			list->firststu = list->firststu->next;
			free(temp);
			list->length--;
			printf("%s ɾ����ɣ�\n", ele.name.c_str());
			return OK;
		}
	}
	//�����׽ڵ�ƥ��
	else {
		preLnode = list->firststu;
		//Ѱ��ƥ��ڵ㣬�ҵ���ͣ����
		while ((preLnode->next->stu.name) != (tempLnode->stu.name))
		{
			int count = 1;
			preLnode = preLnode->next;
			count++;
			//����������˻�û���ҵ�
			if (count == list->length) {
				printf("û��Ҫɾ����Ԫ��\n");
				return OK;
			}
		}
		//Ҫɾ���Ĳ���β�ڵ�
		if ((preLnode->next != NULL) && (preLnode->next->next != NULL)) {
			temp = preLnode->next;
			preLnode->next = preLnode->next->next;
			free(temp);
			list->length--;
			printf("%s ɾ����ɣ�\n", ele.name.c_str());
			return OK;
		}
		//Ҫɾ������β�ڵ�
		else if (preLnode->next->next == NULL) {
			temp = preLnode->next;
			preLnode->next = NULL;
			list->length--;
			free(temp);
			printf("%s ɾ����ɣ�\n", ele.name.c_str());
			return OK;
		}
	}
}

//˳����ѯ
int myCheckSqList(SqList* list, ElemType ele) {
	if (list->length == 0 || list == NULL) {
		printf("˳���Ϊ�գ�\n");
		return -1;
	}
	int i, res = 0;
	for (i = 0; i < list->length; i++) {
		if (list->stu[i].name == ele.name) {
			printf("��ѯ������Ϊ%sѧ����˳�����λ��Ϊ��%dλ\n", list->stu[i].name.c_str(), i + 1);
			res = 1;
		}
		if (i == list->length - 1 && res == 0) {
			printf("û������Ϊ%s��ѧ����\n", ele.name.c_str());
			return -1;
		}
	}
	return i;
}

//�����ѯ
Lnode* myCheckLinkedList(LinkList* list, ElemType ele) {
	if (list == NULL || list->length == 0) {
		printf("����Ϊ�գ�\n");
		return NULL;
	}
	int pos = 1, res = 0;
	if (list->firststu->stu.name == ele.name) {
		printf("��ѯ������Ϊ%s��ѧ�����������д��ڵ�%dλ\n", ele.name.c_str(), pos);
		res = 1;
	}
	pos++;
	Lnode* temp = list->firststu->next;
	while (pos <= list->length) {
		if (temp->stu.name == ele.name) {
			printf("��ѯ������Ϊ%s��ѧ�����������д��ڵ�%dλ\n", ele.name.c_str(), pos);
			res = 1;
		}
		if ((temp->next == NULL) && (res == 0)) {
			printf("û������Ϊ%s��ѧ����\n", ele.name.c_str());
			return NULL;
		}
		temp = temp->next;
		pos++;
	}
	return temp;
}

//˳����ӡ
int printsqlist(SqList* list) {
	if (list == NULL) {
		printf("˳���Ϊ�գ�\n");
		return ERROR;
	}
	printf("....................˳���....................\n");
	for (int i = 0; i < list->length; i++) {
		printf("%s\n", list->stu[i].name.c_str());
	}
	printf("....................˳���....................\n");
	return OK;
}

//�����ӡ
int printLinkedList(LinkList* list) {
	if (list == NULL || list->firststu == NULL) {
		printf("����Ϊ�գ�\n");
		return ERROR;
	}
	printf("....................����....................\n");
	printf("%s\n", list->firststu->stu.name.c_str());
	Lnode* temp = list->firststu->next;
	for (int i = 1; i < list->length; i++) {
		printf("%s\n", temp->stu.name.c_str());
		temp = temp->next;
	}
	printf("....................����....................\n");
	return OK;
}

//˫�������ӡ
int printDoubleLinkList(DoubleLinkList* list) {
	if (list == NULL || list->firststu == NULL) {
		printf("����Ϊ�գ�\n");
		return ERROR;
	}
	printf("....................˫������....................\n");
	printf("%s\n", list->firststu->stu.name.c_str());
	DoubleLinkLnode* temp = list->firststu->next;
	for (int i = 1; i < list->length; i++) {
		printf("%s\n", temp->stu.name.c_str());
		temp = temp->next;
	}
	printf("....................˫������....................\n");
	return OK;
}

//ѭ�������ӡ
int printCircularLinkedList(LinkList* list) {
	if (list == NULL || list->firststu == NULL) {
		printf("����Ϊ�գ�\n");
		return ERROR;
	}
	printf("....................ѭ������....................\n");
	printf("%s\n", list->firststu->stu.name.c_str());
	Lnode* temp = list->firststu->next;
	for (int i = 1; i < list->length; i++) {
		printf("%s\n", temp->stu.name.c_str());
		temp = temp->next;
	}
	printf("....................ѭ������....................\n");
	return OK;
}

//ͨ���ļ�����˳���
void readfile(SqList* list) {
	ElemType tempnode;
	//�ļ�ָ��
	FILE* fp;
	errno_t err = fopen_s(&fp, "name.txt", "r");
	int flag = 1;
	flag = fscanf_s(fp, "%s", temp, _countof(temp));
	while ((flag != 0) && (flag != EOF)) {
		tempnode.name = temp;
		//����˳�����
		SeqInsertSqList(list, tempnode);
		flag = fscanf_s(fp, "%s", temp, _countof(temp));
	}
	fclose(fp);
}

//ͨ���ļ���������
void readfile2(LinkList* list) {
	ElemType tempnode;
	//�ļ�ָ��
	FILE* fp;
	errno_t err = fopen_s(&fp, "name.txt", "r");
	int flag = 1;
	flag = fscanf_s(fp, "%s", temp, _countof(temp));
	while ((flag != 0) && (flag != EOF)) {
		tempnode.name = temp;
		//����˳�����
		SeqInsertLinkList(list, tempnode);
		flag = fscanf_s(fp, "%s", temp, _countof(temp));
	}
	fclose(fp);

}

////ͨ���ļ���������2
//void readfile3(LinkList* list) {
//	ElemType tempnode;
//	//�ļ�ָ��
//	FILE* fp;
//	errno_t err = fopen_s(&fp, "name.txt", "r");
//	int flag = 1;
//	flag = fscanf_s(fp, "%s", temp, _countof(temp));
//	while ((flag != 0) && (flag != EOF)) {
//		tempnode.name = temp;
//		//����˳�����
//		SeqInsertLinkList(list, tempnode);
//		flag = fscanf_s(fp, "%s", temp, _countof(temp));
//	}
//	fclose(fp);
//
//}


////ͨ���ļ���������3
//void readfile4(LinkList* list) {
//	ElemType tempnode;
//	//�ļ�ָ��
//	FILE* fp;
//	errno_t err = fopen_s(&fp, "name2.txt", "r");
//	int flag = 1;
//	flag = fscanf_s(fp, "%s", temp, _countof(temp));
//	while ((flag != 0) && (flag != EOF)) {
//		tempnode.name = temp;
//		//����˳�����
//		SeqInsertLinkList(list, tempnode);
//		flag = fscanf_s(fp, "%s", temp, _countof(temp));
//	}
//	fclose(fp);
//
//}

//ͨ���ļ�����˫������
void readfileDouble(DoubleLinkList* list) {
	ElemType tempnode;
	//�ļ�ָ��
	FILE* fp;
	errno_t err = fopen_s(&fp, "name.txt", "r");
	int flag = 1;
	flag = fscanf_s(fp, "%s", temp, _countof(temp));
	while ((flag != 0) && (flag != EOF)) {
		tempnode.name = temp;
		//����˳�����
		SeqInsertDoubleLinkList(list, tempnode);
		flag = fscanf_s(fp, "%s", temp, _countof(temp));
	}
	fclose(fp);

}

//ͨ���ļ�����ѭ������
void readfileCircular(LinkList* list) {
	ElemType tempnode;
	//�ļ�ָ��
	FILE* fp;
	errno_t err = fopen_s(&fp, "name.txt", "r");
	int flag = 1;
	flag = fscanf_s(fp, "%s", temp, _countof(temp));
	while ((flag != 0) && (flag != EOF)) {
		tempnode.name = temp;
		//����˳�����
		SeqInsertCircularLinkList(list, tempnode);
		flag = fscanf_s(fp, "%s", temp, _countof(temp));
	}
	fclose(fp);

}

//ͨ���ļ�����˳��ջ
void readfileSqStack(SqStack* stack) {
	ElemType tempnode;
	//�ļ�ָ��
	FILE* fp;
	errno_t err = fopen_s(&fp, "name.txt", "r");
	int flag = 1;
	flag = fscanf_s(fp, "%s", temp, _countof(temp));
	while ((flag != 0) && (flag != EOF)) {
		tempnode.name = temp;
		//���ò���
		pushSqStack(stack, tempnode);
		flag = fscanf_s(fp, "%s", temp, _countof(temp));
	}
	fclose(fp);
}
//ͨ���ļ�������ջ
void readfileLinkStack(StackNode* stack) {
	ElemType tempnode;
	//�ļ�ָ��
	FILE* fp;
	errno_t err = fopen_s(&fp, "name.txt", "r");
	int flag = 1;
	flag = fscanf_s(fp, "%s", temp, _countof(temp));
	while ((flag != 0) && (flag != EOF)) {
		tempnode.name = temp;
		//���ò���
		pushLinkStack(stack, tempnode);
		flag = fscanf_s(fp, "%s", temp, _countof(temp));
	}
	fclose(fp);
}
//ͨ���ļ�����ѭ������
void readfileCirQueue(SqQueue* sq) {
	ElemType tempnode;
	//�ļ�ָ��
	FILE* fp;
	errno_t err = fopen_s(&fp, "name.txt", "r");
	int flag = 1;
	flag = fscanf_s(fp, "%s", temp, _countof(temp));
	while ((flag != 0) && (flag != EOF)) {
		tempnode.name = temp;
		//���ò���
		InsertCirQueue(sq, tempnode);
		flag = fscanf_s(fp, "%s", temp, _countof(temp));
	}
	fclose(fp);
}
//ͨ���ļ���������
void readfileLinkQueue(Qpoint* lq) {
	ElemType tempnode;
	//�ļ�ָ��
	FILE* fp;
	errno_t err = fopen_s(&fp, "name.txt", "r");
	int flag = 1;
	flag = fscanf_s(fp, "%s", temp, _countof(temp));
	while ((flag != 0) && (flag != EOF)) {
		tempnode.name = temp;
		//���ò���
		InsertLinkQueue(lq, tempnode);
		flag = fscanf_s(fp, "%s", temp, _countof(temp));
	}
	fclose(fp);
}

//����ԭ����������ϲ�����
void mergeLinkedList(LinkList* list1, LinkList* list2, LinkList*& rest) {
	if ((list1 == NULL || list1->firststu == NULL) && (list2 == NULL || list2->firststu == NULL)) {
		printf("Ҫ�ϲ������������ǿյģ�\n");
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

//˳������ȥ������
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


//������������
void mergeLinkedList2(LinkList* list1, LinkList* list2, LinkList* res) {
	if ((list1 == NULL || list1->firststu == NULL) && (list2 == NULL || list2->firststu == NULL)) {
		printf("Ҫ�ϲ������������ǿյģ�\n");
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
	DoubleLinkList Dstu;//˫����
	LinkList Cstu;//ѭ������
	LinkList noRepeat;//���ڱ���ȥ�ؽ��
	SqStack SSstu;//˳��ջ
	StackNode LSstu;//��ջ
	SqQueue SQstu;//ѭ������
	Qpoint* QP = new Qpoint;//����ָ��
	Qnode* QN = new Qnode;//���ӽڵ�
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
		printf("---------------�ϲ�����---------------\n");
		printf(" press a to input from txt and print merge1\n");
		printf(" press b to input from keyboard and print merge2\n");
		printf(" press c to merge two linklist(using extra space)\n");//����һ������
		printf(" press d to merge two linklist(no using extra space)\n");//ֱ�Ӳ���ԭ������������
		printf("---------------˫����---------------\n");
		printf(" ��e���ļ�����˫����\n");
		printf("---------------ѭ������---------------\n");
		printf(" ��f���ļ�����ѭ������\n");
		printf("---------------ȥ��---------------\n");
		printf(" ��g���ļ���������ȥ�أ�\n");
		printf("---------------˳��ջ---------------\n");
		printf(" ��h��ջ��\n");
		printf(" ��i��ջ��\n");
		printf("---------------��ջ---------------\n");
		printf(" ��j��ջ��\n");
		printf(" ��k��ջ��\n");
		printf("---------------ѭ������---------------\n");
		printf(" ��l��ӣ�\n");
		printf(" ��m���ӣ�\n");
		printf("---------------������---------------\n");
		printf(" ��n��ӣ�\n");
		printf(" ��o���ӣ�\n");
		printf(" press q to quit\n");
		}

		temp = getchar();//�Ӽ���������һ�����ֺ�س���getchar�᷵�����Σ�һ�������֣�һ����'\n',����Ҫ������Ĵ���
		
		switch (temp)
		{
		//�ļ�����˳���
		case '1':
			// add your code 
			readfile(&class1stu);
			printf("�ļ���ȡ��ɣ�\n");
			break;
		//�ļ���������
		case '2':
			readfile2(&class2stu);
			printf("�ļ���ȡ��ɣ�\n");
			break;
		//��������˳���
		case '3':
			printf("����Ҫ��������֣�\n");
			do{
				scanf_s("%s", inputname, 20); //������һ��������name��ÿ��name֮���пո�
				//add your code to insert inputname at the end of SqList and LinkList
				tempname.name = inputname;
				SeqInsertSqList(&class1stu, tempname);
			} while (getchar() != '\n');
			
			break;
		//������������
		case '4':
			printf("����Ҫ��������֣�\n");
			do {
				scanf_s("%s", inputname, 20); //������һ��������name��ÿ��name֮���пո�
				//add your code to insert inputname at the end of SqList and LinkList
				tempname.name = inputname;
				SeqInsertLinkList(&class2stu, tempname);
			} while (getchar() != '\n');

			break;
		//��˳����в�������
		case '5':
			printf("����Ҫ���ҵ����֣�\n");
			// add your code 
			do {
				scanf_s("%s", inputname, 20); //������һ��������name��ÿ��name֮���пո�
				//add your code to insert inputname at the end of SqList and LinkList
				tempname.name = inputname;
				myCheckSqList(&class1stu, tempname);
			} while (getchar() != '\n');
			break;
		//�������в�������
		case '6':
			printf("����Ҫ���ҵ����֣�\n");
			// add your code
			do {
				scanf_s("%s", inputname, 20); //������һ��������name��ÿ��name֮���пո�
				//add your code to insert inputname at the end of SqList and LinkList
				tempname.name = inputname;
				myCheckLinkedList(&class2stu, tempname);
			} while (getchar() != '\n');
			break;
		//��˳�����ɾ������
		case '7':
			printf("����Ҫɾ�������֣�\n");
			// add your code 
			do {
				scanf_s("%s", inputname, 20); //������һ��������name��ÿ��name֮���пո�
				//add your code to insert inputname at the end of SqList and LinkList
				tempname.name = inputname;
				deleteSqList(&class1stu, tempname);
			} while (getchar() != '\n');
			break;
		//��������ɾ������
		case '8':
			printf("����Ҫɾ�������֣�\n");
			do {
				scanf_s("%s", inputname, 20); //������һ��������name��ÿ��name֮���пո�
				//add your code to insert inputname at the end of SqList and LinkList
				tempname.name = inputname;
				deleteLinkedList(&class2stu, tempname);
			} while (getchar() != '\n');
			break;
		//��ӡ˳����е�����
		case '9':
			printsqlist(&class1stu);
			break;
		//��ӡ�����е�����
		case '0':
			printLinkedList(&class2stu);
			break;
		case 'a':
			readfile2(&merge1);
			printf("---------merge1----------\n");
			printLinkedList(&merge1);
			break;
		case 'b':
			printf("����Ҫ��������֣�\n");
			do {
				scanf_s("%s", inputname, 20); //������һ��������name��ÿ��name֮���пո�
				tempname.name = inputname;
				SeqInsertLinkList(&merge2, tempname);
			} while (getchar() != '\n');
			printf("---------merge2----------\n");
			printLinkedList(&merge2);
			break;
		case 'c':
			mergeLinkedList2(&merge1, &merge2, &res2);
			printf("�ϲ���ɣ�\n");
			printf("����ԭʼ����Ľ��!ԭʼ����û�б��ݻ٣�\n");
			printLinkedList(&res2);
			break;
		case 'd':
			mergeLinkedList(&merge1, &merge2, res1);
			printf("ֱ�Ӳ���ԭʼ����Ľ��!����������������Ϊ����ԭʼ�����Ѿ����ݻ٣�\n");
			printLinkedList(res1);
			break;
		case 'e':
			printf("---------˫������----------\n");
			readfileDouble(&Dstu);
			printf("---------˫������----------\n");
			break;
		case 'f':
			printf("---------ѭ������----------\n");
			readfileDouble(&Dstu);
			printf("---------ѭ������----------\n");
			break;
		case 'g':
			readfile2(&noRepeat);
			removeRepeat(&noRepeat);
			printf("ȥ�ؽ�����£�\n");
			printLinkedList(&noRepeat);
			break;
		case 'h':
			printf("����Ҫ��������֣�\n");
			// add your code 
			do {
				scanf_s("%s", inputname, 20); //������һ��������name��ÿ��name֮���пո�
				//add your code to insert inputname at the end of SqList and LinkList
				tempname.name = inputname;
				pushSqStack(&SSstu, tempname);
			} while (getchar() != '\n');
			break;
		case 'i':
			printf("��ʼ��ջ��\n");
			popSqStack(&SSstu);
			printf("��ջ��ɣ�\n");
			break;
		case 'j':
			printf("����Ҫ��������֣�\n");
			// add your code 
			do {
				scanf_s("%s", inputname, 20); //������һ��������name��ÿ��name֮���пո�
				//add your code to insert inputname at the end of SqList and LinkList
				tempname.name = inputname;
				pushLinkStack(&LSstu, tempname);
			} while (getchar() != '\n');
			break;
		case 'k':
			printf("��ʼ��ջ��\n");
			popLinkStack(&LSstu);
			printf("��ջ��ɣ�\n");
			break;
		case 'l':
			printf("����Ҫ��������֣�\n");
			// add your code 
			do {
				scanf_s("%s", inputname, 20); //������һ��������name��ÿ��name֮���пո�
				//add your code to insert inputname at the end of SqList and LinkList
				tempname.name = inputname;
				InsertCirQueue(&SQstu, tempname);
			} while (getchar() != '\n');
			break;
		case 'm':
			printf("��ʼ���ӣ�\n");
			deleteCirQueue(&SQstu);
			printf("������ɣ�\n");
			break;
		case 'n':
			printf("����Ҫ��������֣�\n");
			// add your code 
			do {
				scanf_s("%s", inputname, 20); //������һ��������name��ÿ��name֮���пո�
				//add your code to insert inputname at the end of SqList and LinkList
				tempname.name = inputname;
				InsertLinkQueue(QP, tempname);
			} while (getchar() != '\n');
			break;
		case 'o':
			printf("��ʼ���ӣ�\n");
			deleteLinkQueue(QP);
			printf("������ɣ�\n");
			break;
		case 'q':
			return;
		default:
			break;
		}

	}

	return;
}
