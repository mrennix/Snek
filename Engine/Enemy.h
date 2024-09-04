#pragma once

#include <random>
#include "Board.h"
#include "Snake.h"
#include "Location.h"
#include <vector>

class Enemy
{
public:
    Enemy(std::mt19937& rng, const Board& brd, const Snake& snake, const std::vector<Enemy>& enemies);
    void Spawn(std::mt19937& rng, const Board& brd, const Snake& snake, const std::vector<Enemy>& enemies);
    void Draw(Board& brd) const;
    const Location& GetLocation() const { return loc; }
    bool isInTile(const Location& target, const std::vector<Enemy>& enemies) const;

private:
    static constexpr Color c = Colors::Gray;
    Location loc;
   
};
