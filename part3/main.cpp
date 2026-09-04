#include <SFML/Graphics.hpp>

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

    sf::Sprite sprite(texture);

    float xMovement = 0.05f;
    float yMovement = 0.0f;

    // positions:
    // 0 = right
    // 1 = down
    // 2 = left
    // 3 = up
    int pos = 0;

    float margin = 15.0f;

    sprite.setScale({3.f, 3.f});

    auto bounds = sprite.getLocalBounds();

    sprite.setOrigin({
        bounds.size.x / 2.f,
        bounds.size.y / 2.f
    });

    // Start with the entire sprite 15 pixels
    // away from the top and left edges.
    sprite.setPosition({
        margin + sprite.getGlobalBounds().size.x / 2.f,
        margin + sprite.getGlobalBounds().size.y / 2.f
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
        sprite.move({xMovement, yMovement});

        // Moving RIGHT -> hit top-right corner.
        if (
            sprite.getPosition().x +
            sprite.getGlobalBounds().size.x / 2.f
            >= 640.f - margin
            && pos == 0
        )
        {
            pos = 1;
            sprite.rotate(sf::degrees(90));

            xMovement = 0.0f;
            yMovement = 0.05f;
        }

        // Moving DOWN -> hit bottom-right corner.
        if (
            sprite.getPosition().y +
            sprite.getGlobalBounds().size.y / 2.f
            >= 480.f - margin
            && pos == 1
        )
        {
            pos = 2;
            sprite.rotate(sf::degrees(90));

            xMovement = -0.05f;
            yMovement = 0.0f;
        }

        // Moving LEFT -> hit bottom-left corner.
        if (
            sprite.getPosition().x -
            sprite.getGlobalBounds().size.x / 2.f
            <= margin
            && pos == 2
        )
        {
            pos = 3;
            sprite.rotate(sf::degrees(90));

            xMovement = 0.0f;
            yMovement = -0.05f;
        }

        // Moving UP -> hit top-left corner.
        if (
            sprite.getPosition().y -
            sprite.getGlobalBounds().size.y / 2.f
            <= margin
            && pos == 3
        )
        {
            pos = 0;
            sprite.rotate(sf::degrees(90));

            xMovement = 0.05f;
            yMovement = 0.0f;
        }

        window.clear(sf::Color::White);
        window.draw(sprite);
        window.display();
    }

    return 0;
}