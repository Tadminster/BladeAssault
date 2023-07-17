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
	Vector2			floorPostion;

	float			elapsedTime;

public:
	Scene2_inGame();
	~Scene2_inGame();
	void Init() override;
	void Release() override; //해제
	void Update() override;
	void LateUpdate() override;//갱신
	void Render() override;
	void ResizeScreen() override;

	virtual bool OnFloor();
	virtual bool OnWall();
};