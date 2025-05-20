#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include "CustomSprite.h"


int main()
{

    sf::RenderWindow window(sf::VideoMode(1280, 720), "My window");
    sf::Clock clock;
    srand(time(0));
    window.setFramerateLimit(144);
    sf::Texture guy_tex;
    if (!guy_tex.loadFromFile("guy.png")) {
		std::cout << "Error loading guy texture" << std::endl;
		return -1;
    }
    sf::Texture grass_tex;
    if (!grass_tex.loadFromFile("grass.png")) {
		std::cout << "Error loading grass texture" << std::endl;
        return -1;
    }
    sf::Texture wall_tex;
    if (!wall_tex.loadFromFile("wall.png")) {
		std::cout << "Error loading wall texture" << std::endl;
		return -1;
    }
	wall_tex.setRepeated(true);
    CustomSprite guy;
	guy.setTexture(guy_tex);
    sf::Sprite grass;
	grass.setTexture(grass_tex);
	grass.setTextureRect(sf::IntRect(0, 0, 1280, 720));
	grass_tex.setRepeated(true);
    std::vector<sf::Sprite> walls;
    int number_of_walls = 10;
    for (int i = 0; i < number_of_walls; i++) {
        sf::Sprite wall;
        wall.setTexture(wall_tex);
        wall.setPosition(rand() % 1000 + 100, rand() % 600);
        wall.setScale(0.4, 0.4);
        wall.setTextureRect(sf::IntRect(0, 0, 120, (rand() % 400) + 100));
        walls.emplace_back(wall);
    };
    guy.setPosition(30, 200);
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        guy.setBounds(0, window.getSize().x, 0, window.getSize().y);
        guy.moveInDirection(elapsed, walls);

        window.clear(sf::Color::Black);
        window.draw(grass);
        window.draw(guy);

        for (auto& wall : walls) {
            window.draw(wall);
        }

        window.display();
    }

    return 0;
}
