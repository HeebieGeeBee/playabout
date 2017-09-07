#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;

    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);

}

Animation::~Animation()
{
    //dtor
}

void Animation::Update(float deltaTime, std::string facing, bool moving)
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
            if(moving)
            {
                totalTime += deltaTime;
            }

            if(totalTime >= switchTime && moving)
            {
                totalTime -= switchTime;
                currentImage.x++;

                if(currentImage.x >= imageCount.x)
                {
                    currentImage.x = 1;
                }
            }
            if (!moving)
            {
                currentImage.x = 0;
            }

            uvRect.top = currentImage.y * uvRect.height;
            uvRect.left = currentImage.x * uvRect.width;

        }
