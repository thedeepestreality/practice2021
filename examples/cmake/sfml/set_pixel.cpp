#include <SFML/Graphics.hpp>
#include <ctime>

int main(){
	size_t const WIDTH = 640;
	size_t const HEIGHT = 480;
    // Create main window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML Graphics");
	sf::RectangleShape pixel(sf::Vector2f(1, 1));
	// Random seed
	srand(time(nullptr));
	int randX, randY;
	int r, g, b;
	window.clear();
    // Start game loop
    while (window.isOpen()){
        // Process events
        sf::Event Event;
        while (window.pollEvent(Event)){
            // Close window : exit
            if (Event.type == sf::Event::Closed)
                window.close();
        }
		
		for (int row = 0; row < HEIGHT; ++row)
            for (int col = 0; col < WIDTH; ++col)
            {
                pixel.setFillColor(sf::Color(rand()%255, rand()%255, rand()%255));
                pixel.setPosition(col, row);
                window.draw(pixel);
            }
        // Finally, display the rendered frame on screen
        window.display();
    }

    return EXIT_SUCCESS;
}