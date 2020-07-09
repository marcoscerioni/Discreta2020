#include "veinteveinte.h"
#include "stdbool.h"

typedef struct BloqueSt *bloque;
typedef struct QueueSt *Queue;
typedef struct Dupla2 *dupla;
typedef struct Tripla3 *tripla;

#define UINTMAX 4294967295

struct BloqueSt{
    u32 cantidad;
    u32 *indexVert;
    u32 next;
};

struct Dupla2{
    u32 posicion;
    u32 grado;
};

struct Tripla3 {
    u32 color;
    u32 orden;
    u32 cantidad;
};


struct QueueSt
{
    u32 size;
    u32 *array;
    u32 front;
    int rear;
    u32 itemCount;
};


// Cola
Queue QueueCreate(Queue q, u32 n);
void QueueDestroy(Queue q);
bool QueueIsEmpty(Queue q);
bool QueueIsFull(Queue q);
Queue QueueInsert(Queue q, u32 data);
u32 QueueRemoveData(Queue q);


// Extras
u32 contarColores(Grafo G);
void dfs(Grafo G, u32 v, u32 id, u32*cc);
void Decolorear(Grafo G);
int gradoDecreciente(const void * i, const void * j);
int sortChicoGrande(const void * _a, const void * _b);
