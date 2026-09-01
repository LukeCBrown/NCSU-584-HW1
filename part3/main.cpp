#include <SFML/Graphics.hpp>

int main() 
{
    sf::RenderWindow window(sf::VideoMode({640,480}), "CSC 584 HW1");
    sf::Texture texture;
    texture.loadFromFile("boid-sm.png");
    sf::Sprite sprite(texture);

    sprite.setScale({3.f, 3.f});

    while(window.isOpen()) 
    {
        
        while(const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        window.clear(sf::Color::White);
        window.draw(sprite);
        sprite.move({.05f, .0f});
        
        if (sprite.getPosition().x >= 610.9f) 
        {
            sprite.setPosition({0.f, 0.f});
        }

        window.display();
    }

    return 0;
}