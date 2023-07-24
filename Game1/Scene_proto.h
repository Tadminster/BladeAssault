#pragma once
class Scene_proto : public Scene
{
protected:
	ObTileMap*		tileMap[3];

	Vector2			startPostion;

public:
	Scene_proto();
	~Scene_proto();
	virtual void Init();
	virtual void Release();	//해제
	virtual void Update();
	virtual void LateUpdate();	//갱신
	virtual void Render();
	virtual void ResizeScreen();

	virtual void HandleTerrainCollision(class Creature* creature);
	virtual bool OnFloor(class Creature* creature);
	virtual bool OnWall(class Creature* creature);
	virtual bool OnWallside(class Creature* creature);
};

