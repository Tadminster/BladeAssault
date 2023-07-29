#include "stdafx.h"
#include "DamageText.h"

DamageText::DamageText(Vector2 spawnPos, int value, int color)
{
	this->spawnPos = spawnPos;

	text = new ObImage(L"ui_pixel_font.png");

	text->SetWorldPos(this->spawnPos);
	text->maxFrame.x = 11;
	text->maxFrame.y = 7;
	
	// 크리티컬 데미지는 글자크기를 1.2배로 키움
	float scale = 1.0f;
	if (color == 6) scale = 1.2f;

	text->scale.x = text->imageSize.x / text->maxFrame.x * 2.0f * scale;
	text->scale.y = text->imageSize.y / text->maxFrame.y * 2.0f * scale;

	// value
	if (value == 0)
		text->frame.x = 0;
	else if (value == 1)
		text->frame.x = 1;
	else if (value == 2)
		text->frame.x = 2;
	else if (value == 3)
		text->frame.x = 3;
	else if (value == 4)
		text->frame.x = 4;
	else if (value == 5)
		text->frame.x = 5;
	else if (value == 6)
		text->frame.x = 6;
	else if (value == 7)
		text->frame.x = 7;
	else if (value == 8)
		text->frame.x = 8;
	else if (value == 9)
		text->frame.x = 9;
	else if (value == 10)
		text->frame.x = 10;
	else 
		text->frame.x = 0;

	// color
	if (color == 0)
		text->frame.y = 0;
	else if (color == 1)
		text->frame.y = 1;
	else if (color == 2)
		text->frame.y = 2;
	else if (color == 3)
		text->frame.y = 3;
	else if (color == 4)
		text->frame.y = 4;
	else if (color == 5)
		text->frame.y = 5;
	else if (color == 6)
		text->frame.y = 6;
	else 
		text->frame.y = 0;

	traveledDistance = 0.0f;
	speed = 50.0f;
	range = 150.0f;
}

DamageText::~DamageText()
{
	delete text;
}

void DamageText::Init()
{
}

void DamageText::Release()
{
}

void DamageText::Update()
{
	text->MoveWorldPos(UP * speed * DELTA);
	text->color.w -= 0.5f * DELTA;

	text->Update();
}

void DamageText::LateUpdate()
{
	// 이동한 거리 계산
	//ImGui::Text("traveledDistance %f\n", traveledDistance);
	//traveledDistance = Vector2(spawnPos - text->GetWorldPos()).Length();
	traveledDistance = Vector2::Distance(spawnPos, text->GetWorldPos());
	cout << "traveledDistance " << traveledDistance << endl;
}

void DamageText::Render()
{
	text->Render();
}

bool DamageText::hasTraveledTooFar() const
{
	if (traveledDistance >= range)
	{
		delete this;
		return true;
	}
	return false;
}
