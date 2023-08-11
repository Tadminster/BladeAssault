#pragma once
class ratmotan : public Monster
{
private:
	ObImage* dash;
	ObImage* ui_frame_bossHp;
	ObImage* ui_gauge_bossHp;
	RECT textBox_bossName;
	

	float	lastJumpTime	{ 0.0f };		// ������ ���� �ð�
	float	jumpCooldown	{ 8.0f };		// ���� ��ٿ�

	bool	realDashAttack	{ false };		// �뽬 ���� ����
	float	lastDashTime	{ 0.0f };		// ������ ���� �ð�
	float	dashCooldown	{ 10.0f };		// ���� ��ٿ�
	float   dashSpeed		{ 1500.0f };	// �뽬 �ӵ�

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

