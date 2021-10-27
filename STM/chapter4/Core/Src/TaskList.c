/*
 * TaskList.c
 *
 *  Created on: Oct 26, 2021
 *      Author: fhdtr
 */
#include <TaskList.h>

struct Node {
	STask* data;
	struct Node* next;
};

static uint32_t taskCount = 0;

static struct Node* head = NULL;
static struct Node* curr = NULL;
static struct Node* preCurr = NULL; // for marking the previous curr pointer
static struct Node* tail = NULL;

void TL_init() {
	head = (struct Node*)malloc(sizeof(struct Node)); // create a virtual node
	head->data = NULL;
	head->next = NULL;

	taskCount = 0;
	curr = NULL;
	preCurr = NULL;
	tail = NULL;
}

void TL_insertFront(STask* d) {
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	temp->data = d;
	temp->next = head->next;

	head->next = temp;

	taskCount++;
	if(taskCount == 1) {
		tail = head->next;
		curr = head->next;
	}
}

uint8_t TL_deleteID(uint32_t id) {
	struct Node* i = head->next;
	struct Node* prei = head;
	while(i != NULL && i->data->TaskID != id) {
		prei = i;
		i = i->next;
	}

	if(i == NULL) return 0; // id not found

	if(i == tail) {
		tail = prei;
	}
	if(i == curr) {
		curr = prei;
	}

	prei->next = i->next;

	if(i->data) {
		free(i->data);
	}
	free(i);


	taskCount--;

	return 1;
}

STask* TL_getCurrent() {
	if(curr && taskCount > 0) {
		return curr->data;
	}
	return NULL;
}



uint8_t TL_pointNext() {
	if(curr && curr != tail) {
		curr = curr->next;
		return 1;
	}
	return 0;
}

void TL_pointStart() {
	curr = head->next;
}

void TL_pointMark() {
	preCurr = curr;
}
void TL_restoreMark() {
	curr = preCurr;
}

uint32_t TL_size(void) {
	return taskCount;
}

