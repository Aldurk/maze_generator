#ifndef Maze_H
#define Maze_H

enum DIRECTION { UP, DOWN, RIGHT, LEFT };
enum STATE { WALL, MARKED };

/**
    Nodos de un grafo, en el contexto del laberinto, son una parte del camino.

    dirs    -> Son las direcciones posibles desde el nodo
               y que aun no han sido comprobadas.
    parent  -> Su nodo padre. En el contexto del laberinto,
               entre el nodo hijo y el padre habra un camino.
    state   -> El estado en que esta el nodo:
               WALL, aun no ha sido procesado.
               MARKED, ya esta procesado.
    x,y     -> Las coordenadas que le corresponde en el laberinto.
    numdirs -> El numero de direcciones que aun no ha visitado.
**/
typedef struct NODE
{
    DIRECTION dirs[4];
    NODE *parent;
    STATE state;
    int x, y;
    int numDirs;
} NODE;

class Maze
{
    public:
        Maze(int h, int w);
        virtual ~Maze();

        void makeMaze();
        void showMaze();
        bool isMarked(int n);
        bool isWall(int n);
        NODE* getParent(int n);

    private:
        int width, height;
        NODE* nodes;

        int up(int n, int *i);
        int down(int n, int *i);
        int right(int n, int *i);
        int left(int n, int *i);

        void start();
        void makeMaze(NODE *n);
        void saveNeighbours(int n);
        NODE* nextNode(int n);
};


#endif // Maze_H
