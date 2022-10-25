#include "Title.h"

void Title::Init() {
	BackCirclepos = { 0,0 };
	Titlepos = { 0,0 };
	Spacepos = { 0,0 };
	Arrowpos = { 0,0 };
	Letspos = { 0,0 };
	Targetpos = { 0,-1500 };
	isTitleClear = true;
	isLoadTexture = false;
}
void Title::Process(char prekeys, char keys) {
	if (isLoadTexture == false){
		titlebackground = Novice::LoadTexture("./resource/Title/Titlebackground.png");
		title = Novice::LoadTexture("./resource/Title/Title.png");
		space = Novice::LoadTexture("./resource/Title/Space.png");
		lets = Novice::LoadTexture("./resource/Title/Lets.png");
		isLoadTexture = true;
	}
	theta += 1 / (8.0f * M_PI);
	Titlepos.y = sinf(theta) * 20;
	Spacepos.y = sinf(theta) * 20 - (SCREEN_HEIGHT / 4);
	Arrowpos.y = sinf(theta) * 20 - 600;
	Letspos.y = sinf(theta) * 20 - 1300;
	if (isExist == false) {
		TargetRipplespos = Targetpos;
		Rradius = 20;
		Rcolor = 0x000000FF;
		Existtime = 0.0f;
		isExist = true;
	}
	if (isExist == true) {
		Rradius += 3;
		Existtime += 0.01f;
		Rcolor = 0x00000000 | static_cast<int>((1.0f - Existtime) * 0xFF + Existtime * 0x00);
		if (Rcolor == 0x00000000) {
			isExist = false;
		}
	}
}
void Title::Draw(Screen& screen, Title& title) {
	Quad titles{
		{title.Titlepos.x - (kTitleWidth / 2), title.Titlepos.y + (kTitleHeight / 2)},
		{title.Titlepos.x + (kTitleWidth / 2), title.Titlepos.y + (kTitleHeight / 2)},
		{title.Titlepos.x - (kTitleWidth / 2), title.Titlepos.y - (kTitleHeight / 2)},
		{title.Titlepos.x + (kTitleWidth / 2), title.Titlepos.y - (kTitleHeight / 2)}
	}, spaces{
		{title.Spacepos.x - (kSpaceWidth / 2), title.Spacepos.y + (kSpaceHeight / 2)},
		{title.Spacepos.x + (kSpaceWidth / 2), title.Spacepos.y + (kSpaceHeight / 2)},
		{title.Spacepos.x - (kSpaceWidth / 2), title.Spacepos.y - (kSpaceHeight / 2)},
		{title.Spacepos.x + (kSpaceWidth / 2), title.Spacepos.y - (kSpaceHeight / 2)}
	}, arrows{
		{title.Arrowpos.x - (kArrowWidth / 2), title.Arrowpos.y + (kArrowHeight / 2)},
		{title.Arrowpos.x + (kArrowWidth / 2), title.Arrowpos.y + (kArrowHeight / 2)},
		{title.Arrowpos.x - (kArrowWidth / 2), title.Arrowpos.y - (kArrowHeight / 2)},
		{title.Arrowpos.x + (kArrowWidth / 2), title.Arrowpos.y - (kArrowHeight / 2)}
	}, arrowstriangle{
		{title.Arrowpos.x - kArrowWidth, title.Arrowpos.y - (kArrowHeight / 2)},
		{title.Arrowpos.x + kArrowWidth, title.Arrowpos.y - (kArrowHeight / 2)},
		{title.Arrowpos.x, title.Arrowpos.y - kArrowHeight * 2},
		{title.Arrowpos.x, title.Arrowpos.y - kArrowHeight * 2}
	}, letss{
		{title.Letspos.x - (kLetsWidth / 2), title.Letspos.y + (kLetsHeight / 2)},
		{title.Letspos.x + (kLetsWidth / 2), title.Letspos.y + (kLetsHeight / 2)},
		{title.Letspos.x - (kLetsWidth / 2), title.Letspos.y - (kLetsHeight / 2)},
		{title.Letspos.x + (kLetsWidth / 2), title.Letspos.y - (kLetsHeight / 2)}
	};
	
	for (int i = 0; i < 15; i++){
		screen.DrawEllipse(BackCirclepos.x, BackCirclepos.y, kBackCircleRadius + i, kBackCircleRadius + i, 0.0f, 0xE5C210FF, kFillModeWireFrame);
	}
	screen.DrawQuad2(titles, 0, 0, kTitleWidth, kTitleHeight, title.title, WHITE);
	screen.DrawQuad2(spaces, 0, 0, kSpaceWidth, kSpaceHeight, title.space, WHITE);
	screen.DrawQuad2(arrows, 0, 0, 0, 0, 0, 0xE5C210FF);
	screen.DrawQuad2(arrowstriangle, 0, 0, 0, 0, 0, 0xE5C210FF);
	screen.DrawQuad2(letss, 0, 0, kLetsWidth, kLetsHeight, title.lets, WHITE);
	screen.DrawEllipse(TargetRipplespos.x, TargetRipplespos.y, Rradius, Rradius, 0.0f, Rcolor, kFillModeSolid);
	screen.DrawEllipse(Targetpos.x, Targetpos.y, kTargetRadius, kTargetRadius, 0.0f, 0xE80971FF, kFillModeSolid);
}