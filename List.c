#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct List {
	int val;
	struct List* next;
};

struct List* Create() {
	struct List* head = malloc(sizeof(struct List));
	head->val = 0;
	head->next = NULL;

	return head;
}

struct List* listPush(struct List* head, int value) {
	head->val = value;
	head = head->next;
}

struct List* listPop(struct List* head)