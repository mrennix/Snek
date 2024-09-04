#pragma once

#include "Board.h"

class Snake
{
public:
    Snake(const Location& loc);
    void MoveBy(const Location& delta_loc);
    Location GetNextHeadLocation(const Location& delta_loc) const;
    void Grow();
    void Draw(Board& brd) const;
    bool isInTileExceptEnd(const Location& target) const;
    bool isInTile(const Location& target) const;
    int getSnakeSize() const;
    

private:
    class Segment
    {
    public:
        void InitHead(const Location& loc);
        void InitBody();
        void Follow(const Segment& next);
        void MoveBy(const Location& delta_loc);
        void Draw(Board& brd) const;
        const Location& GetLocation() const;
    private:
        Location loc;
        Color c;
    };

private:
    static constexpr Color headColor = Colors::Green;
    //static constexpr Color bodyColor = Colors::Green;
    static constexpr int nSegmentsMax = 50;
    Segment segments[nSegmentsMax];
    int nSegments = 1;
    static constexpr int nBodyColoursMax = 3;
    inline static Color bodyColours[nBodyColoursMax];
    inline static int colCycle = 0;
};
