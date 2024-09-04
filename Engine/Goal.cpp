#include "Goal.h"
#include "Enemy.h"

Goal::Goal(std::mt19937& rng, const Board& brd, const Snake& snake, const std::vector<Enemy>& enemies)
{
    Respawn(rng, brd, snake, enemies);
}

void Goal::Respawn(std::mt19937& rng, const Board& brd, const Snake& snake, const std::vector<Enemy>& enemies)
{
    std::uniform_int_distribution<int> xDist(1, brd.GetWidth() - 1);
    std::uniform_int_distribution<int> yDist(1, brd.GetHeight() - 1);
    
    Location newLoc;
    do
    {
        newLoc.x = xDist(rng);
        newLoc.y = yDist(rng);
    } while (snake.isInTile(newLoc) || isInTile(newLoc, enemies));

    loc = newLoc;
}

void Goal::Draw(Board& brd)
{
    if (isPulser)
    {
        colourCycle += colourCycleDirection * 10;
        if (colourCycle == 50 || colourCycle == maxRGB)
        {
            colourCycleDirection *= -1;
            colourCycle += colourCycleDirection * 10;
        }
        colourCycle %= maxRGB;

        color = Colors::MakeRGB(colourCycle, 0, 0);
    }
    brd.DrawCell(loc, color);
}

bool Goal::isInTile(const Location& target, const std::vector<Enemy>& enemies) const
{
    for (const auto& enemy : enemies)
    {
        if (enemy.GetLocation() == target)
        {
            return true;
        }
    }
    return false;
}
