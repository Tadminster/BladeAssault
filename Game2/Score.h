#pragma once
class Score
{

private:
	ObImage* top;
public:
	ObRect* col;
	bool        active;
	string	soundKey;
	Score();
	~Score();

	void Init(Vector2 spwan, bool active);
	void Update();
	void Render();
	float GetPosX() { return col->GetWorldPos().x; }
	void PlaySoundEffect();
};

