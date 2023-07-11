#include "stdafx.h"
#include "Scene1_title.h"

Scene1_title::Scene1_title()
{
	bg_title = new ObImage(L"Title.png");
	//skin_btnStart = new ObImage(L"Scene1_title.png");
	//skin_btnExit = new ObImage(L"Scene1_title.png");
	btnStart = new ObRect();
	btnExit = new ObRect();
}

Scene1_title::~Scene1_title()
{
	delete bg_title;
	delete btnStart;
	delete btnExit;

	TEXTURE->DeleteTexture(L"Title.png");
}


void Scene1_title::Init()
{
	bg_title->SetWorldPos(Vector2());
	//bg_title->scale.x = bg_title->imageSize.x;
	//bg_title->scale.y = bg_title->imageSize.y;
	bg_title->scale.x = app.GetWidth();
	bg_title->scale.y = app.GetHeight();

	btnStart->SetParentRT(*bg_title);
	btnStart->SetLocalPosY(0);
	btnStart->scale.x = 200;
	btnStart->scale.y = 100;
	btnStart->isFilled = false;
	btnStart->color = Vector4(0.5, 0.5, 0.5, 0.5);

	btnExit->SetParentRT(*bg_title);
	btnExit->SetLocalPosY(-200);
	btnExit->scale.x = 200;
	btnExit->scale.y = 100;
	btnExit->isFilled = false;
	btnExit->color = Vector4(0.5, 0.5, 0.5, 0.5);

	Vector2 textBox_start_pos = Utility::WorldToScreen(btnStart->GetWorldPos());
	textBox_start.left = textBox_start_pos.x - 80;
	textBox_start.top = textBox_start_pos.y - 20;
	textBox_start.right = textBox_start.left + 500;
	textBox_start.bottom = textBox_start.top + 500;

	Vector2 textBox_exit_pos = Utility::WorldToScreen(btnExit->GetWorldPos());
	textBox_exit.left = textBox_exit_pos.x - 80;
	textBox_exit.top = textBox_exit_pos.y - 20;
	textBox_exit.right = textBox_exit.left + 500;
	textBox_exit.bottom = textBox_exit.top + 500;
}

void Scene1_title::Release()
{
}

void Scene1_title::Update()
{
	OnClick();

	bg_title->Update();
	btnStart->Update();
	btnExit->Update();
}

void Scene1_title::LateUpdate()
{
	if (btnStart->IntersectScreenMouse(INPUT->GetScreenMousePos()))
	{
		btnStart->color = Vector4(1, 0, 0, 0.5);
	}
	else btnStart->color = Vector4(0.5, 0.5, 0.5, 0.5);

	if (btnExit->IntersectScreenMouse(INPUT->GetScreenMousePos()))
	{
		btnExit->color = Vector4(1, 0, 0, 0.5);
	}
	else btnExit->color = Vector4(0.5, 0.5, 0.5, 0.5);
}

void Scene1_title::Render()
{
	// 시작
	DWRITE->RenderText(
		L"시작하기",
		textBox_start,
		40.0f,
		L"Neo둥근모",
		Color(1, 1, 1, 1),
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_ULTRA_EXPANDED);

	// 종료
	DWRITE->RenderText(
		L"종료하기",
		textBox_exit,
		40.0f,
		L"Neo둥근모",
		Color(1, 1, 1, 1),
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_ULTRA_EXPANDED);

	bg_title->Render();
	btnStart->Render();
	btnExit->Render();
}

void Scene1_title::ResizeScreen()
{
}

void Scene1_title::OnClick()
{
	if (INPUT->KeyDown(VK_LBUTTON))
	{
		if (btnStart->IntersectScreenMouse(INPUT->GetScreenMousePos()))
		{
			SCENE->ChangeScene("sc2");
		}
		if (btnExit->IntersectScreenMouse(INPUT->GetScreenMousePos()))
		{
			exit(1);
		}
	}
}