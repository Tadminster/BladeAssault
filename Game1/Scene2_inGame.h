#pragma once
class Scene2_inGame : public Scene_proto
{
private:
	//ObTileMap*		tileMap[3];
	ObImage*		lightCeiling;
	ObImage*		lightRoom;
	ObRect*			nextMap;

	class Chest*			chest;

	bool			isLightDown;
	bool			isLightOn;
	float			LightOffTime;

	float			elapsedTime;

public:
	Scene2_inGame();
	~Scene2_inGame();
	void Init();
	void Release(); //����
	void Update();
	void LateUpdate();//����
	void Render();
	void ResizeScreen();
};