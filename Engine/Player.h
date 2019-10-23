#pragma once
#include "Keyboard.h"
#include "Graphics.h"
#include "Ball.h"

class Player
{
public:
	Player(int a_x, int a_y, bool a_player);
	void Update(Keyboard& kbd, Ball& ball);
	void Render(Graphics& gfx) const;
	static constexpr int width = 20;
	static constexpr int height = 100;
	int GetX() const;
	int GetY() const;
	int GetVy() const;
private:
	//Variables:
	bool player;
	int x;
	int y;
	float vy = 0;
	static constexpr float accel = 0.5;
	static constexpr float decel = -0.25;
	static constexpr int maxv = 4;
	//Functions:
};

