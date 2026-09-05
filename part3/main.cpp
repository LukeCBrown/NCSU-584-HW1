#include <SFML/Graphics.hpp>


   struct MovingSprite
    {
        sf::Sprite sprite;
        int pos;
        float xMovement;
        float yMovement;
    };
    
int main()
{
    sf::RenderWindow window(
        sf::VideoMode({640, 480}),
        "CSC 584 HW1"
    );

    sf::Texture texture;

    if (!texture.loadFromFile("boid-sm.png"))
    {
        return 1;
    }

 

    MovingSprite boid{
        sf::Sprite(texture),
        0,
        0.05f,
        0.0f
    };


    // positions:
    // 0 = right
    // 1 = down
    // 2 = left
    // 3 = up
  

    float margin = 15.0f;

    boid.sprite.setScale({3.f, 3.f});

    auto bounds = boid.sprite.getLocalBounds();

    boid.sprite.setOrigin({
        bounds.size.x / 2.f,
        bounds.size.y / 2.f
    });

    // Start with the entire sprite 15 pixels
    // away from the top and left edges.
    boid.sprite.setPosition({
        margin + boid.sprite.getGlobalBounds().size.x / 2.f,
        margin + boid.sprite.getGlobalBounds().size.y / 2.f
    });

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        // Move using the current direction.
        boid.sprite.move({
            boid.xMovement,
            boid.yMovement
        });


        // Moving RIGHT -> hit top-right corner.
        if (
            boid.sprite.getPosition().x +
            boid.sprite.getGlobalBounds().size.x / 2.f
            >= 640.f - margin
            && boid.pos == 0
        )
        {
            boid.pos = 1;
            boid.sprite.rotate(sf::degrees(90));

            boid.xMovement = 0.0f;
            boid.yMovement = 0.05f;
        }

        // Moving DOWN -> hit bottom-right corner.
        if (
            boid.sprite.getPosition().y +
            boid.sprite.getGlobalBounds().size.y / 2.f
            >= 480.f - margin
            && boid.pos == 1
        )
        {
            boid.pos = 2;
            boid.sprite.rotate(sf::degrees(90));

            boid.xMovement = -0.05f;
            boid.yMovement = 0.0f;
        }

        // Moving LEFT -> hit bottom-left corner.
        if (
            boid.sprite.getPosition().x -
            boid.sprite.getGlobalBounds().size.x / 2.f
            <= margin
            && boid.pos == 2
        )
        {
            boid.pos = 3;
            boid.sprite.rotate(sf::degrees(90));

            boid.xMovement = 0.0f;
            boid.yMovement = -0.05f;
        }

        // Moving UP -> hit top-left corner.
        if (
            boid.sprite.getPosition().y -
            boid.sprite.getGlobalBounds().size.y / 2.f
            <= margin
            && boid.pos == 3
        )
        {
            boid.pos = 0;
            boid.sprite.rotate(sf::degrees(90));

            boid.xMovement = 0.05f;
            boid.yMovement = 0.0f;
        }

        window.clear(sf::Color::White);
        window.draw(boid.sprite);
        window.display();
    }

    return 0;
}