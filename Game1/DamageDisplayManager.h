#pragma once
class DamageDisplayManager
{
private:
	ObImage* text;
	vector<class DamageText*> texts;

public:
	~DamageDisplayManager() {};
	void	Init();
	void	Release();
	void	Update();
	void	LateUpdate();
	void	Render();

	// @brief ������ ǥ�� ������
	// @param spawnPos ������ ǥ�� ���� ��ġ
	// @param value ������ ǥ���� �� 0~9: number, 10: comma
	// @param color ������ ǥ���� ���� 0: white, 1: solid red, 2: red, 3: sky, 4: puple, 5: green 6: yellow
	// @exception param value�� 0~10�� �ƴ� ��� 0���� �ʱ�ȭ
	// @exception param color�� 0~6�� �ƴ� ��� 0���� �ʱ�ȭ
	void	AddText(Vector2 spawnPos, int value, int color = 0);
};
