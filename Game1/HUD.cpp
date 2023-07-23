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

	core_LBUTTON = new ObImage(L"ui_core_frame_normal.png");
	core_RBUTTON = new ObImage(L"ui_core_frame_normal.png");
	core_SPACE = new ObImage(L"ui_core_frame_normal.png");

	icon_LBUTTON = new ObImage(L"ui_keyboard_input_keys_defalut.png");
	icon_RBUTTON = new ObImage(L"ui_keyboard_input_keys_defalut.png");
	icon_SPACE = new ObImage(L"ui_keyboard_input_keys_defalut.png");

	icon_mainWeapon = new ObImage(L"playerattack_icon_kill_subweapon.png");
	icon_skillWeapon = new ObImage(L"playerattack_icon_kill_subweapon.png");
	icon_dash = new ObImage(L"playerattack_icon_kill_dash.png");
}

HUD::~HUD()
{
	delete box_hp;
	delete box_mp;
	delete gauge_hp;
	delete gauge_mp;
	delete core_LBUTTON;
	delete core_RBUTTON;
	delete core_SPACE;
	delete icon_LBUTTON;
	delete icon_RBUTTON;
	delete icon_SPACE;
	delete icon_mainWeapon;
	delete icon_skillWeapon;
	delete icon_dash;

	TEXTURE->DeleteTexture(L"ui_box_hp.png");
	TEXTURE->DeleteTexture(L"ui_box_mp.png");
	TEXTURE->DeleteTexture(L"ui_gauge_hp.png");
	TEXTURE->DeleteTexture(L"ui_gauge_mp.png");
	TEXTURE->DeleteTexture(L"ui_core_frame_normal.png");
}

