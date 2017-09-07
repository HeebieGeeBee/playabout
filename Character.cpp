#include "Character.h"
#define WORLD_WIDTH 2560
#define WORLD_HIEGHT 1280

Character::Character(sf::Vector2f pos, sf::Texture* texture, sf::Vector2u imageCount, float switchTime) :
    animation(texture, imageCount, switchTime)
{
    sprite.setSize(sf::Vector2f(100.0f, 120.0f));
    sprite.setOrigin(sprite.getSize() / 2.0f );
    sprite.setPosition(pos);
    sprite.setTexture(texture);
}

Character::~Character()
{
    //dtor
}

void Character::Draw(sf::RenderTarget& window)
{
    window.draw(sprite);
}

void Character:: Update(float deltaTime)
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

sf::Vector2f Character::GetPosition()
    {
        return sprite.getPosition();
    }
sf::Vector2f Character::GetSize()
    {
        return sprite.getSize();
    }
