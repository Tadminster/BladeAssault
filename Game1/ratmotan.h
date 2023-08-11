#pragma once
class ratmotan : public Monster
{
private:
	ObImage* dash;
	ObImage* ui_frame_bossHp;
	ObImage* ui_gauge_bossHp;
	RECT textBox_bossName;
	

	float	lastJumpTime	{ 0.0f };		// 마지막 점프 시간
	float	jumpCooldown	{ 8.0f };		// 점프 쿨다운

	bool	realDashAttack	{ false };		// 대쉬 공격 여부
	float	lastDashTime	{ 0.0f };		// 마지막 점프 시간
	float	dashCooldown	{ 10.0f };		// 점프 쿨다운
	float   dashSpeed		{ 1500.0f };	// 대쉬 속도

public:
	ratmotan();
	~ratmotan();
	void Update() override;
	void Render() override;

	void Attack() override;
	void Shockwave();

	bool isDashColldown();
	void Dash();
	void DashAttack();
	void DashFinish();
	
	bool isJumpColldown();
	void Jump() override;


};

