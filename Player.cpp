#include "Player.h"

CircleA circleA;
CircleB circleB;
Player* player = &circleA;


Player::Player()
{
	Player::Init();
}

Player::~Player()
{
}

void Player::Init() {
	pos = { 0,0 };
	center = { pos.x,pos.y };
	add = { 0,0 };
	tmppos = { 0,0 };
	deg = 0;
	radius = 50;
	Reverse = 1;
	incDeg = 2;
	Length = 300;
}

void Player::SetPlayers(Player& players) {
	players.pos = player->pos;
}



void CircleA::CircleProcess(Player& players) {
	circleA.deg += (incDeg * Reverse);
	if (circleA.deg > 360) {
		circleA.deg = 0;
	}
	circleA.add.x = cosf(Degree(circleA.deg));
	circleA.add.y = sinf(Degree(circleA.deg));
	circleB.center = circleA.pos;
	circleA.pos = circleA.center + circleA.add * players.Length;
	player->pos = circleA.pos;
}
void CircleB::CircleProcess(Player& players) {
	circleB.deg -= (incDeg * Reverse);
	if (circleB.deg < -360){
		circleB.deg = 0;
	}
	circleB.add.x = cosf(Degree(circleB.deg));
	circleB.add.y = sinf(Degree(circleB.deg));
	circleA.center = circleB.pos;
	circleB.pos = circleB.center + circleB.add * players.Length;
	player->pos = circleB.pos;
}



//CircleBのDegreeを求める関数
void CircleA::SetDegree() {

	circleA.tmppos = circleA.add;
	circleB.tmppos = {-1,0};

	float dp = circleA.tmppos.Dot(circleB.tmppos);
	float cp = circleA.tmppos.Cross(circleB.tmppos);
	float angleAB = Radian(atan2(cp, dp));

	circleB.deg = -angleAB;

}
//CircleAのDegreeを求める関数
void CircleB::SetDegree() {

	circleA.tmppos = {1,0};
	circleB.tmppos = circleB.add;

	float dp = circleA.tmppos.Dot(circleB.tmppos);
	float cp = circleA.tmppos.Cross(circleB.tmppos);
	float angleAB = Radian(atan2(cp, dp));

	circleA.deg = angleAB + 180;
}



void Player::Process(Player& players, char prekeys, char keys, char predik_d, char dik_d) {
	if (predik_d == 0 && dik_d){
		Reverse *= -1;
	}
	if (prekeys == 0 && keys) {
		player->SetDegree();
		if (player == &circleA){
			player = nullptr;
			player = &circleB;
		}
		else if (player == &circleB) {
			player = nullptr;
			player = &circleA;
		}
	}
	player->CircleProcess(players);
}

void Player::Draw(Screen& screen) {
	screen.DrawLine(circleA.pos.x, circleA.pos.y, circleB.pos.x, circleB.pos.y, BLACK);
	screen.DrawEllipse(circleA.pos.x, circleA.pos.y, radius, radius, 0.0f, BLACK, kFillModeSolid);
	screen.DrawEllipse(circleB.pos.x, circleB.pos.y, radius, radius, 0.0f, BLACK, kFillModeSolid);
	Novice::ScreenPrintf(0, 0, "Reverse : %d", Reverse);
}