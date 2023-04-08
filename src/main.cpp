#include <iostream>
#include <SFML/Graphics.hpp>

#define SCREEN_HEIGHT 2560
#define SCREEN_WIDTH 1440
#define NO_OF_SPACE_OBJECTS 1000

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

void draw_objects(sf::RenderWindow *window, space_object object_array[], int size_of_array)
{
    int i;
    for (i = 0; i < size_of_array; i++)
    {
        window->draw(object_array[i].shape);
    }
}

int main()
{
    int i;
    space_object space_objects[NO_OF_SPACE_OBJECTS];
    for (i = 0; i < NO_OF_SPACE_OBJECTS; i++)
    {
        space_objects[i].first_init(i);
    }
    sf::RenderWindow window(sf::VideoMode(SCREEN_HEIGHT, SCREEN_WIDTH), "Game engine");
    sf::RenderWindow *windowptr = &window;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        draw_objects(windowptr, space_objects, NO_OF_SPACE_OBJECTS);
        window.display();
    }
    return 0;
}
