#include "Enemy.h"

Enemy::Enemy(std::mt19937& rng, const Board& brd, const Snake& snake, const std::vector<Enemy>& enemies)
{
    Spawn(rng, brd, snake, enemies);
}

void Enemy::Spawn(std::mt19937& rng, const Board& brd, const Snake& snake, const std::vector<Enemy>& enemies)
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

void Enemy::Draw(Board& brd) const
{

    brd.DrawCell(loc, c);
}

bool Enemy::isInTile(const Location& target, const std::vector<Enemy>& enemies) const
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
