#include "Board.h"
#include <cassert>

Board::Board(Graphics& gfx) : gfx(gfx)
{
}

void Board::DrawCell(const Location& loc, const Color c)
{
    assert(loc.x >= 0);
    assert(loc.x < width);
    assert(loc.y >= 0);
    assert(loc.y < height);
    const int x1 = loc.x * dimension;
    const int y1 = loc.y * dimension;
    gfx.DrawRectDim(x1, y1, dimension, dimension, c);
    for (int x = x1; x < x1 + dimension; x++)
    {
        gfx.PutPixel(x, y1, Colors::Black);
    }
    for (int y = y1; y < y1 + dimension; y++)
    {
        gfx.PutPixel(x1, y, Colors::Black);
    }
}

int Board::GetWidth() const
{
    return width;
}

int Board::GetHeight() const
{
    return height;
}

bool Board::inInsideBoard(const Location& loc) const
{
    return loc.x >= 1 && loc.x < width &&
           loc.y >= 1 && loc.y < height;
}

void Board::DrawBorder() const
{
    for (int x = 19; x < borderWidth; x++)
    {
        gfx.PutPixel(x, 19, borderColour);
    }
    for (int x = 19; x < borderWidth; x++)
    {
        gfx.PutPixel(x, borderHeight, borderColour);
    }
    for (int y = 19; y < borderHeight; y++)
    {
        gfx.PutPixel(19, y, borderColour);
    }
    for (int y = 19; y < borderHeight; y++)
    {
        gfx.PutPixel(borderWidth, y, borderColour);
    }   
}
