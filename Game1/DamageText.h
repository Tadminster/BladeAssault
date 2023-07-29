#pragma once
class DamageText
{
private:
	ObImage* text;

	Vector2 spawnPos;
	string damage;
	float traveledDistance;
	float speed;
	float range;

public:
	// @brief ������ ǥ�� ������
	// @param spawnPos ������ ǥ�� ���� ��ġ
	// @param value ������ ǥ���� ��
	// @param value 0~9: �ش� ����, 10: ,(�޸�)
	// @param color ������ ǥ���� ����
	// @param color 0: ����, 1: ��Ȳ, 2: ���, 3: �ʷ�, 4: �Ķ�, 5: ����
	DamageText(Vector2 spawnPos, int value, int color);
	~DamageText();
	void	Init();
	void	Release();
	void	Update();
	void	LateUpdate();
	void	Render();

	// @brief ź�� �̵��� �Ÿ��� range�� �Ѿ����� Ȯ��
	bool                hasTraveledTooFar() const;
};

