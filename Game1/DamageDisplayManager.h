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

	void	AddText(Vector2 spawnPos, int value, int color = 0);
};

