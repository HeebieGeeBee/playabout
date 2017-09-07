#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cctype>

#define WINDOW_WIDTH 800
#define WINDOW_HIEGHT 600
#define WORLD_WIDTH 2560
#define WORLD_HIEGHT 1280

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
    {
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // get the current tile number
                int tileNumber = tiles[i + j * width];

                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }

        return true;
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

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
        // Setting up keyboard controls
        dir = {0.0f, 0.0f};
        // Up Left Diagonal
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
            sprite.getPosition().y - (sprite.getSize().y / 2) > 0 &&
            sprite.getPosition().x - (sprite.getSize().x / 2) > 0)
        {
            dir.x -= speed * deltaTime;
            dir.y -= speed * deltaTime;
            facing = "LEFT";
            moving = true;
        }
        // Up Right Diagonal
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
                 sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
                 sprite.getPosition().y - (sprite.getSize().y / 2) > 0 &&
                 sprite.getPosition().x + (sprite.getSize().x / 2)  < WORLD_WIDTH)
        {
            dir.x += speed * deltaTime;
            dir.y -= speed * deltaTime;
            facing = "RIGHT";
            moving = true;
        }
        // Down Left Diagonal
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
                 sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
                 sprite.getPosition().y + (sprite.getSize().y / 2) < WORLD_HIEGHT &&
                 sprite.getPosition().x - (sprite.getSize().x / 2) > 0)
        {
            dir.x -= speed * deltaTime;
            dir.y += speed * deltaTime;
            facing = "LEFT";
            moving = true;
        }
        // Down Right Diagonal
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
                 sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
                 sprite.getPosition().y + (sprite.getSize().y / 2) < WORLD_HIEGHT &&
                 sprite.getPosition().x + (sprite.getSize().x / 2)  < WORLD_WIDTH)
        {
            dir.x += speed * deltaTime;
            dir.y += speed * deltaTime;
            facing = "RIGHT";
            moving = true;
        }
        // Up
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
                 sprite.getPosition().y - (sprite.getSize().y / 2) > 0)
        {
            dir.y -= speed * deltaTime;
            facing = "UP";
            moving = true;
        }
        // Down
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
                 sprite.getPosition().y + (sprite.getSize().y / 2) < WORLD_HIEGHT)
        {
            dir.y += speed * deltaTime;
            facing = "DOWN";
            moving = true;
        }
        // Left
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
                 sprite.getPosition().x - (sprite.getSize().x / 2) > 0)
        {
            dir.x -= speed * deltaTime;
            facing = "LEFT";
            moving = true;
        }
        // Right
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
                 sprite.getPosition().x + (sprite.getSize().x / 2)  < WORLD_WIDTH)
        {
            dir.x += speed * deltaTime;
            facing = "RIGHT";
            moving = true;
        }
        // Not Moving
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
    sf::RectangleShape sprite;
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

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile( "free-wallpaper-33.jpg" );
    sf::RectangleShape background({WORLD_WIDTH, WORLD_HIEGHT});
    background.setTexture(&backgroundTexture);

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
        view.setCenter(knight.GetPosition());
        // Clear screen
        app.clear();
        // Draw the knight
        app.draw(background);

        app.draw(map);

        knight.Draw(app);
        app.setView(view);
        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
