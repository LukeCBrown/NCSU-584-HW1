#include <SFML/Graphics.hpp>

int main() 
{
    sf::RenderWindow window(sf::VideoMode({640,480}), "CSC 584 HW1");
    sf::Texture texture;
    texture.loadFromFile("boid-sm.png");
    sf::Sprite sprite(texture);
    float xMovement = 0.05f;
    float yMovement = 0.0f;
    int pos = 0;
    
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
        sprite.move({xMovement, yMovement});
        
        // Makes sure the sprite is always on screen. Originally i hardcoded a number like 619.9f but thats actually bad practice.
        if (pos == 0 && (sprite.getPosition().x) >= 640.f) 
        {
            sprite.rotate(sf::degrees(90));
            xMovement = 0.0f;
            yMovement = 0.03f;
            pos = 1;
        }

        window.display();
    }

    return 0;
}