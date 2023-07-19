#include "stdafx.h"
#include "Scene1_title.h"

Scene1_title::Scene1_title()
{
	titleBg = new ObImage(L"titleBg.png");
	titleLogo = new ObImage(L"titleLogo.png");
	//skin_btnStart = new ObImage(L"Scene1_title.png");
	//skin_btnExit = new ObImage(L"Scene1_title.png");
	btnStart = new ObRect();
	btnExit = new ObRect();
}

Scene1_title::~Scene1_title()
{
	delete titleBg;
	delete titleLogo;
	delete btnStart;
	delete btnExit;

	TEXTURE->DeleteTexture(L"titleBg.png");
	TEXTURE->DeleteTexture(L"titleLogo.png");
}


void Scene1_title::Init()
{
	CAM->position = Vector2();

	titleBg->SetWorldPos(Vector2());
	titleBg->scale.x = app.GetWidth();
	titleBg->scale.y = app.GetHeight();
	
	titleLogo->SetParentRT(*titleBg);
	titleLogo->SetLocalPosY(app.GetHalfHeight() / 3.0f);
	titleLogo->maxFrame.x = 5;
	titleLogo->maxFrame.y = 12;
	titleLogo->scale.x = titleLogo->imageSize.x / titleLogo->maxFrame.x * (app.GetWidth() / 500.f);
	titleLogo->scale.y = titleLogo->imageSize.y / titleLogo->maxFrame.y * (app.GetHeight() / 500.f);
	titleLogo->ChangeAnim(ANIMSTATE::ONCE, 0.05);

	btnStart->SetParentRT(*titleBg);
	btnStart->SetLocalPosY(-100);
	btnStart->scale.x = 200;
	btnStart->scale.y = 80;
	btnStart->isFilled = false;
	btnStart->color = Vector4(0.5, 0.5, 0.5, 0.5);

	btnExit->SetParentRT(*titleLogo);
	btnExit->SetLocalPosY(-350);
	btnExit->scale.x = 200;
	btnExit->scale.y = 80;
	btnExit->isFilled = false;
	btnExit->color = Vector4(0.5, 0.5, 0.5, 0.5);

	titleBg->Update();
	titleLogo->Update();
	btnStart->Update();
	btnExit->Update();

	Vector2 textBox_start_pos = Utility::WorldToScreen(btnStart->GetWorldPos());
	textBox_start.left = textBox_start_pos.x - 80;
	textBox_start.top = textBox_start_pos.y - 20;
	textBox_start.right = textBox_start.left + 500;
	textBox_start.bottom = textBox_start.top + 500;

	Vector2 textBox_exit_pos = Utility::WorldToScreen(btnExit->GetWorldPos());
	textBox_exit.left = textBox_exit_pos.x - 80;
	textBox_exit.top = textBox_exit_pos.y - 20;
	textBox_exit.right = textBox_exit.left + 1000;
	textBox_exit.bottom = textBox_exit.top + 1000;
}

void Scene1_title::Release()
{
}

void Scene1_title::Update()
{
	ImGui::Text("title_x: %d\n", titleLogo->frame.x);
	ImGui::Text("title_y: %d\n", titleLogo->frame.y);
	ImGui::Text("titleAnimTime: %f\n", titleAnimTime);

	if (titleLogo->frame.x == titleLogo->maxFrame.x - 1)
	{
		if (titleLogo->frame.y != titleLogo->maxFrame.y - 1)
		{
			titleLogo->frame.x = 0;
			titleLogo->frame.y++;
			titleLogo->ChangeAnim(ANIMSTATE::ONCE, 0.05);
		}
		else
		{
			titleAnimTime += DELTA;
		}
	}

	if (titleAnimTime > 5.0f)
	{
		titleAnimTime = 0.0f;
		titleLogo->frame.x = 0;
		titleLogo->frame.y = 0;
		titleLogo->ChangeAnim(ANIMSTATE::ONCE, 0.05);
	}

	OnClick();

	titleBg->Update();
	titleLogo->Update();
	btnStart->Update();
	btnExit->Update();
}

