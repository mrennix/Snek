/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include <random>
#include <vector>
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "Snake.h"
#include "Goal.h"
#include "Enemy.h"
#include "FrameTimer.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	/********************************/
	FrameTimer ft;
	Board brd;
	std::mt19937 rng;
	Snake snake;
	std::vector<Enemy> enemies;
	Location delta_loc = { 1, 0 };
	static constexpr Location delta_loc_up = { 0, -1 };
	static constexpr Location delta_loc_down = { 0, 1 };
	static constexpr Location delta_loc_right = { 1, 0 };
	static constexpr Location delta_loc_left = { -1, 0 };
	Location prev_delta_loc = { 0, 0 };
	Goal goal;
	
	static constexpr float snakeMovePeriodMin = 0.01f;  // A lower bound on snake speed...um actually not sure
	float snakeMovePeriod = 0.2f;   // Decrease to make snake start quicker
	float snakeMoveCounter = 0.0f;
	//float snakeSpeedCounter = 0;
	int enemyAppearCounter = 0;
	static constexpr int enemyAppearPeriod = 3; // number of treats to eat before a new rock is spawned
	static constexpr float snakeSpeedUpFactor = 0.12f; // Increase to make snake speed up quicker after eating a treat
	bool gameIsOver = false;
	bool gameIsStarted = false;
	std::wstring gameOverTitle = L"Snek - The Game!";
	std::wstring gameOverMsg = L"Poor Snek died, it had length: ";
};