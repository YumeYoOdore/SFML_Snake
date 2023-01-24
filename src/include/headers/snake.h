#pragma once
#include <SFML/Graphics.hpp>
#include "headers/tile.h"

enum class Direction{
    UP, DOWN, LEFT, RIGHT
};

class Snake
{
private:
    
    //DEPRECATED: THIS WOULD TAKE A LOT OF MEMORY
    //Storing the snake body (in tiles) in a vector for later rendering
    Tile *m_head; //Keeping a separate pointer for the head 

    //Storing a pointer of the current head position
    sf::Vector2i *m_headPosition;
    //Storing a pointer to the current location of each member in the tail
    std::vector<sf::Vector2i*> m_tailPositions;
    int m_size;
    
    Direction m_direction;
    float m_Speed;
    bool m_isAlive;

public:
    Snake();
    ~Snake();

    Tile *getHead(); //Used to get a pointer of the head
    sf::Vector2i *getHeadPosition();

    //Used to start or restart the game
    void initSnake();

    void setHeadPosition(sf::Vector2i *pos);
    void changeDirection(Direction dir);
    void update(sf::RenderWindow &window, float dtAsSeconds);
    void checkCollisions();

    void move();
    void grow();
    bool isAlive();
};