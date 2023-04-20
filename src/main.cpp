#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <cmath>

#define SCREEN_HEIGHT 1440
#define SCREEN_WIDTH 2560
#define NO_OF_SPACE_OBJECTS 500
#define GRAVITY_CONSTANT 0.5
#define PI 3.141592

/* funtion breaks when you enter a fraction as any of the parameters*/
float simple_exponent(float base, int exponenet)
{
    if (exponenet < 1)
        return 1;
    else
        return base * simple_exponent(base, exponenet - 1);
}

/*Converts degrees to radians*/
float degrees_to_radians(float degree)
{
    float radian;
    radian = degree * (PI / 180);
    return radian;
}

/*Returns a random integer ,upper and lower bound included*/
int random_int(int lower_bound, int upper_bound)
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(lower_bound, upper_bound);
    return dist(rd);
}

/*Returns a random float value , upper and lower bound included*/
float random_float(float lower_bound, float upper_bound)
{
    std::random_device rd;
    std::uniform_real_distribution<float> dist(lower_bound, upper_bound);
    return dist(rd);
}

/*Returns an absolute value of a program*/
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
    float velocity[2];

public:
    sf::CircleShape shape;
    float force[2], position[2], mass, acceleration[2];
    bool fixed_pos;

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
        fixed_pos = false;
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
            velocity[i] += (acceleration[i] * time_step);
    }
    void update_position(float time_step)
    {
        int i;
        for (i = 0; i < 2; i++)
            position[i] += (velocity[i] * time_step);

        // tp_particle_back_to_screen();
        shape.setPosition(position[0], position[1]);
    }

    void tp_particle_back_to_screen()
    {
        if (position[0] > SCREEN_WIDTH)
            position[0] = position[0] - SCREEN_WIDTH;

        if (position[0] < 0)
            position[0] = SCREEN_WIDTH - position[0];

        if (position[1] > SCREEN_HEIGHT)
            position[1] = position[1] - SCREEN_HEIGHT;

        if (position[1] < 0)
            position[1] = SCREEN_HEIGHT - position[1];
    }

    void set_position(float x, float y)
    {
        position[0] = x;
        position[1] = y;
        shape.setPosition(position[0], position[1]);
    }
    void set_position(double x, double y)
    {
        position[0] = x;
        position[1] = y;
        shape.setPosition(position[0], position[1]);
    }
    void set_position(int x, int y)
    {
        position[0] = x;
        position[1] = y;
        shape.setPosition(position[0], position[1]);
    }

    void set_velocity(float x, float y)
    {
        velocity[0] = x;
        velocity[1] = y;
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
    float magnitude_squared, magnitude;
    for (i = 0; i < no_of_space_objects; i++)
    {
        if (space_objects[i].mass == 0)
            continue;
        for (j = 0; j < 2; j++)
        {
            space_objects[i].force[j] = 0;
        }
        for (j = 0; j < no_of_space_objects; j++)
        {
            if (j == i)
                continue;
            if (space_objects[j].mass == 0)
                continue;
            magnitude_squared = (simple_exponent((space_objects[j].position[0] - space_objects[i].position[0]), 2)) +
                                (simple_exponent((space_objects[j].position[1] - space_objects[i].position[1]), 2));
            if (magnitude_squared < space_objects[i].shape.getRadius())
            {
                continue;
            }
            magnitude = sqrt(magnitude_squared);
            space_objects[i].force[0] += (GRAVITY_CONSTANT * space_objects[i].mass * space_objects[j].mass * (space_objects[j].position[0] - space_objects[i].position[0])) / simple_exponent(magnitude, 3);
            space_objects[i].force[1] += (GRAVITY_CONSTANT * space_objects[i].mass * space_objects[j].mass * (space_objects[j].position[1] - space_objects[i].position[1])) / simple_exponent(magnitude, 3);
        }
    }
}

void update(space_object space_objects[], int no_of_space_objects, float delta_time)
{

    int i, j;
    update_force(space_objects, no_of_space_objects);
    for (i = 0; i < no_of_space_objects; i++)
    {
        space_objects[i].update_acceleration();
        space_objects[i].update_velocity(delta_time);
        if (space_objects[i].fixed_pos == true)
            continue;
        space_objects[i].update_position(delta_time);
    }
}
int main()
{
    space_object space_objects[NO_OF_SPACE_OBJECTS];
    sf::Clock dtclock;
    float dt;

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

        dt = dtclock.restart().asSeconds();

        window.clear();

        // Update here
        update(space_objects, NO_OF_SPACE_OBJECTS, dt * 100);

        // render here
        draw_objects(windowptr, space_objects, NO_OF_SPACE_OBJECTS);
        window.display();
    }
    return 0;
}
