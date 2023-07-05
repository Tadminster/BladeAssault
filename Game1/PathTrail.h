#pragma once
class PathTrail
{
private:
	deque<ObRect*> pathLine;


public:
	PathTrail();
	~PathTrail();

	void Init();
	//void Release();
	void Update();
	//void LateUpdate();
	void Render();
	void Resize(int value, vector<Tile*>& way);
};

