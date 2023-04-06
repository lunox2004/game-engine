
#include <SFML/Graphics.hpp>

class testshape
{
public:
    int x, y;
    testshape()
    {
        x = 0;
        y = 0;
    }
};

int main()
{
    float a = 1;
    sf::RenderWindow window(sf::VideoMode(2560, 1440), "Game engine");

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
