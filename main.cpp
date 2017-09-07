#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#define WINDOW_WIDTH 800
#define WINDOW_HIEGHT 600
#define WORLD_WIDTH 1980
#define WORLD_HIEGHT 1080

class Animation
{
    public:
        Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
        {
            this->imageCount = imageCount;
            this->switchTime = switchTime;
            totalTime = 0.0f;
            currentImage.x = 0;

            uvRect.width = texture->getSize().x / float(imageCount.x);
            uvRect.height = texture->getSize().y / float(imageCount.y);
        }
        virtual ~Animation()
        {

        }

        void Update(float deltaTime, std::string facing, bool moving)
        {
            int row;
            if (facing == "UP")
            {
                row = 0;
            }
            if (facing == "DOWN")
            {
                row = 2;
            }
            if (facing == "LEFT")
            {
                row = 1;
            }
            if (facing == "RIGHT")
            {
                row = 3;
            }
            currentImage.y = row;
            totalTime += deltaTime;

            if(totalTime >= switchTime && moving)
            {
                totalTime -= switchTime;
                currentImage.x++;

                if(currentImage.x >= imageCount.x)
                {
                    currentImage.x = 2;
                }
            }
            if (!moving)
            {
                currentImage.x = 0;
            }

            uvRect.top = currentImage.y * uvRect.height;
            uvRect.left = currentImage.x * uvRect.width;

        }

        sf::IntRect uvRect;

    private:
        sf::Vector2u imageCount;
        sf::Vector2u currentImage;

        float totalTime;
        float switchTime;


};

class Character
{
public:
    Character(sf::Vector2f pos, sf::Texture* texture, sf::Vector2u imageCount, float switchTime) :
        animation(texture, imageCount, switchTime)
    {
        position = pos;
        sprite.setSize(sf::Vector2f(100.0f, 120.0f));
        sprite.setOrigin(sprite.getSize() / 2.0f );
        sprite.setPosition(pos);
        sprite.setTexture(texture);


    }
    void Draw(sf::RenderTarget& window)
    {
        window.draw(sprite);
    }
    void Update(float deltaTime)
    {
        dir = {0.0f, 0.0f};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sprite.getPosition().y - (sprite.getSize().y / 2) > 0)
        {
            dir.y -= speed * deltaTime;
            facing = "UP";
            moving = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sprite.getPosition().y + (sprite.getSize().y / 2) < WORLD_HIEGHT)
        {
            dir.y += speed * deltaTime;
            facing = "DOWN";
            moving = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sprite.getPosition().x - (sprite.getSize().x / 2) > 0)
        {
            dir.x -= speed * deltaTime;
            facing = "LEFT";
            moving = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sprite.getPosition().x + (sprite.getSize().x / 2)  < WORLD_WIDTH)
        {
            dir.x += speed * deltaTime;
            facing = "RIGHT";
            moving = true;
        }
        else
        {
            moving = false;
        }
        sprite.setTextureRect(animation.uvRect);
        animation.Update(deltaTime, facing, moving);
        sprite.move(dir);

    }
    sf::Vector2f GetPosition()
    {
        return sprite.getPosition();
    }
    sf::Vector2f GetSize()
    {
        return sprite.getSize();
    }
private:

    static constexpr float speed = 100.f;
    sf::Vector2f position;
    sf::Vector2f velocity = {0.0f, 0.0f};
    sf::RectangleShape sprite;
    sf::Vector2f textureSize;
    sf::Vector2f dir = {0.0f, 0.0f};
    std::string facing = "DOWN";
    Animation animation;
    bool moving = false;


};


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
    knightTexture.loadFromFile( "BODY_male_Epic_armors_Golden.png");
    knightTexture.setSmooth(true);

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile( "free-wallpaper-33.jpg" );
    sf::RectangleShape background({WORLD_WIDTH, WORLD_HIEGHT});
    background.setTexture(&backgroundTexture);
    Character knight({500.0f, 400.0f}, &knightTexture, {9, 4}, 0.1f);

    sf::CircleShape triangle(30, 3);
    triangle.setPosition(100.0f, 100.0f);
    triangle.setOrigin(triangle.getRadius(), triangle.getRadius() );

    sf::View view({0,0}, sf::Vector2f(WINDOW_WIDTH,WINDOW_HIEGHT));

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

        triangle.rotate(100.0f * deltaTime);


        // Update the knight
        knight.Update(deltaTime);
        view.setCenter(knight.GetPosition().x - (knight.GetSize().x / 2) <= WINDOW_WIDTH/2 ? WINDOW_WIDTH/2 + (knight.GetSize().x / 2) : knight.GetPosition().x ||
                       knight.GetPosition().x + (knight.GetSize().x / 2) >= WORLD_WIDTH - (WINDOW_WIDTH/2) ? WINDOW_WIDTH/2 - (knight.GetSize().x / 2) : knight.GetPosition().x , knight.GetPosition().y);
        // Clear screen
        app.clear();

        // Draw the knight
        app.draw(background);
        knight.Draw(app);
        app.draw(triangle);
        app.setView(view);
        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
