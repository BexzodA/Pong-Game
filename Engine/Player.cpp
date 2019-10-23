#include "Player.h"
#include "Game.h"
#include "Ball.h"

Player::Player(int a_x, int a_y, bool a_player) :
	x(a_x),
	y(a_y),
	player(a_player)
{
}

void Player::Update(Keyboard& kbd, Ball& ball)
{
	if (player) {
		if (kbd.KeyIsPressed('W')) {
			vy -= accel;
		}
		if (kbd.KeyIsPressed('S')) {
			vy += accel;
		}
	}
	else {
		if (kbd.KeyIsPressed(VK_UP)) {
			vy -= accel;
		}
		if (kbd.KeyIsPressed(VK_DOWN)) {
			vy += accel;
		}
	}

	if (std::abs(vy) > maxv) {
		if (vy < 0) {
			vy = -maxv;
		}
		else {
			vy = maxv;
		}
	}
	
	y += vy;

	if (Game::IsCollidingVer(x, y, width, height, ball.GetX() - Ball::radius, ball.GetY() - Ball::radius, Ball::radius * 2, Ball::radius * 2)) {
		ball.SetY(ball.GetY() + vy);
	}

	Game::ClampToScreen(x, y, width, height);

	if (std::abs(vy) > 0)
		if (vy < 0)
			vy -= decel;
		else
			vy += decel;
}

void Player::Render(Graphics& gfx) const
{
	gfx.DrawRectangle(x, y, width, height, Color(255, 255, 255));
}

int Player::GetX() const
{
	return x;
}

int Player::GetY() const
{
	return y;
}

int Player::GetVy() const
{
	return vy;
}
