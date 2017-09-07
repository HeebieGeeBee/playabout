#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Animation.h"

class Character
{
    public:
        Character(sf::Vector2f pos, sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
        virtual ~Character();

        void Draw(sf::RenderTarget& window);

        void Update(float deltaTime);

        sf::Vector2f GetPosition();

        sf::Vector2f GetSize();


    protected:

    private:
        static constexpr float speed = 100.f;
        sf::RectangleShape sprite;
        sf::Vector2f dir = {0.0f, 0.0f};
        std::string facing = "DOWN";
        Animation animation;
        bool moving = false;
};

#endif // CHARACTER_H
