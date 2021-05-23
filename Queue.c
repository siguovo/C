#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int* data;
	int front;
	int tail;
	int size;
	int flag;
}MyQueue;

MyQueue* Create(int k) {
	if (k < 0) {
		return NULL;
	}
	MyQueue* obj = malloc(sizeof(MyQueue));
	if (obj == NULL) {
		return NULL;
	}
	obj->data = malloc(sizeof(int) * k);
	if (obj->data == NULL) {
		return NULL;
	}
	obj->front = obj->tail = 0;
	obj->size = k;
	obj->flag = 0;

	return obj;
}

bool IsEmpty(MyQueue* obj) {
	if (obj->flag == 0 && obj->front == obj->tail) {
		return true;
	}
	return false;
}

bool IsFull(MyQueue* obj) {
	if (obj->flag == 1) {
		return true;
	}
	return false;
}

bool EnQueue(MyQueue* obj, int value) {
	if (IsFull(obj)) {
		return false;
	}

	obj->data[obj->tail] = value;
	obj->tail = ((obj->tail + 1) < obj->size) ? (obj->tail + 1) : 0;

	if (obj->front == obj->tail) {
		obj->flag = 1;
	}
	return true;
}

bool DeQueue(MyQueue* obj) {
	if (IsEmpty(obj)) {
		return false;
	}

	obj->data[obj->front] = 0;
	obj->front = ((obj->front + 1) < obj->size) ? (obj->front + 1) : 0;

	obj->flag = 0;
	return true;
}

int FrontQueue(MyQueue* obj) {
	if (IsEmpty(obj)) {
		return -1;
	}
	return obj->data[obj->front];
}

int TailQueue(MyQueue* obj) {
	if (IsEmpty(obj)) {
		return false;
	}
	int i = (obj->tail == 0) ? (obj->size - 1) : (obj->tail - 1);
	return obj->data[i];
}

void FreeQueue(MyQueue* obj) {
	free(obj->data);
	obj->data = NULL;
	free(obj);
	obj = NULL;
}

/*
* 一个队列的元素有:
* data(数据域),front,tail(头指针，尾指针),
* size(队列的大小),flag(非必要，可以用来标志队列状态:满/空)
* 1.给定一个k初始化队列
* 2.判断队列是否为空
* 3.判断队列是否已满
* 4.添加一个队列(入队)
* 5.删除一个队列(出队)
* 6.输出队列的头元素
* 7.输出队列的尾元素
* 8.释放队列空间
*/