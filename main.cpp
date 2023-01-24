#include <SFML/Graphics.hpp>
#include "headers/tile.h"
#include "headers/snake.h"
#include <sstream>

void initFruit(Tile &fruit){
    srand((int)time(0));

    int fruitXpos;
    int fruitYpox;

    fruitXpos = rand() % 30;
    fruitYpox = rand() % 40;

    fruit.setTilePosition(fruitXpos, fruitYpox);
}

sf::Text initText(sf::Font &font, const sf::String &string, int xpos, int ypos, int characterSize = 30)
{
    sf::Text newText;
    newText.setFont(font);
    newText.setString(string);
    newText.setPosition(xpos, ypos);
    newText.setCharacterSize(characterSize);

    return newText;
}

int main(int argc, char** argv){

    sf::RenderWindow window(sf::VideoMode(480, 640), "SUNEEKU", sf::Style::Default);

    sf::Font font;
    font.loadFromFile("fonts/ModernDOS8x16.ttf");

    sf::Text gameOverText = initText(font, "Game Over", 165, 290); 
    sf::Text restartText = initText(font, "Press enter to restart", 120, 330, 20);
    sf::Text scoreText = initText(font, "Score: 0", 300, 5);
    
    int scoreVal = 0;

    Snake snake;

    Tile fruit(sf::Color::Red);
    initFruit(fruit);

    bool isFruitSpawned = true;

    float timer = 0.f;
    float delay = 0.1f;
    float keyBoardDelay = 0.09f;
    bool wasKeyRecentlyPressed = false;
    sf::Clock clock;

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        //Can comment this if exiting by esc is annoying
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            window.close();
        }

        if(snake.isAlive()){
            
            if(!wasKeyRecentlyPressed){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                    snake.changeDirection(Direction::LEFT);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                    snake.changeDirection(Direction::RIGHT);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                    snake.changeDirection(Direction::UP);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                    snake.changeDirection(Direction::DOWN);
                }
                wasKeyRecentlyPressed = true;
            }

            //Check head collision with food
            if(*snake.getHeadPosition() == fruit.getTilePos() && isFruitSpawned){
                isFruitSpawned = false;
                scoreVal += 1;
                snake.grow();
            }
            
            std::stringstream scoress;
            scoress << "Score: " << scoreVal;

            scoreText.setString(scoress.str());

            float dtime = clock.getElapsedTime().asSeconds();
            timer += dtime;

            sf::Time dt = clock.restart();
            
            window.clear();
            
            /*for (auto &tile: multipleTiles){
                tile.draw(window);
            }*/

            if (isFruitSpawned){
                fruit.draw(window);
            }else{
                initFruit(fruit);
                isFruitSpawned = true;
            }
            snake.update(window, dt.asSeconds());

            if(timer > keyBoardDelay){
                wasKeyRecentlyPressed = false;
            }

            if(timer > delay){
                //check collision before moving
                snake.checkCollisions();
                snake.move();
                timer = 0.f;
            }
        }else{
            window.draw(gameOverText);
            window.draw(restartText);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                scoreVal = 0;
                snake.initSnake();                
            }
        }

        window.draw(scoreText);
        window.display();

    }
    return 0;
}