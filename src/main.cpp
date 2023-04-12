#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <random>

#define SCREEN_HEIGHT 1440
#define SCREEN_WIDTH 2560
#define NO_OF_SPACE_OBJECTS 100
#define GRAVITY_CONSTANT 1

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
    float velocity[2], acceleration[2];

public:
    sf::CircleShape shape;
    float force[2], position[2], mass;

    space_object()
    {
        shape.setFillColor(sf::Color::White);
        shape.setRadius(10);
        position[0] = random_int(0, SCREEN_WIDTH);
        position[1] = random_int(0, SCREEN_HEIGHT);
        velocity[0] = 0;
        velocity[1] = 0;
        force[0] = 0;
        force[1] = 0;
        acceleration[0] = 0;
        acceleration[1] = 0;
        shape.setPosition(position[0], position[1]);
        mass = 1;
    }

    void update_acceleration()
    {
        int i;
        for (i = 0; i < 2; i++)
            acceleration[i] = force[i] / mass;
    }

    void update_velocity(float time_step)
    {
        int i;
        for (i = 0; i < 2; i++)
            velocity[i] = velocity[i] + (acceleration[i] * time_step);
    }
    void update_position(float time_step)
    {
        int i;
        for (i = 0; i < 2; i++)
            position[i] = position[i] + (velocity[i] * time_step);

        if (position[0] > SCREEN_WIDTH)
            position[0] = position[0] - SCREEN_WIDTH;

        if (position[0] < 0)
            position[0] = SCREEN_WIDTH - position[0];

        if (position[1] > SCREEN_HEIGHT)
            position[1] = position[1] - SCREEN_HEIGHT;

        if (position[1] < 0)
            position[1] = SCREEN_HEIGHT - position[1];
        shape.setPosition(position[0], position[1]);
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

void update_force(space_object space_objects[], int no_of_space_objects)
{
    int i, j;
    float disp_x, disp_y;
    for (i = 0; i < no_of_space_objects; i++)
    {
        for (j = 0; j < no_of_space_objects; j++)
        {
            if (j == i)
                continue;
                }
    }
}

void update(space_object space_objects[], int no_of_space_objects)
{
    int i, j;
    update_force(space_objects, no_of_space_objects);
    for (i = 0; i < no_of_space_objects; i++)
    {
        space_objects[i].update_acceleration();
        space_objects[i].update_velocity(0.01);
        space_objects[i].update_position(0.01);
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
