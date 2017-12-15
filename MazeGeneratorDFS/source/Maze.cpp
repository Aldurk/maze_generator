#include "../include/Maze.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


/*******************************************************************

    Generador de laberintos aleatorios utilizando el algoritmo DFS.

    Para cualquier duda o sugerencia: @_aldurk (Twitter)

********************************************************************/


/**
    Constructor

    h -> altura del laberinto
    w -> anchura del laberinto
**/
Maze::Maze(int h, int w)
{
    srand (time(NULL));
    height = h;
    width = w;
}

/**
    Destructor
**/
Maze::~Maze()
{
    delete[] nodes;
}

/**
    Inicializa los valores de cada nodo
**/
void Maze::start()
{
    nodes = new NODE[height*width];

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            nodes[i*width+j].state = WALL;
            nodes[i*width+j].parent = NULL;
            nodes[i*width+j].numDirs = 0;
            nodes[i*width+j].x = i;
            nodes[i*width+j].y = j;
        }
    }
}

/**
    IN: n, un entero con el numero de nodo a tratar.
    (PRE: esta en el array de nodos)

    OUT: TRUE  -> El nodo esta marcado, es decir, ya esta tratado.
         FALSE -> c.c.

**/
bool Maze::isMarked(int n)
{
    if(nodes[n].state == MARKED)
        return true;
    return false;
}

/**
    IN: n, un entero con el numero de nodo a tratar.
    (PRE: esta en el array de nodos)

    OUT: TRUE  -> El nodo es una pared, es decir, aun no se ha tratado.
         FALSE -> c.c.

**/
bool Maze::isWall(int n)
{
    if(nodes[n].state == WALL)
        return true;
    return false;
}

/**
    IN:
        n, un entero con el numero de nodo a tratar.
        (PRE: esta en el array de nodos)

    OUT: El nodo padre correspondiente a ese nodo.

**/
NODE* Maze::getParent(int n)
{
    return nodes[n].parent;
}

/**
    Comienza la creacion del laberinto, iniciando los nodos y
    llamando a la funcion recursiva makeMaze(Node *n)
**/
void Maze::makeMaze()
{
    start();
    makeMaze(&nodes[rand() % (height*width)-1]);
}

/**
    Crea el laberinto desde el nodo recibido.
    Empieza marcandolo, es decir, el nodo ya esta procesado.

    Lo siguiente que hace es guardar las direcciones posibles
    a las que puede ir con la funcion saveNeightbours(int n).

    Finalmente, comprueba todos los nodos adyacentes a los que puede ir:

    Si el nodo no tiene padre, se marca a si mismo como su padre y lo procesa,
    en caso contrario, ya ha sido procesado por otro nodo, por lo tanto,
    no hace nada con el.
**/
void Maze::makeMaze(NODE *n)
{
    n->state = MARKED;
    saveNeighbours((n->x*width)+(n->y));

    while(n->numDirs > 0)
    {
        NODE* next = nextNode(n->x*width+n->y);

        if(next->parent == NULL)
        {
            next->parent = n;
            makeMaze(next);
        }
    }
}

/**
    Muestra en la consola si cada nodo esta marcado o no.
**/
void Maze::showMaze()
{

    for(int i = 0; i < height; i++)
    {
	 for(int j = 0; j < width; j++)
	 {
        if(isMarked(i*width+j))
            printf("%c",'M');
        else if(isWall(i*width+j))
            printf("%c",'W');
	 }

     printf("\n");
    }
}

/**
    IN:
        n, un entero con el numero de nodo a tratar.
        (PRE: esta en el array de nodos)

        *i, un puntero a un entero para la posicion
            del nodo adyacente de arriba del nodo recibido.

    OUT: 1 -> Esa posicion existe.
         0 -> c.c.
**/
int Maze::up(int n, int *i)
{
    if(width <= n && n < width*height)
    {
        *i = n-width;
        return 1;
    }

    return 0;
}

/**
    IN:
        n, un entero con el numero de nodo a tratar.
        (PRE: esta en el array de nodos)

        *i, un puntero a un entero para la posicion
            del nodo adyacente de abajo del nodo recibido.

    OUT: 1 -> Esa posicion existe.
         0 -> c.c.
**/
int Maze::down(int n, int *i)
{
     if(0 <= n && n < (width*height)-width)
    {
        *i = n+width;
        return 1;
    }

    return 0;
}

/**
    IN:
        n, un entero con el numero de nodo a tratar.
        (PRE: esta en el array de nodos)

        *i, un puntero a un entero para la posicion
            del nodo adyacente de la derecha del nodo recibido.

    OUT: 1 -> Esa posicion existe.
         0 -> c.c.
**/
int Maze::right(int n, int *i)
{
    if((n+1)%width != 0)
    {
        *i = n+1;
        return 1;
    }

    return 0;
}

/**
    IN:
        n, un entero con el numero de nodo a tratar.
        (PRE: esta en el array de nodos)

        *i, un puntero a un entero para la posicion
            del nodo adyacente de la izquierda del nodo recibido.

    OUT: 1 -> Esa posicion existe.
         0 -> c.c.
**/
int Maze::left(int n, int *i)
{
    if(n%width!=0)
    {
        *i = n-1;
        return 1;
    }

    return 0;
}

/**
    IN:
        n, un entero con el numero de nodo a tratar.
        (PRE: esta en el array de nodos)

    Obtiene las direcciones posibles que puede ir desde ese nodo
    y la cantidad de ellos.
**/
void Maze::saveNeighbours(int n)
{
    int i;
    NODE* node = &nodes[n];

    if(up(n, &i) && nodes[i].state == WALL)
    {
        node->dirs[node->numDirs] = UP;
        node->numDirs++;
    }

    if(down(n, &i) && nodes[i].state == WALL)
    {
        node->dirs[node->numDirs] = DOWN;
        node->numDirs++;
    }

    if(right(n, &i) && nodes[i].state == WALL)
    {
        node->dirs[node->numDirs] = RIGHT;
        node->numDirs++;
    }

    if(left(n, &i) && nodes[i].state == WALL)
    {
        node->dirs[node->numDirs] = LEFT;
        node->numDirs++;
    }
}

/**
    IN:
        n, un entero con el numero de nodo a tratar.
        (PRE: esta en el array de nodos)

    OUT: Un puntero al siguiente nodo

    Selecciona aleatoriamente el siguiente nodo a tratar desde el nodo recibido.
**/
NODE* Maze::nextNode(int n)
{
    NODE* node = &nodes[n];
    int dir = rand() % node->numDirs;

    int i;
    switch(node->dirs[dir])
    {
        case UP:
            up(n, &i);
            break;
        case DOWN:
            down(n, &i);
            break;
        case RIGHT:
            right(n, &i);
            break;
        case LEFT:
            left(n, &i);
            break;
    }

    node->numDirs--;
    node->dirs[dir] = node->dirs[node->numDirs];
    return &nodes[i];
}
