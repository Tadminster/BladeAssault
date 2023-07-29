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
	// @param value ������ ǥ���� �� 0~9: number, 10: comma
	// @param color ������ ǥ���� ���� 0: white, 1: solid red, 2: red, 3: sky, 4: puple, 5: green 6: yellow
	// @exception param value�� 0~10�� �ƴ� ��� 0���� �ʱ�ȭ
	// @exception param color�� 0~6�� �ƴ� ��� 0���� �ʱ�ȭ
	DamageText(Vector2 spawnPos, int value, int color = 0);
	~DamageText();
	void	Init();
	void	Release();
	void	Update();
	void	LateUpdate();
	void	Render();

	// @brief ź�� �̵��� �Ÿ��� range�� �Ѿ����� Ȯ��
	bool                hasTraveledTooFar() const;
};

