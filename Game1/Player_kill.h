#pragma once


class Player_kill : public Player
{
private:
	class ObImage* chargingFx;

public:
	Player_kill();
	//~Player_kill() override;
	//void Init() override;
	void Update() override;
	void Render() override;
	void Attack() override;
	void ChargingAttack() override;
};