#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <random>

#define SCREEN_HEIGHT 1440
#define SCREEN_WIDTH 2560
#define NO_OF_SPACE_OBJECTS 5500
int random_int(int lower_bound, int upper_bound)
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(lower_bound, upper_bound);
    return dist(rd);
}

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

    void first_init(int id)
    {
        identity = id;
        shape.setPosition(random_int(0, SCREEN_WIDTH), random_int(0, SCREEN_HEIGHT));
    }

    void update_pos(int x, int y)
    {
        shape.setPosition(x, y);
    }
};

void draw_objects(sf::RenderWindow *windowptr, space_object object_array[], int size_of_array)
{
    int i;
    for (i = 0; i < size_of_array; i++)
    {
        windowptr->draw(object_array[i].shape);
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
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game engine");
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
