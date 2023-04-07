#include <iostream>
#include <SFML/Graphics.hpp>

#define SCREEN_HEIGHT 2560
#define SCREEN_WIDTH 1440
#define NO_OF_SPACE_OBJECTS 100

class space_object
{
public:
    int identity;
    sf::CircleShape shape;

    space_object()
    {
        shape.setFillColor(sf::Color::White);
        shape.setRadius(1.f);
    }

private:
    int x, y;

public:
    void first_init(int id)
    {
        identity = id;
        x = identity;
        y = identity;
        shape.setPosition(x, y);
    }
};

int main()
{
    space_object space_objects[NO_OF_SPACE_OBJECTS];
    sf::RenderWindow window(sf::VideoMode(SCREEN_HEIGHT, SCREEN_WIDTH), "Game engine");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.display();
    }
    return 0;
}
