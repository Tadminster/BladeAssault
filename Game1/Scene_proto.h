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

	void HandleTerrainCollision(class Creature* creature);
	bool OnFloor(class Creature* creature);
	bool OnWall(class Creature* creature);
	bool OnWallside(class Creature* creature);

	// 몬스터를 소환
	virtual void SummonMonster();

	// @brief 상자를 생성
	// @param type 생성할 상자의 종류
	// 0: 랜덤 상자, 1: common chest, 2: uncommon chest, 3: rare chest
	// @param pos 생성할 위치
	void CreateChest(int type, Vector2 pos);

	// @brief 다음 맵으로 이동하기전 Object들을 정리
	void CleanupBeforeNewMap();
};

