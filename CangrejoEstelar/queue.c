#include "entrega.h"
#include "veinteveinte.h"

Queue QueueCreate(Queue q, u32 n)
{
    q = malloc(sizeof(struct QueueSt));
    if (!q)
        return NULL;

    q->size = n-1;

    q->array = malloc(q->size*sizeof(unsigned int));
    if (!q->array)
    {
        free(q);
        q = NULL;

        return NULL;
    }

    q->front = 0;
    q->rear = -1;
    q->itemCount = 0;

    return q;
}

void QueueDestroy(Queue q)
{
    if (!q)
        return;

    free(q->array);
    free(q);
    q = NULL;
}

bool QueueIsEmpty(Queue q)
{
    return q->itemCount == 0;
}

bool QueueIsFull(Queue q)
{
    return q->itemCount == q->size;
}

Queue QueueInsert(Queue q, u32 data)
{
    if (!QueueIsFull(q))
    {
        if (q->rear == (int) (q->size-1))
            q->rear = -1;

        q->array[++(q->rear)] = data;
        q->itemCount++;
    }

    return q;
}

u32 QueueRemoveData(Queue q)
{
    u32 data = q->array[q->front++];

    if (q->front == q->size)
        q->front = 0;

    q->itemCount--;

    return data;
}
