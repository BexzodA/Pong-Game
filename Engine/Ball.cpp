#include "Ball.h"
#include <random>
#include "Game.h"

Ball::Ball()
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> Range(8, 992);
	std::uniform_int_distribution<int> VelRand(-2, 2);

	x = 599;
	y = Range(rng);

	vx = VelRand(rng);
	vy = VelRand(rng);
	
	while (vx == 0 || vy == 0) {
		vx = VelRand(rng);
		vy = VelRand(rng);
	}
}

void Ball::Update(const Player& one, const Player& two)
{
	x += vx;
	y += vy;
	
	ClampToScreen();

	if (Game::IsColliding(one.GetX(), one.GetY(), Player::width, Player::height, x - radius,y - radius, radius * 2, radius * 2)) {
		if (one.GetVy() != 0) {
			if (vx < 0) {
				vx -= .25;
			}
			else {
				vx += .25;
			}
		}
		if(Game::IsCollidingHor(one.GetX(), one.GetY(), Player::width, Player::height, x - radius, y - radius, radius * 2, radius * 2))
			vx *= -1;
		else {
			vy *= -1;
		}

	}
	if (Game::IsColliding(two.GetX(), two.GetY(), Player::width, Player::height, x - radius, y - radius, radius * 2, radius * 2)) {
		if (two.GetVy() != 0) {
			if (vx < 0) {
				vx -= .25;
			}
			else {
				vx += .25;
			}
		}
		if(Game::IsCollidingHor(two.GetX(), two.GetY(), Player::width, Player::height, x - radius, y - radius, radius * 2, radius * 2))
			vx *= -1;
		else {
			vy *= -1;
		}
	}

	if (std::abs(vx) > maxVel) {
		if (vx < 0) {
			vx = -maxVel;
		}
		else {
			vx = maxVel;
		}
	}
}

void Ball::Render(Graphics& gfx)
{
	gfx.DrawCircle(x, y, radius);
}

int Ball::GetX() const
{
	return x;
}

int Ball::GetY() const
{
	return y;
}

void Ball::SetY(int a_y)
{
	y = a_y;

	if (y - radius < 0) {
		y = 0 + radius;
		vy *= -1;
	}

	if (y + radius + 1 > Graphics::ScreenHeight) {
		y = Graphics::ScreenHeight - radius - 1;
		vy *= -1;
	}
}

void Ball::ClampToScreen()
{
	if (x - radius < 0) {
		x = radius;
		vx *= -1;
	}
	if (y - radius < 0) {
		y = 0 + radius;
		vy *= -1;
	}
	if (x + radius + 1 > Graphics::ScreenWidth) {
		x = Graphics::ScreenWidth - radius - 1;
		vx *= -1;
	}
	if (y + radius + 1 > Graphics::ScreenHeight) {
		y = Graphics::ScreenHeight - radius - 1;
		vy *= -1;
	}
}
