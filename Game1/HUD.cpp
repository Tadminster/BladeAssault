#include "stdafx.h"
#include "Creature.h"
#include "player.h"
#include "HUD.h"

#include <iomanip>
#include <sstream>

HUD::HUD()
{
	damageTaken = new ObImage(L"ui_player_damage_fx.png");

	box_hp = new ObImage(L"ui_frame_hp.png");
	box_mp = new ObImage(L"ui_frame_mp.png");

	gauge_hp = new ObImage(L"ui_gauge_hp.png");
	gauge_mp = new ObImage(L"ui_gauge_mp.png");

	frame_LBUTTON = new ObImage(L"ui_core_frame_normal.png");
	frame_RBUTTON = new ObImage(L"ui_core_frame_normal.png");
	frame_SPACE = new ObImage(L"ui_core_frame_normal.png");

	icon_LBUTTON = new ObImage(L"ui_keyboard_input_keys_defalut.png");
	icon_RBUTTON = new ObImage(L"ui_keyboard_input_keys_defalut.png");
	icon_SPACE = new ObImage(L"ui_keyboard_input_keys_defalut.png");

	icon_mainWeapon = new ObImage(L"playerattack_icon_kill_subweapon.png");
	icon_skillWeapon = new ObImage(L"playerattack_icon_kill_skill.png");
	icon_dash = new ObImage(L"playerattack_icon_kill_dash.png");

	damageTaken->space = SPACE::SCREEN;
	box_hp->space = SPACE::SCREEN;
	box_mp->space = SPACE::SCREEN;
	gauge_hp->space = SPACE::SCREEN;
	gauge_mp->space = SPACE::SCREEN;
	frame_LBUTTON->space = SPACE::SCREEN;
	frame_RBUTTON->space = SPACE::SCREEN;
	frame_SPACE->space = SPACE::SCREEN;
	icon_LBUTTON->space = SPACE::SCREEN;
	icon_RBUTTON->space = SPACE::SCREEN;
	icon_SPACE->space = SPACE::SCREEN;
	icon_mainWeapon->space = SPACE::SCREEN;
	icon_skillWeapon->space = SPACE::SCREEN;
	icon_dash->space = SPACE::SCREEN;

	damageTaken->pivot = OFFSET_LB;
	damageTaken->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));
	damageTaken->maxFrame.x = 1;
	damageTaken->maxFrame.y = 5;
	float damageTakenScaleX = app.GetWidth() / (damageTaken->imageSize.x / damageTaken->maxFrame.x);
	float damageTakenScaleY = app.GetHeight() / (damageTaken->imageSize.y / damageTaken->maxFrame.y);
	damageTaken->scale.x = (damageTaken->imageSize.x / damageTaken->maxFrame.x) * damageTakenScaleX;
	damageTaken->scale.y = (damageTaken->imageSize.y / damageTaken->maxFrame.y) * damageTakenScaleY;
	damageTaken->ChangeAnim(ANIMSTATE::ONCE, 0.1f, false);

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

	frame_LBUTTON->pivot = OFFSET_LB;
	frame_LBUTTON->SetWorldPos(Vector2(app.GetHalfWidth() * 0.55, -app.GetHalfHeight() * 0.95));
	frame_LBUTTON->scale.x = frame_LBUTTON->imageSize.x * 0.5;
	frame_LBUTTON->scale.y = frame_LBUTTON->imageSize.y * 0.5;

	frame_RBUTTON->pivot = OFFSET_LB;
	frame_RBUTTON->SetWorldPos(Vector2(app.GetHalfWidth() * 0.70, -app.GetHalfHeight() * 0.95));
	frame_RBUTTON->scale.x = frame_RBUTTON->imageSize.x * 0.5;
	frame_RBUTTON->scale.y = frame_RBUTTON->imageSize.y * 0.5;

	frame_SPACE->pivot = OFFSET_LB;
	frame_SPACE->SetWorldPos(Vector2(app.GetHalfWidth() * 0.85, -app.GetHalfHeight() * 0.95));
	frame_SPACE->scale.x = frame_SPACE->imageSize.x * 0.5;
	frame_SPACE->scale.y = frame_SPACE->imageSize.y * 0.5;

	icon_mainWeapon->SetParentRT(*frame_LBUTTON);
	icon_mainWeapon->pivot = OFFSET_LB;
	icon_mainWeapon->scale.x = icon_mainWeapon->imageSize.x * 0.5;
	icon_mainWeapon->scale.y = icon_mainWeapon->imageSize.y * 0.5;

	icon_skillWeapon->SetParentRT(*frame_RBUTTON);
	icon_skillWeapon->pivot = OFFSET_LB;
	icon_skillWeapon->scale.x = icon_skillWeapon->imageSize.x * 0.5;
	icon_skillWeapon->scale.y = icon_skillWeapon->imageSize.y * 0.5;

	icon_dash->SetParentRT(*frame_SPACE);
	icon_dash->pivot = OFFSET_LB;
	icon_dash->scale.x = icon_dash->imageSize.x * 0.5;
	icon_dash->scale.y = icon_dash->imageSize.y * 0.5;

	icon_LBUTTON->SetParentRT(*frame_LBUTTON);
	icon_LBUTTON->pivot = OFFSET_LB;
	icon_LBUTTON->maxFrame.x = 3;
	icon_LBUTTON->frame.x = 0;
	icon_LBUTTON->scale.x = icon_LBUTTON->imageSize.x / icon_LBUTTON->maxFrame.x * 1.4f;
	icon_LBUTTON->scale.y = icon_LBUTTON->imageSize.y * 1.4f;

	icon_RBUTTON->SetParentRT(*frame_RBUTTON);
	icon_RBUTTON->pivot = OFFSET_LB;
	icon_RBUTTON->maxFrame.x = 3;
	icon_RBUTTON->frame.x = 1;
	icon_RBUTTON->scale.x = icon_RBUTTON->imageSize.x / icon_LBUTTON->maxFrame.x * 1.4f;
	icon_RBUTTON->scale.y = icon_RBUTTON->imageSize.y * 1.4f;

	icon_SPACE->SetParentRT(*frame_SPACE);
	icon_SPACE->pivot = OFFSET_LB;
	icon_SPACE->maxFrame.x = 3;
	icon_SPACE->frame.x = 2;
	icon_SPACE->scale.x = icon_SPACE->imageSize.x / icon_LBUTTON->maxFrame.x * 1.4f;
	icon_SPACE->scale.y = icon_SPACE->imageSize.y * 1.4f;

	damageTaken->Update();
	box_hp->Update();
	box_mp->Update();
	gauge_mp->Update();
	gauge_hp->Update();
	frame_LBUTTON->Update();
	frame_RBUTTON->Update();
	frame_SPACE->Update();
	icon_mainWeapon->Update();
	icon_skillWeapon->Update();
	icon_dash->Update();
	icon_LBUTTON->Update();
	icon_RBUTTON->Update();
	icon_SPACE->Update();

	// hp
	Vector2 textBox_hp_pos = Utility::WorldToScreen(box_hp->GetWorldPos());
	textBox_hp.left = textBox_hp_pos.x;
	textBox_hp.top = textBox_hp_pos.y - 70;
	textBox_hp.right = textBox_hp.left + 1000;
	textBox_hp.bottom = textBox_hp.top + 1000;

	// mp
	Vector2 textBox_mp_pos = Utility::WorldToScreen(box_mp->GetWorldPos());
	textBox_mp.left = textBox_mp_pos.x + 140;
	textBox_mp.top = textBox_mp_pos.y - 40;
	textBox_mp.right = textBox_mp.left + 1000;
	textBox_mp.bottom = textBox_mp.top + 1000;

	// world time
	Vector2 textBox_time_pos = Utility::WorldToScreen(Vector2(-app.GetHalfWidth(), app.GetHalfHeight()));
	textBox_time.left = textBox_time_pos.x + 20;
	textBox_time.top = textBox_time_pos.y + 10;
	textBox_time.right = textBox_time.left + 1000;
	textBox_time.bottom = textBox_time.top + 1000;

	// colldown (skill)
	Vector2 textBox_cooltime_skill_pos = Utility::WorldToScreen(frame_RBUTTON->GetWorldPos());
	textBox_colldown_skill.left = textBox_cooltime_skill_pos.x + 15;
	textBox_colldown_skill.top = textBox_cooltime_skill_pos.y - 55;
	textBox_colldown_skill.right = textBox_colldown_skill.left + 1000;
	textBox_colldown_skill.bottom = textBox_colldown_skill.top + 1000;

	// colldown (dash)
	Vector2 textBox_cooltime_dash_pos = Utility::WorldToScreen(frame_SPACE->GetWorldPos());
	//Vector2 textBox_cooltime_dash_pos = frame_SPACE->GetWorldPos();
	textBox_colldown_dash.left = textBox_cooltime_dash_pos.x + 15;
	textBox_colldown_dash.top = textBox_cooltime_dash_pos.y - 55;
	textBox_colldown_dash.right = textBox_colldown_dash.left + 1000;
	textBox_colldown_dash.bottom = textBox_colldown_dash.top + 1000;
}

