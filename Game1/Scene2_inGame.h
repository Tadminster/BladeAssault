#pragma once
class Scene2_inGame : public Scene
{
private:
	ObTileMap*		tileMap[3];
	ObImage*		lightCeiling;
	ObImage*		lightRoom;

	ObRect*			nextMap;

	bool			isLightDown;
	bool			isLightOn;
	float			LightOffTime;


	Vector2			startPostion;
	float			elapsedTime;

public:
	Scene2_inGame();
	~Scene2_inGame();
	void Init() override;
	void Release() override; //����
	void Update() override;
	void LateUpdate() override;//����
	void Render() override;
	void ResizeScreen() override;

	virtual bool OnFloor();
	virtual bool OnWall();
	virtual bool OnWallside();
};