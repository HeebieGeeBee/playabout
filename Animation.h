#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Animation
{
    public:
        Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
        virtual ~Animation();

        void Update(float deltaTime, std::string facing, bool moving);

        sf::IntRect uvRect;

    protected:

    private:
        sf::Vector2u imageCount;
        sf::Vector2u currentImage;

        float totalTime;
        float switchTime;
};


#endif // ANIMATION_H