HUD::~HUD()
{
	delete damageTaken;
	delete box_hp;
	delete box_mp;
	delete gauge_hp;
	delete gauge_mp;
	delete frame_LBUTTON;
	delete frame_RBUTTON;
	delete frame_SPACE;
	delete icon_LBUTTON;
	delete icon_RBUTTON;
	delete icon_SPACE;
	delete icon_mainWeapon;
	delete icon_skillWeapon;
	delete icon_dash;

	TEXTURE->DeleteTexture(L"ui_player_damage_fx.png");
	TEXTURE->DeleteTexture(L"ui_frame_hp.png");
	TEXTURE->DeleteTexture(L"ui_frame_mp.png");
	TEXTURE->DeleteTexture(L"ui_gauge_hp.png");
	TEXTURE->DeleteTexture(L"ui_gauge_mp.png");
	TEXTURE->DeleteTexture(L"ui_core_frame_normal.png");
	TEXTURE->DeleteTexture(L"ui_keyboard_input_keys_defalut.png");
	TEXTURE->DeleteTexture(L"playerattack_icon_kill_subweapon.png");
	TEXTURE->DeleteTexture(L"playerattack_icon_kill_skill.png");
	TEXTURE->DeleteTexture(L"playerattack_icon_kill_dash.png");
}

