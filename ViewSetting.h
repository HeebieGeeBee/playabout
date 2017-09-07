#include "Globals.h"

sf::Vector2f ViewSetting(Character knight)
{
    if (knight.GetPosition().x - (knight.GetSize().x/2 ) <= WINDOW_WIDTH / 2 - (knight.GetSize().x/2))
    {
        if (knight.GetPosition().y <= WINDOW_HIEGHT /2)
        {
            return sf::Vector2f(WINDOW_WIDTH/2, WINDOW_HIEGHT/2);
        }
        else if (knight.GetPosition().y + (knight.GetSize().y/2) >= WORLD_HIEGHT - (WINDOW_HIEGHT/2) + (knight.GetSize().y/2) )
        {
            return sf::Vector2f(WINDOW_WIDTH/2, WORLD_HIEGHT - (WINDOW_HIEGHT/2) );
        }
        else
        {
            return sf::Vector2f(WINDOW_WIDTH/2, knight.GetPosition().y);
        }
    }
    if (knight.GetPosition().x + (knight.GetSize().x/2 ) >= WORLD_WIDTH - (WINDOW_WIDTH/2) + (knight.GetSize().x/2))
    {
        if (knight.GetPosition().y <= WINDOW_HIEGHT /2)
        {
            return sf::Vector2f(WORLD_WIDTH - (WINDOW_WIDTH/2), WINDOW_HIEGHT/2);
        }
        else if (knight.GetPosition().y + (knight.GetSize().y/2) >= WORLD_HIEGHT - (WINDOW_HIEGHT/2) + (knight.GetSize().y/2) )
        {
            return sf::Vector2f(WORLD_WIDTH - (WINDOW_WIDTH/2), WORLD_HIEGHT - (WINDOW_HIEGHT/2) );
        }
        else
        {
            return sf::Vector2f(WORLD_WIDTH - (WINDOW_WIDTH/2), knight.GetPosition().y);
        }
    }
    if (knight.GetPosition().y <= WINDOW_HIEGHT /2)
    {
        return sf::Vector2f(knight.GetPosition().x, WINDOW_HIEGHT/2);
    }
    if (knight.GetPosition().y + (knight.GetSize().y/2) >= WORLD_HIEGHT - (WINDOW_HIEGHT/2) + (knight.GetSize().y/2))
    {
        return sf::Vector2f(knight.GetPosition().x, WORLD_HIEGHT - (WINDOW_HIEGHT/2));
    }

    else
    {
        return knight.GetPosition();
    }
}
