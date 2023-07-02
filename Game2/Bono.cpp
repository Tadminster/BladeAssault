#include "stdafx.h"
#include "Bono.h"

Bono::Bono()
{
	top = new ObImage(L"bono.bmp");
	top->scale.x = 100.0f;
	top->scale.y = 120.0f;
	top->pivot = OFFSET_LT;
	top->SetLocalPosY(75.0f);


	col = new ObRect();
	col->scale = top->scale;
	col->scale.y = 15.0f;


	col->isFilled = false;
	col->pivot = OFFSET_LT;
	//col->hasAxis = true;
	col->color.x = 1.0f;
	col->color.y = 0.0f;
	col->color.z = 0.0f;
	col->SetWorldPosY(-200.0f);

	top->SetParentRT(*col);
}

Bono::~Bono()
{
}

void Bono::Init(Vector2 spwan, bool active)
{
	col->SetWorldPos(spwan);
	this->active = active;
}

void Bono::Update()
{
	//if (not active) return;

	top->Update();
	col->Update();
}

void Bono::Render()
{
	if (not active) return;

	top->Render();
	col->Render();
}
