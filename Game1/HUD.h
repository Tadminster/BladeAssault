#pragma once
class HUD
{
private:


	class ObImage* box_hp;
	class ObImage* box_mp;
	class ObImage* gauge_hp;
	class ObImage* gauge_mp;

	class ObImage* frame_LBUTTON;
	class ObImage* frame_RBUTTON;
	class ObImage* frame_SPACE;
	class ObImage* icon_LBUTTON;
	class ObImage* icon_RBUTTON;
	class ObImage* icon_SPACE;
	class ObImage* icon_mainWeapon;
	class ObImage* icon_skillWeapon;
	class ObImage* icon_dash;

	RECT textBox_hp;
	RECT textBox_mp;
	RECT textBox_time;
	RECT textBox_colldown_skill;
	RECT textBox_colldown_dash;


	string fontFile;
	int minute, second;
	int score;

public:
	HUD();
	~HUD();
	void Init();
	void Release(); //해제
	void Update();
	void LateUpdate();//갱신
	void Render();
};

