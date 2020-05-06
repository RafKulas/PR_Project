typedef struct pqueue pqueue;
struct pqueue 
{
	int k;
	void *data;
	pqueue *next;
	pqueue *prev;
};

void
qinsert(pqueue **phead, void *data, int k);

void
qlist(pqueue *head, void (*print_data)(void *));

pqueue *qpop(pqueue **phead);
