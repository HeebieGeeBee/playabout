#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cctype>
#include "TileMap.h"
#include "Animation.h"
#include "Character.h"
#include "ViewSetting.h"
#include "Globals.h"
#include "Maps.h"

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



    TileMap map;
    if (!map.load("tiles.png", sf::Vector2u(16, 16), world1, 100, 100))
        return -1;

    map.scale(2,2);

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
        // Set view
        // Set view center

        view.setCenter(ViewSetting(knight));
        // Clear screen
        app.clear();
        // Draw map
        app.draw(map);
        // Draw knight
        knight.Draw(app);

        app.setView(view);

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}


