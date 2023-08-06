#pragma once
class Scene_proto : public Scene
{
protected:
	ObTileMap*		tileMap[3];
	ObRect*			spawnTrigger;

	Vector2			startPostion;
	float			localtime = 0;

	// ���͸� ��ȯ�� ���� �ִ��� üũ
	bool			isSummoned{ false };

public:
	Scene_proto();
	~Scene_proto();
	virtual void Init();
	virtual void Release();		//����
	virtual void Update();
	virtual void LateUpdate();	//����
	virtual void Render();
	virtual void ResizeScreen();

	void HandleTerrainCollision(class Creature* creature);
	bool OnFloor(class Creature* creature);
	bool OnWall(class Creature* creature);
	bool OnWallside(class Creature* creature);

	// ���͸� ��ȯ
	virtual void SummonMonster();

	// @brief ���ڸ� ����
	// @param type ������ ������ ����
	// 0: ���� ����, 1: common chest, 2: uncommon chest, 3: rare chest
	// @param pos ������ ��ġ
	void CreateChest(int type, Vector2 pos);

	// @brief ���� ������ �̵��ϱ��� Object���� ����
	void CleanupBeforeNewMap();
};

