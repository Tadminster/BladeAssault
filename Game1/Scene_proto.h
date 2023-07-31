#pragma once
class Scene_proto : public Scene
{
protected:
	ObTileMap*		tileMap[3];
	ObRect*			spawnTrigger;

	Vector2			startPostion;
	float			localtime = 0;

	// 몬스터를 소환한 적이 있는지 체크
	bool			isSummoned{ false };

public:
	Scene_proto();
	~Scene_proto();
	virtual void Init();
	virtual void Release();		//해제
	virtual void Update();
	virtual void LateUpdate();	//갱신
	virtual void Render();
	virtual void ResizeScreen();

	virtual void HandleTerrainCollision(class Creature* creature);
	virtual bool OnFloor(class Creature* creature);
	virtual bool OnWall(class Creature* creature);
	virtual bool OnWallside(class Creature* creature);

	// 몬스터를 소환
	virtual void SummonMonster();
};

