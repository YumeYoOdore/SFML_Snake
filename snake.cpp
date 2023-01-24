#include "headers/snake.h"
#include "headers/tile.h"
#include <stdio.h>

Snake::Snake(){
    initSnake();
}

Snake::~Snake(){
    free(m_head);
    free(m_headPosition);
}

void Snake::initSnake(){
    //m_Speed = 1; //Setting speed as 15
    m_size = 3; //Starting snake size = 3 
    m_direction = Direction::LEFT; //The snake starts moving to the left

    sf::Vector2i *initial_head_position = new sf::Vector2i(15, 20);
    setHeadPosition(initial_head_position);

    //Init tail
    if(!m_tailPositions.empty())
        m_tailPositions.clear();
    for(int i=1; i<= m_size; i++){
        sf::Vector2i* vector = new sf::Vector2i(15 + i, 20);
        m_tailPositions.push_back(vector);
    }

    m_head = new Tile(sf::Color::Green);
    m_head->setTilePosition(initial_head_position->x, initial_head_position->y);
    m_isAlive = true;
}

void Snake::changeDirection(Direction dir){
    //Check if we can move to the target direction
    if((dir == Direction::DOWN || dir == Direction::UP) &&
    (m_direction != Direction::DOWN && m_direction != Direction::UP)){
        m_direction = dir;
    }

    if((dir == Direction::LEFT || dir == Direction::RIGHT) &&
    (m_direction != Direction::LEFT && m_direction != Direction::RIGHT)){
        m_direction = dir;
    }
    
}

void Snake::update(sf::RenderWindow &window, float dtAsSeconds){
    //USE THIS FUNCTION TO UPDATE THE SNAKE POSITION AND HAVE EACH TILE DRAW ITSELF
    sf::Vector2i *pos = getHeadPosition();

    m_head->draw(window);

    Tile *drawTile = new Tile(sf::Color::Green);
    for(auto *tailPos: m_tailPositions){
        drawTile->setTilePosition(tailPos->x, tailPos->y);
        drawTile->draw(window);
    }

}

void Snake::checkCollisions(){
    sf::Vector2i *pos = getHeadPosition();
    //Check for collisions with body
    if(pos->x < 0 || pos->x > 30){
        //printf("Collision with wall! AT %d, %d... DED\n", pos->x, pos->y); //Comment this at the end
        m_isAlive = false;
    }
    
    if(pos->y < 0 || pos->y > 42){
        //printf("Collision with wall! AT %d, %d... DED\n", pos->x, pos->y); //Comment this at the end
        m_isAlive = false;
    }

    for(auto *tailPos: m_tailPositions){
        if(pos->x == tailPos->x && pos->y == tailPos->y){
            printf("COLLISION WITH OWN BODY!\n"); //Comment this at the end
            m_isAlive = false;
        }
    }
}

void Snake::grow(){
    //Creating a new position vector for the new tail element and adding it at the end of the snake
    sf::Vector2i* vector = m_tailPositions.at(m_size-1);
    m_tailPositions.push_back(vector);
    m_size += 1; //Increase size by 1
}

void Snake::setHeadPosition(sf::Vector2i *pos){
    m_headPosition = pos;
    //m_head->setTilePosition(pos->x, pos->y);
}

void Snake::move(){
    //USE THIS FUNCTION TO UPDATE THE SNAKE POSITION AND HAVE EACH TILE DRAW ITSELF
    sf::Vector2i *pos = getHeadPosition();
    sf::Vector2i *newPos = new sf::Vector2i(pos->x, pos->y);
    if(m_direction == Direction::LEFT)
        newPos->x -= 1;
    if(m_direction == Direction::RIGHT)
        newPos->x += 1;
    if(m_direction == Direction::UP)
        newPos->y -= 1;
    if(m_direction == Direction::DOWN)
        newPos->y += 1;

    setHeadPosition(newPos);

    for(int i=0; i< m_size ; i++){
        sf::Vector2i *tmp = m_tailPositions[i];
        m_tailPositions[i] = pos;
        pos = tmp;
    }
    m_head->setTilePosition(pos->x, pos->y);
}

sf::Vector2i *Snake::getHeadPosition(){
    return m_headPosition;
}

bool Snake::isAlive(){
    return m_isAlive;
}