#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    size_t const SIZE = 100; 
    size_t const WIDTH = 4;
    size_t const HEIGHT = 3;

    sf::RenderWindow window(sf::VideoMode(WIDTH*SIZE, HEIGHT*SIZE), "SFML works!");
    sf::RectangleShape shape(sf::Vector2f(SIZE, SIZE));
    sf::Color colors[HEIGHT][WIDTH] = {
        {sf::Color(64,0,0), sf::Color(128,0,0), sf::Color(192,0,0), sf::Color(255,0,0)},
        {sf::Color(0,64,0), sf::Color(0,128,0), sf::Color(0,192,0), sf::Color(0, 255,0)},
        {sf::Color(0,0,64), sf::Color(0,0,128), sf::Color(0,0,192), sf::Color(0,0,255)}
    };

    float x_offset = 0;
    float y_offset = 0;
    float const DX = 10;
    float const DY = 10;

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed1 = clock.getElapsedTime();
        float sec = elapsed1.asSeconds();
        if (sec >= 0.1)
        {
            x_offset -= sf::Keyboard::isKeyPressed(sf::Keyboard::Left) * DX;
            x_offset += sf::Keyboard::isKeyPressed(sf::Keyboard::Right) * DX;
            y_offset += sf::Keyboard::isKeyPressed(sf::Keyboard::Down) * DY;
            y_offset -= sf::Keyboard::isKeyPressed(sf::Keyboard::Up) * DY;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                int l_x = localPosition.x - x_offset;
                int l_y = localPosition.y - y_offset;
                if (l_y >= 0 && l_y < HEIGHT*SIZE && 
                    l_x >= 0 && l_x < WIDTH*SIZE)
                {
                    int row = l_y/SIZE;
                    int col = l_x/SIZE;
                    colors[row][col] = sf::Color::Black;
                }
            }
            clock.restart();
        }

        window.clear();
        for (int row = 0; row < HEIGHT; ++row)
            for (int col = 0; col < WIDTH; ++col)
            {
                shape.setFillColor(colors[row][col]);
                shape.setPosition(col*SIZE + x_offset, row*SIZE + y_offset);
                window.draw(shape);
            }
        window.display();
    }
    return 0;
}