void Scene1_title::LateUpdate()
{
	//if (btnStart->Intersect(INPUT->GetWorldMousePos()))
	//{
	//	cout << " 마우스 올라감" << endl;
	//	btnStart->color = Vector4(1, 0, 0, 0.5);
	//} 

	//if (btnStart->IntersectScreenMouse(INPUT->GetScreenMousePos()))
	//{
	//	btnStart->color = Vector4(1, 0, 0, 0.5);
	//}
	//else btnStart->color = Vector4(0.5, 0.5, 0.5, 0.5);

	//if (btnExit->IntersectScreenMouse(INPUT->GetScreenMousePos()))
	//{
	//	btnExit->color = Vector4(1, 0, 0, 0.5);
	//}
	//else btnExit->color = Vector4(0.5, 0.5, 0.5, 0.5);
}

void Scene1_title::Render()
{
	titleBg->Render();
	titleLogo->Render();
	if (GM->DEBUG_MODE)
	{
		btnStart->Render();
		btnExit->Render();
	}

	if (btnStart->IntersectScreenMouse(INPUT->GetScreenMousePos()))
	{
		ResizeText(1);
		DWRITE->RenderText(
			L"시작하기",
			textBox_start,
			50.0f,
			L"Neo둥근모",
			Color(1, 0.9, 0.5, 0.5),
			DWRITE_FONT_WEIGHT_BOLD,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_ULTRA_EXPANDED);
	}
	else
	{
		DWRITE->RenderText(
			L"시작하기",
			textBox_start,
			40.0f,
			L"Neo둥근모",
			Color(1, 1, 1, 0.5),
			DWRITE_FONT_WEIGHT_BOLD,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_ULTRA_EXPANDED);
	}

	if (btnExit->IntersectScreenMouse(INPUT->GetScreenMousePos()))
	{
		ResizeText(2);
		// 종료
		DWRITE->RenderText(
			L"종료하기",
			textBox_exit,
			50.0f,
			L"Neo둥근모",
			Color(1, 0.9, 0.5, 0.5),
			DWRITE_FONT_WEIGHT_BOLD,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_ULTRA_EXPANDED);
	}
	else
	{
		ResizeText(0);
		DWRITE->RenderText(
			L"종료하기",
			textBox_exit,
			40.0f,
			L"Neo둥근모",
			Color(1, 1, 1, 0.5),
			DWRITE_FONT_WEIGHT_BOLD,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_ULTRA_EXPANDED);
	}

	if (!btnStart->IntersectScreenMouse(INPUT->GetScreenMousePos()) &&
		!btnExit->IntersectScreenMouse(INPUT->GetScreenMousePos()))
	{
		ResizeText(0);
	}
}

void Scene1_title::ResizeScreen()
{
}

void Scene1_title::ResizeText(int type)
{
	if (type == 0)
	{
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
	else if (type == 1)
	{
		Vector2 textBox_start_pos = Utility::WorldToScreen(btnStart->GetWorldPos());
		textBox_start.left = textBox_start_pos.x - 100;
		textBox_start.top = textBox_start_pos.y - 24;
		textBox_start.right = textBox_start.left + 500;
		textBox_start.bottom = textBox_start.top + 500;

		Vector2 textBox_exit_pos = Utility::WorldToScreen(btnExit->GetWorldPos());
		textBox_exit.left = textBox_exit_pos.x - 80;
		textBox_exit.top = textBox_exit_pos.y - 20;
		textBox_exit.right = textBox_exit.left + 500;
		textBox_exit.bottom = textBox_exit.top + 500;
	}
	else if (type == 2)
	{
		Vector2 textBox_start_pos = Utility::WorldToScreen(btnStart->GetWorldPos());
		textBox_start.left = textBox_start_pos.x - 80;
		textBox_start.top = textBox_start_pos.y - 20;
		textBox_start.right = textBox_start.left + 500;
		textBox_start.bottom = textBox_start.top + 500;

		Vector2 textBox_exit_pos = Utility::WorldToScreen(btnExit->GetWorldPos());
		textBox_exit.left = textBox_exit_pos.x - 100;
		textBox_exit.top = textBox_exit_pos.y - 24;
		textBox_exit.right = textBox_exit.left + 500;
		textBox_exit.bottom = textBox_exit.top + 500;
	}


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