#pragma once
class Scene2_inGame : public Scene
{
private:
	class Player* player;
	class Mutal* mutal;
	class PathTrail* pathTrail;
	ObTileMap* tileMap[2];

public:
	Scene2_inGame();
	~Scene2_inGame();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};