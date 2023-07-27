#pragma once


class Player_kill : public Player
{
private:
	class ObImage* chargingFx;

	bool			isSkill1;
	bool			isSkill2;
	bool			isSkill3;

public:
	Player_kill();
	//~Player_kill() override;
	//void Init() override;
	void Update() override;
	void Render() override;
	void Attack() override;
	void ChargingAttack() override;
	void Skill() override;
	void SkillAttack() override;
};