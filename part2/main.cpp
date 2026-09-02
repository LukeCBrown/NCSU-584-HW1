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
        sprite.move({0.05f, 0.0f});
        
        // Makes sure the sprite is always on screen. Originally i hardcoded a number like 619.9f but thats actually bad practice.
        if (sprite.getPosition().x  + sprite.getGlobalBounds().size.x >= 640.f) 
        {
            sprite.setPosition({0.0f, 0.0f});
        }

        window.display();
    }

    return 0;
}