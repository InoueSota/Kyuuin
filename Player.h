#pragma once
#include <Novice.h>
#include "Vec2.h"
#include "Screen.h"

class Player
{
public:

	Player();
	~Player();

	//�ϐ�
	Vec2 pos;
	Vec2 center;
	Vec2 add;
	Vec2 tmppos;
	float deg;
	float radius;

	//�֐�
	void Init();
	virtual void CircleProcess() {};
	virtual void SetDegree() {};
	void Move() {
		add.x = cosf(Degree(deg));
		add.y = sinf(Degree(deg));
		pos = center + add * 300;
	}
	void Process(char prekeys, char keys);
	void Draw(Screen& screen);

private:

};

class CircleA : public Player {
public:
	void CircleProcess();
	void SetDegree();
};

class CircleB : public Player {
public:
	void CircleProcess();
	void SetDegree();
};