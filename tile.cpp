#include "headers/tile.h"

Tile::Tile(const sf::Color &color){
    m_displayColor = color;
    m_shape.setSize(sf::Vector2f(m_width, m_height));
    m_shape.setFillColor(color);
}


sf::Vector2i Tile::getTilePos(){
    sf::Vector2i tilePos;
    sf::Vector2f shapePos = m_shape.getPosition();
    tilePos.x = (shapePos.x - 1) / 15;
    tilePos.y = (shapePos.y - 1) / 15;
    return tilePos;
}
sf::Vector2f Tile::getTileWorldPos(){
    return m_shape.getPosition();
}

sf::RectangleShape Tile::getShape(){
    return m_shape;
}

void Tile::draw(sf::RenderWindow &window){
    window.draw(m_shape);
}

void Tile::setTilePosition(sf::Vector2f tilePos){
    sf::Vector2i newPos = tilePositionToWorldPosition(tilePos);
    
    m_shape.setPosition(tilePos.x, tilePos.y);
}

void Tile::setTilePosition(int x, int y){
    sf::Vector2i newPos = tilePositionToWorldPosition(sf::Vector2f(x, y));
    x = newPos.x;
    y = newPos.y;
    m_shape.setPosition(x, y);
}

sf::Vector2i Tile::tilePositionToWorldPosition(sf::Vector2f tilePos){
    sf::Vector2i posInTileSpace;
    /* 
    * Since tiles are of size 16 x 16 px, we need a co-relation
    * where (0, 0) = (0, 0)
    * (0, 1) = (0, 16)
    * (1, 0) = (16, 0)
    * ((0, 2) = (0, 32)
    * .
    * .
    * .
    * (x, y) = (x*16, y*16)
    */
   // Adding a small pixel offset
    posInTileSpace.x = tilePos.x * 15 + 1;
    posInTileSpace.y = tilePos.y * 15 + 1;

    return posInTileSpace;
}