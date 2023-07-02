#pragma once
class Bono
{
private:
	ObImage*	top;
public:
	ObRect*		col;
	bool        active;
	Bono();
	~Bono();

	void Init(Vector2 spwan,bool active);
	void Update();
	void Render();
	float GetPosX() { return col->GetWorldPos().x; }


};