void HUD::Init()
{
}

void HUD::Release()
{
}

void HUD::Update()
{
	// hp/mp 게이지 길이 계산
	gauge_hp->scale.x = gauge_hp->imageSize.x * ((float)GM->player->GetHp() / (float)GM->player->GetMaxHp());
	gauge_mp->scale.x = gauge_mp->imageSize.x * ((float)GM->player->GetMp() / (float)GM->player->GetMaxMp());

	// 데미지 받음 FX 출력이 끝났으면
	if (GM->player->damageTaken && damageTaken->frame.y == damageTaken->maxFrame.y - 1)
	{
		GM->player->damageTaken = false;
		damageTaken->frame.y = 0;
	}

	// DASH 쿨다운 중에 컬러 변경
	if (GM->player->GetDashCooldown() > 0.0f && icon_dash->color.x == 0.5f)
		icon_dash->color = Vector4(0.35f, 0.35f, 0.35f, 0.5f);
	else if (GM->player->GetDashCooldown() <= 0.0f && icon_dash->color.x != 0.5f)
		icon_dash->color = Vector4(0.5f, 0.5f, 0.5f, 0.5f);

	// SKILL 컬러 변경
	if ((GM->player->GetSkillCooldown() > 0.0f		// 스킬 쿨다운 중이거나
		|| !GM->player->hasEnoughManaForSkill())	// 마나가 부족하면
		&& icon_skillWeapon->color.x == 0.5f)
	{
		// 스킬 아이콘 어두워짐
		icon_skillWeapon->color = Vector4(0.25f, 0.25f, 0.25f, 0.5f);
	}
	else if (GM->player->GetSkillCooldown() <= 0.0f	// 스킬 쿨다운이 끝났고
		&& GM->player->hasEnoughManaForSkill()		// 마나가 충분하면
		&& icon_skillWeapon->color.x != 0.5f)
	{
		// 스킬 아이콘 밝아짐
		icon_skillWeapon->color = Vector4(0.5f, 0.5f, 0.5f, 0.5f);
	}

	damageTaken->Update();
	box_hp->Update();
	box_mp->Update();
	gauge_mp->Update();
	gauge_hp->Update();
	frame_LBUTTON->Update();
	frame_RBUTTON->Update();
	frame_SPACE->Update();
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
	if (GM->player->damageTaken)
		damageTaken->Render();

	box_hp->Render();
	box_mp->Render();
	gauge_hp->Render();
	gauge_mp->Render();
	icon_mainWeapon->Render();
	icon_skillWeapon->Render();
	icon_dash->Render();
	frame_LBUTTON->Render();
	frame_RBUTTON->Render();
	frame_SPACE->Render();
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

	// 쿨다운(skill)
	if (GM->player->GetSkillCooldown() > 0.0f)
	{
		int temp = GM->player->GetSkillCooldown() * 10;

		wstring skillCooldown;
		if (temp >= 10)
			skillCooldown = to_wstring(temp);
		else
			skillCooldown = L"0" + to_wstring(temp);

		DWRITE->RenderText(
			skillCooldown.substr(0, 1) + L"." + skillCooldown.substr(1, 1),
			textBox_colldown_skill,
			30.0f,
			L"Commando",
			Color(1, 1, 1, 1),
			DWRITE_FONT_WEIGHT_ULTRA_LIGHT,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_ULTRA_EXPANDED);
	}

	// 쿨다운(dash)
	if (GM->player->GetDashCooldown() > 0.0f)
	{
		int temp = GM->player->GetDashCooldown() * 10;

		wstring dashCooldown;
		if (temp >= 10)
			dashCooldown = to_wstring(temp);
		else
			dashCooldown = L"0" + to_wstring(temp);

		DWRITE->RenderText(
			dashCooldown.substr(0,1) + L"." + dashCooldown.substr(1,1),
			textBox_colldown_dash,
			30.0f,
			L"Commando",
			Color(1, 1, 1, 1),
			DWRITE_FONT_WEIGHT_ULTRA_LIGHT,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_ULTRA_EXPANDED);
	}
}