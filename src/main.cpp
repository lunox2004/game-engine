#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <random>

#define SCREEN_HEIGHT 1440
#define SCREEN_WIDTH 2560
#define NO_OF_SPACE_OBJECTS 5000

int random_int(int lower_bound, int upper_bound)
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(lower_bound, upper_bound);
    return dist(rd);
}

float random_float(float lower_bound, float upper_bound)
{
    std::random_device rd;
    std::uniform_real_distribution<float> dist(lower_bound, upper_bound);
    return dist(rd);
}

int absolute_value(float value)
{
    if (value > 0)
        return 1;
    else if (value < 0)
        return -1;
    else
        return 0;
}

class space_object
{
private:
    float x_velocity, y_velocity, x_acceleration, y_acceleration, x_force, y_force, x_position, y_position;

public:
    sf::CircleShape shape;

    space_object()
    {
        shape.setFillColor(sf::Color::White);
        shape.setRadius(1.f);
        x_position = random_int(0, SCREEN_WIDTH);
        y_position = random_int(0, SCREEN_HEIGHT);
        x_force = 0;
        x_acceleration = 0;
        x_velocity = 0;
        y_force = 0;
        y_acceleration = 0;
        y_velocity = 0;
        shape.setPosition(x_position, y_position);
    }

    void update_velocity(float time_step)
    {
        x_velocity = x_velocity + (x_acceleration * time_step);
        y_velocity = y_velocity + (y_acceleration * time_step);
    }
    void update_position(float time_step)
    {
        x_position = x_position + (x_velocity * time_step);
        y_position = y_position + (y_velocity * time_step);

        if (x_position > SCREEN_WIDTH)
            x_position = x_position - SCREEN_WIDTH;

        if (x_position < 0)
            x_position = SCREEN_WIDTH - x_position;

        if (y_position > SCREEN_HEIGHT)
            y_position = y_position - SCREEN_HEIGHT;

        if (y_position < 0)
            y_position = SCREEN_HEIGHT - y_position;
        shape.setPosition(x_position, y_position);
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

void update(space_object space_objects[], int no_of_space_objects)
{
    int i, j;
    for (i = 0; i < no_of_space_objects; i++)
    {
        space_objects[i].update_velocity(0);
        space_objects[i].update_position(0);
    }
}

int main()
{
    int i;
    space_object space_objects[NO_OF_SPACE_OBJECTS];
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

        // Update here
        update(space_objects, NO_OF_SPACE_OBJECTS);

        // render here
        draw_objects(windowptr, space_objects, NO_OF_SPACE_OBJECTS);
        window.display();
    }
    return 0;
}
