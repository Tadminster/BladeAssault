#pragma once
class ratmotan : public Monster
{
private:
	ObImage* ui_frame_bossHp;
	ObImage* ui_gauge_bossHp;
	RECT textBox_bossName;

public:
	ratmotan();
	//ratmotan(Vector2 spawnPos);
	~ratmotan();
	void Update() override;
	void Render() override;
	void Attack() override;
};

