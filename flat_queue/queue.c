#include <stdio.h>
#include <math.h>

#define MAX_QUEUE_MEMBERS 64
typedef struct queue_t
{
	int items[MAX_QUEUE_MEMBERS];
	int count;
	int front;
	int back;
} Queue;
int queueInit(Queue *queue);
int queueIsFull(Queue *queue);
int queueIsEmpty(Queue *queue);
int queueInsert(Queue *queue, int item);
int queueFirst(Queue *queue);

int queueInit(Queue *queue)
{
		queue->count = 0;
		queue->front = 0;
		queue->back = 0;
}

int queueInsert(Queue *queue, int item)
{
	if(queueIsFull(queue)) return -1;
	queue->items[queue->back] = item;
	if(queue->back + 1 < MAX_QUEUE_MEMBERS)
		queue->back++;
	else
		queue->back = 0;
	return queue->count++;
}

int queueIsFull(Queue *queue)
{
	if(queue->count >= MAX_QUEUE_MEMBERS)
		return 1;
	else
		return 0;
}

int queueIsEmpty(Queue *queue)
{
	if(queue->back == queue->front && queue->count == 0)
		return 1;
	else
		return 0;
}

int queueFirst(Queue *queue)
{
	if(queueIsEmpty(queue)) return -1;
	int firstItem = queue->items[queue->front];
	queue->front++;
	queue->count--;
	if(queue->front >= MAX_QUEUE_MEMBERS)
			queue->front = 0;
	return firstItem;
}
