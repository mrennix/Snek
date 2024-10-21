/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"
#include "Location.h"
#include <string>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd( gfx ),
	rng( std::random_device()()),
	snake({10,10}),
	goal(rng, brd, snake, enemies)
{
	// Grow the snake a few times before the game starts
	snake.Grow();
	snake.MoveBy(delta_loc_right);
	snake.Grow();
	snake.MoveBy(delta_loc_right);
	snake.Grow();
	snake.MoveBy(delta_loc_right);
	//enemies.emplace_back(Enemy( rng, brd, snake, enemies ));
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();

	if (!gameIsOver)
	{
		if (gameIsStarted)
		{
			if (wnd.kbd.KeyIsPressed(VK_UP))
			{
				if (prev_delta_loc != delta_loc_down) // Prevent snake from moving in the opposite direction into itself!
				{
					delta_loc = delta_loc_up;
				}
			}
			else if (wnd.kbd.KeyIsPressed(VK_DOWN))
			{
				if (prev_delta_loc != delta_loc_up)  // Prevent snake from moving in the opposite direction into itself!
				{
					delta_loc = delta_loc_down;
				}
			}
			else if (wnd.kbd.KeyIsPressed(VK_LEFT))  
			{
				if (prev_delta_loc != delta_loc_right)  // Prevent snake from moving in the opposite direction into itself!
				{
					delta_loc = delta_loc_left;
				}
			}
			else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			{
				if (prev_delta_loc != delta_loc_left)  // Prevent snake from moving in the opposite direction into itself!
				{
					delta_loc = delta_loc_right;
				}
			}
			prev_delta_loc = delta_loc;
			snakeMoveCounter += dt;
			if (snakeMoveCounter >= snakeMovePeriod)
			{
				snakeMoveCounter -= snakeMovePeriod;
				const Location next = snake.GetNextHeadLocation(delta_loc);
				// Collision detection
				if (!brd.inInsideBoard(next) || snake.isInTileExceptEnd(next))
				{
					gameIsOver = true;
				}
				else
				{
					for (const auto& enemy : enemies)
					{
						const bool enemyCollision = (next == enemy.GetLocation());
						if (enemyCollision)
						{
							gameIsOver = true;
							break;
						}
					}
					if (!gameIsOver)
					{
						const bool eating = (next == goal.GetLocation());
						if (eating)
						{
							snake.Grow();
						}
						snake.MoveBy(delta_loc);
						if (eating)
						{
							if (++enemyAppearCounter >= enemyAppearPeriod)
							{
								enemyAppearCounter = 0;
								enemies.emplace_back(Enemy(rng, brd, snake, enemies)); // Spawn a random rock
							}
							goal.Respawn(rng, brd, snake, enemies);
							
							//if (++snakeSpeedCounter >= snakeSpeedPeriod)
							//{
							//	snakeSpeedCounter = 0;
							//	snakeMovePeriod--; // Inrease snake speed!
							//}
							snakeMovePeriod = std::max(snakeMovePeriod - dt * snakeSpeedUpFactor, snakeMovePeriodMin);
							//snakeMovePeriod = snakeMovePeriod - dt * snakeSpeedUpFactor;

						}
					}
					
				}
			}
		}
		else 
		{
			if (wnd.kbd.KeyIsPressed(VK_RETURN))
			{
				gameIsStarted = true;
			}
		}
	}
}

void Game::ComposeFrame()
{
	if (gameIsStarted)
	{
		brd.DrawBorder();
		snake.Draw(brd);
		goal.Draw(brd);
		// gfx.DrawCircle(200, 200, 10, Colors::Magenta);
		for (const auto& enemy : enemies)
		{
			enemy.Draw(brd);
		}
		if (gameIsOver)
		{
			SpriteCodex::DrawGameOver(610, 210, gfx);
			gameOverMsg += std::to_wstring(snake.getSnakeSize());
			wnd.ShowMessageBox(gameOverTitle, gameOverMsg);
			wnd.Kill(); // Quit the application
		}
	}
	else
	{
		brd.DrawBorder();
		SpriteCodex::DrawTitle(160, 160, gfx);
	}
	
}
