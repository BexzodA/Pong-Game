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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	playerOne(50, 550, true),
	playerTwo(Graphics::ScreenWidth - 70, 550, false)
{

}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::ClampToScreen(int& x, int& y, const int width, const int height)
{
	if (x < 0) {
		x = 0;
	}
	if (y < 0) {
		y = 0;
	}

	if (x + width > Graphics::ScreenWidth) {
		x = Graphics::ScreenWidth - width;
	}
	if (y + height > Graphics::ScreenHeight) {
		y = Graphics::ScreenHeight - height;
	}
}

bool Game::IsColliding(int x0, int y0, int width0, int height0, int x1, int y1, int width1, int height1)
{
	const int right0 = x0 + width0;
	const int bottom0 = y0 + height0;
	const int right1 = x1 + width1;
	const int bottom1 = y1 + height1;

	return right0 >= x1 &&
		x0 <= right1 &&
		bottom0 >= y1 &&
		y0 <= bottom1;
}

bool Game::IsCollidingHor(int x0, int y0, int width0, int height0, int x1, int y1, int width1, int height1)
{
	const int right0 = x0 + width0;
	const int right1 = x1 + width1;

	return right0 >= x1 &&
		x0 <= right1;
}

bool Game::IsCollidingVer(int x0, int y0, int width0, int height0, int x1, int y1, int width1, int height1)
{
	const int bottom0 = y0 + height0;
	const int bottom1 = y1 + height1;
	
	return 	bottom0 >= y1 &&
		y0 <= bottom1;
}

void Game::UpdateModel()
{
	playerOne.Update(wnd.kbd, ball);
	playerTwo.Update(wnd.kbd, ball);
	ball.Update(playerOne, playerTwo);
	if (ball.GetX() == Ball::radius) {
		ball = Ball();
	}
	if (ball.GetX() == Graphics::ScreenWidth - Ball::radius - 1) {
		ball = Ball();
	}

}

void Game::ComposeFrame()
{
	playerOne.Render(gfx);
	playerTwo.Render(gfx);
	gfx.DrawDottedLine(597, 988, 6, 6);
	ball.Render(gfx);
}
