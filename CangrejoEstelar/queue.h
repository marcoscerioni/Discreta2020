#include "GrafoSt2020.h"

Queue QueueCreate(Queue q, u32 n);
void QueueDestroy(Queue q);
bool QueueIsEmpty(Queue q);
bool QueueIsFull(Queue q);
Queue QueueInsert(Queue q, u32 data);
u32 QueueRemoveData(Queue q);
