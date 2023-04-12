#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <random>

#define SCREEN_HEIGHT 1440
#define SCREEN_WIDTH 2560
#define NO_OF_SPACE_OBJECTS 3
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
    float x_velocity, y_velocity, x_acceleration, y_acceleration;

public:
    sf::CircleShape shape;
    float x_force, y_force, x_position, y_position, mass;

    space_object()
    {
        shape.setFillColor(sf::Color::White);
        shape.setRadius(10);
        x_position = random_int(0, SCREEN_WIDTH);
        y_position = random_int(0, SCREEN_HEIGHT);
        x_force = 0;
        x_acceleration = 0;
        x_velocity = 0;
        y_force = 0;
        y_acceleration = 0;
        y_velocity = 0;
        shape.setPosition(x_position, y_position);
        mass = 1;
    }

    void update_acceleration()
    {
        x_acceleration = x_force / mass;
        y_acceleration = y_force / mass;
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
            disp_x = space_objects[j].x_position - space_objects[i].x_position;
            if (disp_x > 1 || disp_x < -1)
            {
                space_objects[i].x_force = space_objects[i].x_force + (GRAVITY_CONSTANT * (absolute_value(disp_x) * (1 / (disp_x * disp_x))));
            }
            else
            {
                space_objects[i].x_force = 0;
            }

            disp_y = space_objects[j].y_position - space_objects[i].y_position;
            if (disp_y > 1 || disp_y < -1)
            {
                space_objects[i].y_force = space_objects[i].y_force + (GRAVITY_CONSTANT * (absolute_value(disp_y) * (1 / (disp_y * disp_y))));
            }
            else
            {
                space_objects[i].y_force = 0;
            }
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
