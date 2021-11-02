/*
 * TaskList.c
 *
 *  Created on: Oct 26, 2021
 *      Author: fhdtr
 */
#include "TaskList.h"


struct Node {
	STask* data;
	struct Node* next;
};

static uint32_t taskCount = 0;

static struct Node* head = NULL;
static struct Node* curr = NULL;
static struct Node* preCurr = NULL; // for marking the previous curr pointer

void TL_init(void) {
	head = (struct Node*)malloc(sizeof(struct Node)); // create a virtual node
	head->data = NULL;
	head->next = NULL;

	taskCount = 0;
	curr = NULL;
	preCurr = NULL;
}

void TL_insert(STask* t) {
	struct Node* preTemp = head;
	struct Node* temp = head->next;

	uint32_t accumDelay = 0;
	while(temp && (accumDelay + temp->data->Delay) <= t->Delay) {
		accumDelay += temp->data->Delay;

		preTemp = temp;
		temp = temp->next;
	}

	struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
	preTemp->next = newNode;
	newNode->next = temp;

	newNode->data = t;
	newNode->data->Delay -= accumDelay;
	if(temp) {
		temp->data->Delay -= newNode->data->Delay;
	}

	taskCount++;
}

STask* TL_removeFront(void) {
	if(taskCount == 0) return NULL;

	struct Node* delNode = head->next;
	head->next = delNode->next;

	taskCount--;
	return delNode->data;
}

STask* TL_getFront() {
	if(head)
		return head->next->data;
	return NULL;
}
