#pragma once

#include <random>
#include "Board.h"
#include "Snake.h"
#include "Location.h"
#include "Enemy.h"
#include <vector>

class Goal
{
public:
    Goal(std::mt19937& rng, const Board& brd, const Snake& snake, const std::vector<Enemy>& enemies);
    void Respawn(std::mt19937& rng, const Board& brd, const Snake& snake, const std::vector<Enemy>& enemies);
    void Draw(Board& brd);
    const Location& GetLocation() const { return loc; }
    bool isInTile(const Location& target, const std::vector<Enemy>& enemies) const;

private:
    // static constexpr Color c = Colors::Red;
    Location loc;
    bool isPulser = true;
    int maxRGB = 250;
    int colourCycle = 250;
    int colourCycleDirection = -1;
    Color color = Colors::Red;
};
