#pragma once
#include "Graphics.h"
#include "Player.h"

class Ball
{
public:
	Ball();
	void Update(const Player& one, const Player& two);
	void Render(Graphics& gfx);
	int GetX() const;
	int GetY() const;
	void SetY(int a_y);
	static constexpr int radius = 8;
private:
	int x;
	int y;
	float vx = 0;
	float vy = 0;
	static constexpr float maxVel = 5;
	void ClampToScreen();
};

