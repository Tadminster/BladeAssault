#pragma once

class Main : public Scene
{
private:

	class Player* player;
	class Mutal* mutal;
	class PathTrail* pathTrail;
	ObTileMap* tileMap[2];


public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
