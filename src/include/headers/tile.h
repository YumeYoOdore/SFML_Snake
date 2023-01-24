#pragma once
#include <SFML/Graphics.hpp>

class Tile{
private:
    const int m_height = 15;
    const int m_width = 15;
    sf::Color m_displayColor;
    sf::Vector2f m_Pos;
    sf::RectangleShape m_shape;

public:
    Tile(const sf::Color &color);
    Tile(){};
    ~Tile(){};
    
    sf::Vector2i getTilePos(); //Using this function to get tilePosition in tile space coordinates
    sf::Vector2f getTileWorldPos(); //Not sure if really need this: use this function to get tilePosition in world space coordinates
    sf::RectangleShape getShape();
    
    void draw(sf::RenderWindow &window);
    void setTilePosition(sf::Vector2f tilePos);
    void setTilePosition(int x, int y); //Override: set tiles given 2 integers rather than a vector2f

    //Utility function to convert tile space coordinates to world space coordinates (pixel coordinates) 
    sf::Vector2i tilePositionToWorldPosition(sf::Vector2f tilePos);
};