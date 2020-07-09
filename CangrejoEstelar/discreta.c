#include <time.h>
#include "entrega.h"


u32 Greedy(Grafo G)
{
    if(G == NULL)
        return UINTMAX;


    u32 i, j, totalColores;
    totalColores = 1;
    u32 *colores = calloc(NumeroDeVertices(G), sizeof(u32));

    //Seteo todos los colores previos
    for(i = 0; i < NumeroDeVertices(G); i++)
        FijarColor(UINTMAX, i, G);

    //Coloreo el primer vertice
    FijarColor(0,0,G);
    colores[0] = 0;
    for(i = 1; i < NumeroDeVertices(G); i++)
    {

        for(j = 0; j < Grado(i, G); j++)
        {
            if(ColorVecino(j, i, G) != UINTMAX)
                colores[ColorVecino(j, i, G)] = 1;
        }
        for(j = 0; j < totalColores; j++)
        {
            if (colores[j] == 0)
            {
                FijarColor(j, i, G);
                break;
            }
        }
        if(totalColores == j)
        {
            FijarColor(totalColores, i, G);
            totalColores += 1;
        }
        for(j = 0; j < totalColores; j++)
            colores[j] = 0;
    }

    free(colores);
    colores = NULL;

    return totalColores;
}


char Bipartito(Grafo G)
{
    if (G == NULL)
        return 0;

    u32 i = 0;
    u32 j = 0;
    u32 n = NumeroDeVertices(G);
    u32 p = 0;
    u32 w = 0;
    u32 x = 0;

    //Antes que nada los ordeno en orden creciente natural
    for(i=0; i < NumeroDeVertices(G); i++)
        FijarOrden(i, G, i);

    //Creo la cola
    Queue q = NULL;
    q = QueueCreate(q, n);

    //Descoloreamos vertices
    Decolorear(G);
    j = 0;

    while(j < n){
        for(i = x; i < n; i++)
        {
            if(Color(i, G) == UINTMAX)
            {
                x = i + 1;
                break;
            }
        }
        FijarColor(0, x-1, G);
        j++;

        QueueInsert(q, x-1);


        while(!QueueIsEmpty(q)){
            p = QueueRemoveData(q);

            for(w=0; w<Grado(p, G); w++)
            {
                if(ColorVecino(w, p, G) == UINTMAX)
                {
                    q = QueueInsert(q, OrdenVecino(w, p, G));
                    j++;
                    u32 u = 1 - (Color(p, G));
                    FijarColor(u,OrdenVecino(w, p, G), G);
                }
            }
        }
    }

    for(i = 0; i < n; i++){
        for(j = 0; j < Grado(i, G); j++){
            if(Color(i, G) == Color(OrdenVecino(j, i, G), G)){
                QueueDestroy(q);
                Greedy(G);
                return 0;
            }
        }
    }

    QueueDestroy(q);
    return 1;
}


char SwitchColores(Grafo G, u32 i, u32 j)
{
    u32 coloresTotales = contarColores(G);
    if(G == NULL || coloresTotales <= i || coloresTotales <= j)
        return 1;

    for(u32 x = 0; x < NumeroDeVertices(G); x++)
    {
        if(Color(x,G) == i)
            FijarColor(j, x, G);
        else if(Color(x, G) == j)
            FijarColor(i, x, G);
    }
    return 0;
}


char WelshPowell(Grafo G)
{
    if(G == NULL)
        return 1;

    u32 N = NumeroDeVertices(G);
    dupla array = malloc(N *sizeof(struct Dupla2));

    if(array == NULL)
        return 1;

    for(u32 i = 0; i < N; i++)
    {
        FijarOrden(i, G, i);
        array[i].grado = Grado(i, G);
        array[i].posicion = i;
    }

    qsort(array, N, sizeof(struct Dupla2), gradoDecreciente);

    for (u32 i = 0; i < N; i++)
        FijarOrden(i, G, array[i].posicion);

    free(array);
    array = NULL;

    return 0;
}


char RevierteBC(Grafo G)
{
    if (G == NULL) 
        return 1;

    u32 N = NumeroDeVertices(G);
    dupla array = malloc(N * sizeof(struct Dupla2));

    if(array == NULL)
        return 1;

    for (u32 i = 0; i < N; i++)
    {
        FijarOrden(i, G, i);
        array[i].grado = Color(i, G);
        array[i].posicion = i;
    }

    qsort(array, N, sizeof(struct Dupla2), gradoDecreciente);

    for (u32 i = 0; i < NumeroDeVertices(G);i++)
        FijarOrden(i, G, array[i].posicion);

    free(array);
    array = NULL;

    return 0;
}


