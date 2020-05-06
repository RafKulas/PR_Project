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

void qinsert(pqueue **phead, void *data, int k) 
{
	pqueue *elem = *phead;
	if (elem == NULL)
	{
		elem = (pqueue*)malloc(sizeof(pqueue));
		elem->k = k;
		elem->data = data;
		elem->next = NULL;
		elem->prev = NULL;
		*phead = elem;
		return;
	}
	else
	{		
		for (;; elem = elem->next)
		{				
			if(k >= elem->k)
			{
				pqueue* new_elem = (pqueue*)malloc(sizeof(pqueue));
				new_elem->k = k;
				new_elem->data = data;
				new_elem->next = elem;
				new_elem->prev = elem->prev;
				elem->prev = new_elem;
				if(new_elem->prev != NULL)new_elem->prev->next = new_elem;
				if (elem == (*phead))*phead = new_elem;
				return;
			}
			if(elem->next==NULL)
			{
				pqueue* new_elem = (pqueue*)malloc(sizeof(pqueue));
				new_elem->k = k;
				new_elem->data = data;
				new_elem->next = NULL;
				new_elem->prev = elem;
				elem->next = new_elem;
				return;	
			}
		}			
	}
}

void qremove(pqueue **phead, int k) 
{
	pqueue *elem = *phead;
	if(elem == NULL)
	{
		printf("Nie mozna usunac elementu z pustej kolejki\n");
	}
	else
	{		
		for (; elem != NULL; elem = elem->next)
		{
			if(elem->k == k)
			{
				while (elem->k == k)
				{
					pqueue* help = elem;
					if (help->next != NULL)
					{
						help->next->prev = help->prev;
						if (elem == (*phead))*phead = elem->next;
					}
					if (help->prev != NULL)
					{
						help->prev->next = help->next;
					}
					if (elem == (*phead) && elem->next == NULL)*phead = NULL;
					elem = elem->next;
					free(help);
					if (elem == NULL)return;
				}
				return;
			}	
		}
	}
}