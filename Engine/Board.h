#pragma once

#include "Graphics.h"
#include "Location.h"
#include "Colors.h"

class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, const Color c);
	int GetWidth() const;
	int GetHeight() const;
	bool inInsideBoard(const Location& loc) const;
	void DrawBorder() const;
	
private:
	static constexpr int dimension = 20; // No. of pixels for each cell
	static constexpr int width = 25;
	static constexpr int height = 25;
	static constexpr Color borderColour = Colors::Cyan;
	static constexpr int borderWidth = 500;
	static constexpr int borderHeight = 500;

	Graphics& gfx;

};