void HUD::Init()
{
	box_hp->space = SPACE::SCREEN;
	box_mp->space = SPACE::SCREEN;
	gauge_hp->space = SPACE::SCREEN;
	gauge_mp->space = SPACE::SCREEN;
	core_LBUTTON->space = SPACE::SCREEN;
	core_RBUTTON->space = SPACE::SCREEN;
	core_SPACE->space = SPACE::SCREEN;
	icon_LBUTTON->space = SPACE::SCREEN;
	icon_RBUTTON->space = SPACE::SCREEN;
	icon_SPACE->space = SPACE::SCREEN;
	icon_mainWeapon->space = SPACE::SCREEN;
	icon_skillWeapon->space = SPACE::SCREEN;
	icon_dash->space = SPACE::SCREEN;

	box_hp->pivot = OFFSET_LB;
	box_hp->SetWorldPos(Vector2(-app.GetHalfWidth() * 0.95, -app.GetHalfHeight() * 0.9));
	box_hp->scale.x = box_hp->imageSize.x;
	box_hp->scale.y = box_hp->imageSize.y;

	box_mp->pivot = OFFSET_LB;
	box_mp->SetWorldPos(Vector2(-app.GetHalfWidth() * 0.95, -app.GetHalfHeight() * 0.95));
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

	core_LBUTTON->pivot = OFFSET_LB;
	core_LBUTTON->SetWorldPos(Vector2(app.GetHalfWidth() * 0.55, -app.GetHalfHeight() * 0.95));
	core_LBUTTON->scale.x = core_LBUTTON->imageSize.x * 0.5;
	core_LBUTTON->scale.y = core_LBUTTON->imageSize.y * 0.5;

	core_RBUTTON->pivot = OFFSET_LB;
	core_RBUTTON->SetWorldPos(Vector2(app.GetHalfWidth() * 0.70, -app.GetHalfHeight() * 0.95));
	core_RBUTTON->scale.x = core_RBUTTON->imageSize.x * 0.5;
	core_RBUTTON->scale.y = core_RBUTTON->imageSize.y * 0.5;

	core_SPACE->pivot = OFFSET_LB;
	core_SPACE->SetWorldPos(Vector2(app.GetHalfWidth() * 0.85, -app.GetHalfHeight() * 0.95));
	core_SPACE->scale.x = core_SPACE->imageSize.x * 0.5;
	core_SPACE->scale.y = core_SPACE->imageSize.y * 0.5;

	icon_mainWeapon->SetParentRT(*core_LBUTTON);
	icon_mainWeapon->pivot = OFFSET_LB;
	icon_mainWeapon->scale.x = icon_mainWeapon->imageSize.x * 0.5;
	icon_mainWeapon->scale.y = icon_mainWeapon->imageSize.y * 0.5;

	icon_skillWeapon->SetParentRT(*core_RBUTTON);
	icon_skillWeapon->pivot = OFFSET_LB;
	icon_skillWeapon->scale.x = icon_skillWeapon->imageSize.x * 0.5;
	icon_skillWeapon->scale.y = icon_skillWeapon->imageSize.y * 0.5;

	icon_dash->SetParentRT(*core_SPACE);
	icon_dash->pivot = OFFSET_LB;
	icon_dash->scale.x = icon_dash->imageSize.x * 0.5;
	icon_dash->scale.y = icon_dash->imageSize.y * 0.5;

	icon_LBUTTON->SetParentRT(*core_LBUTTON);
	icon_LBUTTON->pivot = OFFSET_LB;
	icon_LBUTTON->maxFrame.x = 3;
	icon_LBUTTON->frame.x = 0;
	icon_LBUTTON->scale.x = icon_LBUTTON->imageSize.x / icon_LBUTTON->maxFrame.x * 1.4f;
	icon_LBUTTON->scale.y = icon_LBUTTON->imageSize.y * 1.4f;

	icon_RBUTTON->SetParentRT(*core_RBUTTON);
	icon_RBUTTON->pivot = OFFSET_LB;
	icon_RBUTTON->maxFrame.x = 3;
	icon_RBUTTON->frame.x = 1;
	icon_RBUTTON->scale.x = icon_RBUTTON->imageSize.x / icon_LBUTTON->maxFrame.x * 1.4f;
	icon_RBUTTON->scale.y = icon_RBUTTON->imageSize.y * 1.4f;

	icon_SPACE->SetParentRT(*core_SPACE);
	icon_SPACE->pivot = OFFSET_LB;
	icon_SPACE->maxFrame.x = 3;
	icon_SPACE->frame.x = 2;
	icon_SPACE->scale.x = icon_SPACE->imageSize.x / icon_LBUTTON->maxFrame.x * 1.4f;
	icon_SPACE->scale.y = icon_SPACE->imageSize.y * 1.4f;




	box_hp->Update();
	box_mp->Update();
	gauge_mp->Update();
	gauge_hp->Update();
	core_LBUTTON->Update();
	core_RBUTTON->Update();
	core_SPACE->Update();
	icon_mainWeapon->Update();
	icon_skillWeapon->Update();
	icon_dash->Update();
	icon_LBUTTON->Update();
	icon_RBUTTON->Update();
	icon_SPACE->Update();



	Vector2 textBox_hp_pos = Utility::WorldToScreen(box_hp->GetWorldPos());
	textBox_hp.left = textBox_hp_pos.x;
	textBox_hp.top = textBox_hp_pos.y - 70;
	textBox_hp.right = textBox_hp.left + 1000;
	textBox_hp.bottom = textBox_hp.top + 1000;

	Vector2 textBox_mp_pos = Utility::WorldToScreen(box_mp->GetWorldPos());
	textBox_mp.left = textBox_mp_pos.x + 140;
	textBox_mp.top = textBox_mp_pos.y - 40;
	textBox_mp.right = textBox_mp.left + 1000;
	textBox_mp.bottom = textBox_mp.top + 1000;

	Vector2 textBox_time_pos = Utility::WorldToScreen(Vector2(-app.GetHalfWidth(), app.GetHalfHeight()));
	textBox_time.left = textBox_time_pos.x + 20;
	textBox_time.top = textBox_time_pos.y + 10;
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
	core_LBUTTON->Update();
	core_RBUTTON->Update();
	core_SPACE->Update();
	icon_mainWeapon->Update();
	icon_skillWeapon->Update();
	icon_dash->Update();
	icon_LBUTTON->Update();
	icon_RBUTTON->Update();
	icon_SPACE->Update();

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
	icon_mainWeapon->Render();
	icon_skillWeapon->Render();
	icon_dash->Render();
	core_LBUTTON->Render();
	core_RBUTTON->Render();
	core_SPACE->Render();
	icon_LBUTTON->Render();
	icon_RBUTTON->Render();
	icon_SPACE->Render();

	// HP
	DWRITE->RenderText(
		to_wstring(GM->player->GetHp()) + L"/" + to_wstring(GM->player->GetMaxHp()),
		textBox_hp,
		35.0f,
		L"Commando",
		Color(1, 1, 1, 1),
		DWRITE_FONT_WEIGHT_ULTRA_LIGHT,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_ULTRA_EXPANDED);

	// 레벨
	DWRITE->RenderText(
		to_wstring(GM->player->GetMp()) + L"/" + to_wstring(GM->player->GetMaxMp()),
		textBox_mp,
		30.0f,
		L"Commando",
		Color(1, 1, 1, 1),
		DWRITE_FONT_WEIGHT_ULTRA_LIGHT,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_ULTRA_EXPANDED);

	// 시간
	DWRITE->RenderText(
		wstring(2 - to_wstring(minute).length(), L'0') + to_wstring(minute) + L":" + wstring(2 - to_wstring(second).length(), L'0') + to_wstring(second),
		textBox_time,
		25.0f,
		L"Commando",
		Color(0.7, 0.7, 0.7, 1),
		DWRITE_FONT_WEIGHT_ULTRA_LIGHT,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_ULTRA_EXPANDED);
}