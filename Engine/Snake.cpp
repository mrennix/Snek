#include "Snake.h"
#include <cassert>

Snake::Snake(const Location& loc)
{
    segments[0].InitHead(loc);
	bodyColours[0] = Colors::MakeRGB(0x00, 0x56, 0x3F);
	bodyColours[1] = Colors::MakeRGB(0x35, 0x5E, 0x3B);
	bodyColours[2] = Colors::MakeRGB(0x13, 0x88, 0x08);
	
}

void Snake::MoveBy(const Location& delta_loc)
{
	// Move the snake body
	for (int i = nSegments - 1; i > 0; i--)
	{
		segments[i].Follow(segments[i - 1]);
	}
	// Move the snake head
	segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
	if (nSegments < nSegmentsMax)
	{
		segments[nSegments].InitBody();
		++nSegments;
	}
}

void Snake::Draw(Board& brd) const
{
	for (int i = 0; i < nSegments; i++)
	{
		segments[i].Draw(brd);
	}
}

bool Snake::isInTileExceptEnd(const Location& target) const
{
	for (int i = 0; i < nSegments - 1; i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

bool Snake::isInTile(const Location& target) const
{
	for (int i = 0; i < nSegments; i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

int Snake::getSnakeSize() const
{
	return nSegments;
}

void Snake::Segment::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody()
{
	//c = Snake::bodyColor;
	c = bodyColours[colCycle++];
	colCycle %= nBodyColoursMax;
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	// Check that either x or y is 1 as snake can only move 1 cell at a time
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

Location Snake::GetNextHeadLocation(const Location& delta_loc) const
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

void Snake::Segment::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}
