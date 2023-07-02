#include "stdafx.h"
#include "Score.h"

Score::Score()
{
	top = new ObImage(L"jelly.png");
	top->scale.x = 40.0f;
	top->scale.y = 40.0f;
	top->pivot = OFFSET_LB;
	top->maxFrame.x = 3;
	top->ChangeAnim(ANIMSTATE::LOOP, 0.1f);


	col = new ObRect();
	col->isFilled = false;
	col->pivot = OFFSET_LB;
	col->color.x = 1.0f;
	col->color.y = 0.0f;
	col->color.z = 0.0f;

	top->SetParentRT(*col);
}

Score::~Score()
{
	SOUND->DeleteSound(soundKey);
}

void Score::Init(Vector2 spwan, bool active)
{
	top->frame.x = RANDOM->Int(0, 2);
	col->SetWorldPos(spwan);
	this->active = active;
}

void Score::Update()
{
	top->Update();
	col->Update();
}

void Score::Render()
{
	if (not active) return;

	top->Render();
	col->Render();
}

void Score::PlaySoundEffect()
{
	SOUND->Play(soundKey);
}
