#pragma once
class HUD
{
private:


	class ObImage* box_hp;
	class ObImage* box_mp;
	class ObImage* gauge_hp;
	class ObImage* gauge_mp;

	RECT textBox_hp;
	RECT textBox_mp;
	RECT textBox_time;

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

