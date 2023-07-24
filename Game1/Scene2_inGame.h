#pragma once
class Scene2_inGame : public Scene_proto
{
private:
	//ObTileMap*		tileMap[3];
	ObImage*		lightCeiling;
	ObImage*		lightRoom;
	ObRect*			nextMap;

	bool			isLightDown;
	bool			isLightOn;
	float			LightOffTime;

	float			elapsedTime;

public:
	Scene2_inGame();
	~Scene2_inGame();
	void Init();
	void Release(); //해제
	void Update();
	void LateUpdate();//갱신
	void Render();
	void ResizeScreen();
	//void HandleTerrainCollision(class Creature* creature);

	//virtual bool OnFloor(class Creature* creature);
	//virtual bool OnWall(class Creature* creature);
	//virtual bool OnWallside(class Creature* creature);
};