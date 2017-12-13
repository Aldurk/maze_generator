#include "include/Maze.h"
#include <SFML/Graphics.hpp>

int tamX = 100;
int tamY = 100;

/***************************************************************************

    Un ejemplo de como mostrar el laberinto utilizando la librearia SFML

***************************************************************************/


/**
    Muestra el laberinto
**/
void showMaze(Maze* l, sf::RenderWindow *window)
{
    sf::RectangleShape rectangle(sf::Vector2f((tamX*10)+5, (tamY*10)+5));
    rectangle.setFillColor(sf::Color::White);
    window->draw(rectangle);

    for(int i = 0; i < tamX; i++)
    {
	 for(int j = 0; j < tamY; j++)
	 {
        //Muestra el nodo, el cual estara rodeado de paredes
        sf::RectangleShape rectangle(sf::Vector2f(5,5));
        rectangle.setFillColor(sf::Color::Black);
        rectangle.move(5*((i*2)+1),5*((j*2)+1));
        window->draw(rectangle);

        //Si tiene padre, borrara la pared que hay entre ellos
        NODE* n = l->getParent(i*tamY+j);
        if(n != NULL)
        {
            if(n->x > i)
                rectangle.move(5,0);
            else if(n->y > j)
                rectangle.move(0,5);
            else if(n->x < i)
                rectangle.move(-5,0);
            else if(n->y < j)
                rectangle.move(0,-5);

            window->draw(rectangle);
        }
	 }

     printf("\n");
    }
}

/**
    Muestra la ventana, el tamaño se ajustara al del laberinto
**/
void showWindow(Maze* l)
{
    sf::RenderWindow window(sf::VideoMode((tamX*10)+5, (tamY*10)+5), "Laberinto");
    showMaze(l, &window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::R)
                {
                    l->makeMaze();
                    showMaze(l, &window);
                }
            }

            if (event.type == sf::Event::Resized)
            {
                showMaze(l, &window);
            }

            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.display();
    }
}

int main(int argc, char *argv[])
{
    if(argc > 2)
    {
        tamX = atoi(argv[1]);
        tamY = atoi(argv[2]);
    }

    Maze* l = new Maze(tamX,tamY);
    l->makeMaze();
    showWindow(l);

    return 0;
}

