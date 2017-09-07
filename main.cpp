#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cctype>
#include "TileMap.h"
#include "Animation.h"
#include "Character.h"

#define WINDOW_WIDTH 1240
#define WINDOW_HIEGHT 720
#define WORLD_WIDTH 2560
#define WORLD_HIEGHT 1280


int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(WINDOW_WIDTH, WINDOW_HIEGHT), "SFML window", sf::Style::Default, settings);
    app.setVerticalSyncEnabled(true);
    // Declare deltaTime
    float deltaTime = 0.0f;
    sf::Clock clock;
    // Create new Character knight
    sf::Texture knightTexture;
    if (!knightTexture.loadFromFile("BODY_male_Epic_armors_Golden.png"))
    {
        return EXIT_FAILURE;
    }

    Character knight({500.0f, 400.0f},  &knightTexture, {9, 4}, 0.1f);


    sf::View view({0,0}, sf::Vector2f(WINDOW_WIDTH,WINDOW_HIEGHT));

    const int level[] =
    {
        22, 15, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    };

    TileMap map;
    if (!map.load("tiles.png", sf::Vector2u(32, 32), level, 16, 8))
        return -1;

    map.scale(5,5);

	// Start the game loop
    while (app.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        // Update the knight
        knight.Update(deltaTime);
        // Set view center
        view.setCenter(knight.GetPosition());
        // Clear screen
        app.clear();
        // Draw map
        app.draw(map);
        // Draw knight
        knight.Draw(app);
        // Set view
        app.setView(view);
        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
