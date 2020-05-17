#include <stdio.h>
#include <stdlib.h>
#include "priority_queue_list.h"

void
qlist(pqueue *head, void (*print_data)(void *)) {
	pqueue *p;
	
	for (p = head; p != NULL; p = p->next) {
		printf("%d: ", p->k);
		print_data(p->data);
		printf("\n");
	}
	
}

pqueue *
qpop(pqueue **phead) {
	pqueue *p, *head;
	
	head = *phead;
	if (head == NULL) {
		return NULL;
	}
	
	p = head->next; // new head
	if (p != NULL) {
		p->prev = NULL;
	}
	*phead = p; //save new head
	
	return head;
}

void
qinsert(pqueue **phead, void *data, int k) {
	pqueue *p, *head;
	pqueue *new = (pqueue *)malloc(sizeof(pqueue));
	
	new->k = k;
	new->data = data;
	new->next = new->prev = NULL;
	
	head = *phead;
	if (head == NULL) {
		*phead = new;
		return;
	// insert element at the begingin of the queue
	} else if (head->k <= new->k) {
		new->next = head;
		head->prev = new;
		*phead = new;
		return;
	}
	
	p = head;
	while (p != NULL && p->k > new->k) {
		//insert element at the end of the queue
		if (p->next == NULL) {
			p->next = new;
			new->prev = p;
			return;
		}
		p = p->next;
	}
	// insert element before "p"
	new->next = p;
	new->prev = p->prev;
	
	p->prev->next = new;
	p->prev = new;
}