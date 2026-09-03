#include <SFML/Graphics.hpp>

int main() 
{
    sf::RenderWindow window(sf::VideoMode({640,480}), "CSC 584 HW1");
    sf::Texture texture;
    texture.loadFromFile("boid-sm.png");
    sf::Sprite sprite(texture);
    float xMovement = 0.05f;
    float yMovement = 0.0f;

    // positions 0-3: 0: right, 1: down, 2: left, 3: up
    int pos = 0;

    float margin = 15.0f;
    
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
        

        auto bounds = sprite.getLocalBounds();

        sprite.setOrigin({
        bounds.size.x / 2.f,
        bounds.size.y / 2.f
        });

        sprite.setPosition({
        margin + sprite.getGlobalBounds().size.x / 2.f,
        margin + sprite.getGlobalBounds().size.y / 2.f
        });

        sprite.move({xMovement, yMovement});
        
        // Makes sure the sprite is always on screen. Originally i hardcoded a number like 619.9f but thats actually bad practice.
        if ((sprite.getPosition().x + sprite.getGlobalBounds().size.x/2) >= (640.f - margin) && pos == 0) 
        {
            pos = 1;
            sprite.rotate(sf::degrees(90));
            xMovement = 0.0f;
            yMovement = 0.05f;
        }
        if ((sprite.getPosition().y + sprite.getGlobalBounds().size.y/2) >= (480.f - margin) && pos == 1) 
        {
            pos = 2;
            sprite.rotate(sf::degrees(90));
            xMovement = -0.05f;
            yMovement = 0.0f;
        }

        if ((sprite.getPosition().x - sprite.getGlobalBounds().size.x/2) <= margin && pos == 2) 
        {
            pos = 3;
            sprite.rotate(sf::degrees(90));
            xMovement = 0.0f;
            yMovement = -0.05f;
        }

        if ((sprite.getPosition().y - sprite.getGlobalBounds().size.y/2) <= margin && pos == 3) 
        {
            pos = 0;
            sprite.rotate(sf::degrees(90));
            xMovement = 0.05f;
            yMovement = 0.0f;
        }

        window.draw(sprite);
        window.display();
    }

    return 0;
}