#include "stdafx.h"
#include "SoundDB.h"

SoundDB::SoundDB()
{
	// bgm
	SOUND->AddSound("bgm_title.ogg"					, "bgm_title"				, true);
	SOUND->AddSound("bgm_hankroom.ogg"				, "bgm_hankroom"			, true);
	SOUND->AddSound("bgm_jazzBar.ogg"				, "bgm_jazzBar"				, true);
	SOUND->AddSound("bgm_armory.ogg"				, "bgm_armory"				, true);
	SOUND->AddSound("bgm_undercity.ogg"				, "bgm_undercity"			, true);
	SOUND->AddSound("bgm_boss1.ogg"					, "bgm_boss1"				, true);
	SOUND->AddSound("bgm_boss2.ogg"					, "bgm_boss2"				, true);
	SOUND->AddSound("bgm_boss3.ogg"					, "bgm_boss3"				, true);

	// ui
	SOUND->AddSound("UI_move.wav"					, "UI_move"					, false);
	SOUND->AddSound("UI_select.wav"					, "UI_select"				, false);
	SOUND->AddSound("UI_error.wav"					, "UI_error"				, false);
	SOUND->AddSound("UI_purchase.wav"				, "UI_purchase"				, false);

	// player
	SOUND->AddSound("run1.wav"						, "run1"					, false);
	SOUND->AddSound("run2.wav"						, "run2"					, false);
	SOUND->AddSound("run3.wav"						, "run3"					, false);
	SOUND->AddSound("run4.wav"						, "run4"					, false);
	SOUND->AddSound("dash.wav"						, "dash"					, false);
	SOUND->AddSound("jumpToGround.wav"				, "jump"					, false);
	SOUND->AddSound("jumpToApex.wav"				, "doubleJump"				, false);
	SOUND->AddSound("crouchDown.wav"				, "crouchDown"				, false);
	SOUND->AddSound("damaged.wav"					, "damaged"					, false);

	// kill
	SOUND->AddSound("kill_attack.wav"				, "kill_attack"				, false);
	SOUND->AddSound("kill_attack_hit.wav"			, "kill_attack_hit"			, false);
	SOUND->AddSound("kill_skill.wav"				, "kill_skill"				, false);
	SOUND->AddSound("kill_skill_hit.wav"			, "kill_skill_hit"			, false);
	SOUND->AddSound("kill_chargeAttack.wav"			, "kill_chargeAttack"		, false);
	SOUND->AddSound("kill_chargeAttack_hit.wav"		, "kill_chargeAttack_hit"	, false);
	SOUND->AddSound("kill_charging.wav"				, "kill_charging"			, false);

	// Monster
	SOUND->AddSound("redHairRat_attack.wav"			, "redHairRat_attack"		, false); // rat
	SOUND->AddSound("orangeHairRat_attack.wav"		, "orangeHairRat_attack"	, false);
	SOUND->AddSound("greenHairRat_attack.wav"		, "greenHairRat_attack"		, false);
	SOUND->AddSound("rat_die.wav"					, "rat_die"					, false);

	SOUND->AddSound("ratmotan_shockwaveAttack.wav"	, "ratmotan_shockwaveAttack", false); // ratmotan
	SOUND->AddSound("ratmotan_dashAttack.wav"		, "ratmotan_dashAttack"		, false);
	SOUND->AddSound("ratmotan_dashCollision.wav"	, "ratmotan_dashCollision"	, false);
	SOUND->AddSound("ratmotan_jumpAttack.wav"		, "ratmotan_jumpAttack"		, false);
	SOUND->AddSound("ratmotan_jumpStart.wav"		, "ratmotan_jumpStart"		, false);
	SOUND->AddSound("ratmotan_die.wav"				, "ratmotan_die"			, false);

	// ETC
	SOUND->AddSound("gearBox_open.wav"				, "gearBox_open"			, false);

}

SoundDB::~SoundDB()
{
}

void SoundDB::Init()
{
	SOUND->SetVolume("bgm_hankroom"	, 0.5f);
	SOUND->SetVolume("bgm_jazzBar"	, 0.5f);
	SOUND->SetVolume("bgm_armory"	, 0.5f);
	SOUND->SetVolume("bgm_undercity", 0.5f);
	SOUND->SetVolume("bgm_boss1"	, 0.5f);
	SOUND->SetVolume("bgm_boss2"	, 0.5f);
	SOUND->SetVolume("bgm_boss3"	, 0.5f);
}

void SoundDB::Release()
{
}

void SoundDB::Update()
{
}

void SoundDB::LateUpdate()
{
}

void SoundDB::Render()
{
}