char ChicoGrandeBC(Grafo G)
{
    if (G == NULL) 
        return 1;

    u32 N = NumeroDeVertices(G);

    u32 *cantidad = calloc(N, sizeof(u32));

    if (cantidad == NULL)
        return 1;

    tripla array = malloc(N * sizeof(struct Tripla3));

    if (array == NULL)
        return 1;

    for (u32 i = 0; i < N; i++) {
        FijarOrden(i, G, i);
        cantidad[Color(i, G)]++;
        array[i].orden = i;
        array[i].color = Color(i, G);
    }

    for (u32 i = 0; i < N; i++)
        array[i].cantidad = cantidad[Color(i, G)];

    qsort(array, N, sizeof(struct Tripla3), sortChicoGrande);

    for (u32 i = 0; i < N; i++) 
        FijarOrden(i, G, array[i].orden);

    free(array);
    array = NULL;
    free(cantidad);
    cantidad = NULL;

    return 0;
}

char AleatorizarVertices(Grafo G, u32 R)
{
    u32 temp, randomIndex, i;
    temp = 0;
    randomIndex = 0;

    u32 *array = calloc(NumeroDeVertices(G), sizeof(u32));
    
    for(i = 0; i < NumeroDeVertices(G); i++)
        array[i] = i;
    
    srand(R);

    for (i = 0; i < NumeroDeVertices(G); i++) 
    {
        temp = array[i];
        randomIndex = (u32) rand() % NumeroDeVertices(G);
        array[i] = array[randomIndex];
        array[randomIndex] = temp;
    }
    for(i = 0; i < NumeroDeVertices(G); i++)
        FijarOrden(i,G,array[i]);
    
    free(array);
    array = NULL;

    return 0;
}



u32 NumCCs(Grafo G)
{
    u32 *cc = calloc(NumeroDeVertices(G), sizeof(u32));
    u32 id = 0;

    for(u32 v = 0; v < NumeroDeVertices(G); v++)
    {
        cc[v] = UINTMAX;
        FijarOrden(v, G, v);
    }

    for(u32 v = 0; v < NumeroDeVertices(G); v++)
    {
        if(cc[v] == UINTMAX)
        {
            id+=1;
            dfs(G, v, id,cc);
        }
    }

    free(cc);
    cc = NULL;

    return id;
}

// Extras

u32 contarColores(Grafo G)
{
    u32 *colores = calloc(NumeroDeVertices(G), sizeof(u32));
    u32 count = 0;

    for(u32 v = 0; v < NumeroDeVertices(G); v++)
        colores[v] = UINTMAX;

    for(u32 v = 0; v < NumeroDeVertices(G); v++)
    {
        if(colores[Color(v, G)] == UINTMAX)
        {
            colores[Color(v, G)] = 1;
            count += 1;
        }
    }

    free(colores);
    colores = NULL;

    return count;
}


void dfs(Grafo G, u32 v, u32 id, u32*cc)
{
    cc[v] = id;
    for(u32 a = 0; a < Grado(v,G); a++)
    {
        if(cc[OrdenVecino(a, v, G)] == UINTMAX)
            dfs(G, OrdenVecino(a, v, G), id, cc);
    }
}


void Decolorear(Grafo G)
{
    for(u32 i = 0; i < NumeroDeVertices(G); i++)
        FijarColor(UINTMAX, i, G);
}

int gradoDecreciente(const void * i, const void * j)
{
    dupla a, b;
    a = (dupla) i;
    b = (dupla) j;
    if(a->grado < b->grado) return 1;
    else if(a->grado == b->grado) return 0;
    else return -1;
}

int sortChicoGrande(const void * _a, const void * _b) {
    tripla a, b;
    a = (tripla) _a;
    b = (tripla) _b;

    if (a->cantidad == b->cantidad)
    {
        if (a->color < b->color) return -1;
        else if (a->color == b->color) return 0;
        else return 1;
    }
    else 
    {
        if (a->cantidad < b->cantidad) return -1;
        else if (a->cantidad == b->cantidad) return 0;
        else return 1;
    }
}

