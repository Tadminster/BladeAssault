#pragma once
class EffectManager
{
private:
	vector<class ObImage*>	effects;

public:
	~EffectManager() {};

	void	Init();
	void	Release();
	void	Update();
	void	LateUpdate();
	void	Render();

	void	AddEffects(ObImage* image);
};

