#include "stdafx.h"
#include "player.h"
#include "HUD.h"

#include <iomanip>

HUD::HUD()
{
	box_hp = new ObImage(L"ui_box_hp.png");
	box_mp = new ObImage(L"ui_box_mp.png");

	gauge_hp = new ObImage(L"ui_gauge_hp.png");
	gauge_mp = new ObImage(L"ui_gauge_mp.png");



	fontFile = "C:\\Users\\91bot\\source\\repos\\Tadminster\\CastleDefence\\Contents\\Fonts\\neodgm.ttf";
}

HUD::~HUD()
{
	delete box_hp;
	delete box_mp;
	delete gauge_hp;
	delete gauge_mp;

	TEXTURE->DeleteTexture(L"ui_box_hp.png");
	TEXTURE->DeleteTexture(L"ui_box_mp.png");
	TEXTURE->DeleteTexture(L"ui_gauge_hp.png");
	TEXTURE->DeleteTexture(L"ui_gauge_mp.png");
}

void HUD::Init()
{
	box_hp->space = SPACE::SCREEN;
	box_mp->space = SPACE::SCREEN;
	gauge_hp->space = SPACE::SCREEN;
	gauge_mp->space = SPACE::SCREEN;

	box_hp->pivot = OFFSET_LB;
	box_hp->color = Vector4(0.5, 0.5, 0.5, 0.4);
	box_hp->SetWorldPos(Vector2(- app.GetHalfWidth() * 0.95, -app.GetHalfHeight() * 0.9));
	box_hp->scale.x = box_hp->imageSize.x;
	box_hp->scale.y = box_hp->imageSize.y;

	box_mp->pivot = OFFSET_LB;
	box_mp->SetWorldPos(Vector2(- app.GetHalfWidth() * 0.95, -app.GetHalfHeight() * 0.95));
	box_mp->scale.x = box_mp->imageSize.x;
	box_mp->scale.y = box_mp->imageSize.y;

	gauge_hp->SetParentRT(*box_hp);
	gauge_hp->pivot = OFFSET_LB;
	gauge_hp->scale.x = gauge_hp->imageSize.x;
	gauge_hp->scale.y = gauge_hp->imageSize.y;

	gauge_mp->SetParentRT(*box_mp);
	gauge_mp->pivot = OFFSET_LB;
	gauge_mp->scale.x = gauge_mp->imageSize.x;
	gauge_mp->scale.y = gauge_mp->imageSize.y;

	textBox_hp.left = Utility::WorldToScreen(Vector2(app.GetHalfWidth(), 0)).x - 90;
	textBox_hp.top = Utility::WorldToScreen(Vector2(app.GetHalfWidth(), 0)).x - 90;
	textBox_hp.right = textBox_hp.left + 200;
	textBox_hp.bottom = textBox_hp.top + 200;

	textBox_mp.left = Utility::WorldToScreen(Vector2(app.GetHalfWidth(), 0)).x - 90;
	textBox_mp.top = Utility::WorldToScreen(Vector2(0, app.GetHalfHeight())).y + 35;
	textBox_mp.right = textBox_mp.left + 200;
	textBox_mp.bottom = textBox_mp.top + 200;

	textBox_time.left = Utility::WorldToScreen(Vector2(-60, 0)).x;
	textBox_time.top = Utility::WorldToScreen(Vector2(0, 400)).y;
	textBox_time.right = textBox_time.left + 1000;
	textBox_time.bottom = textBox_time.top + 1000;
}

void HUD::Release()
{
}

void HUD::Update()
{
	gauge_hp->scale.x = gauge_hp->imageSize.x * ((float)GM->player->GetHp() / (float)GM->player->GetMaxHp());
	gauge_mp->scale.x = gauge_mp->imageSize.x * ((float)GM->player->GetMp() / (float)GM->player->GetMaxMp());

	box_hp->Update();
	box_mp->Update();
	gauge_mp->Update();
	gauge_hp->Update();

	minute = TIMER->GetWorldTime() / 60;
	second = static_cast<int>(TIMER->GetWorldTime()) % 60;
}

void HUD::LateUpdate()
{
}

void HUD::Render()
{
	box_hp->Render();
	box_mp->Render();
	gauge_hp->Render();
	gauge_mp->Render();

	////Å³aaaa
	//DWRITE->RenderText(
	//	L"" + to_wstring(GM->kill),
	//	textBox_hp,
	//	30.0f,
	//	L"NeoµÕ±Ù¸ð",
	//	Color(0.1, 0.1, 0.1, 1),
	//	DWRITE_FONT_WEIGHT_BOLD,
	//	DWRITE_FONT_STYLE_NORMAL,
	//	DWRITE_FONT_STRETCH_ULTRA_EXPANDED);

	//// ·¹º§
	//DWRITE->RenderText(
	//	L"LV." + to_wstring(GM->player->level),
	//	textBox_mp,
	//	30.0f,
	//	L"NeoµÕ±Ù¸ð",
	//	Color(0.1, 0.1, 0.1, 1),
	//	DWRITE_FONT_WEIGHT_BOLD,
	//	DWRITE_FONT_STYLE_NORMAL,
	//	DWRITE_FONT_STRETCH_ULTRA_EXPANDED);

	//// ½Ã°£
	//DWRITE->RenderText(
	//	wstring(2 - to_wstring(minute).length(), L'0') + to_wstring(minute) + L":" + wstring(2 - to_wstring(second).length(), L'0') + to_wstring(second),
	//	textBox_time,
	//	50.0f,
	//	L"NeoµÕ±Ù¸ð",
	//	Color(0.7, 0.7, 0.7, 1),
	//	DWRITE_FONT_WEIGHT_BOLD,
	//	DWRITE_FONT_STYLE_NORMAL,
	//	DWRITE_FONT_STRETCH_ULTRA_EXPANDED);
}