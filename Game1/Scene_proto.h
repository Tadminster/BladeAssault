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

	virtual void HandleTerrainCollision(class Creature* creature);
	virtual bool OnFloor(class Creature* creature);
	virtual bool OnWall(class Creature* creature);
	virtual bool OnWallside(class Creature* creature);

	// ���͸� ��ȯ
	virtual void SummonMonster();

	// @brief ���ڸ� ����
	// @param type ������ ������ ����
	// 0: ���� ����, 1: �Ϲ� ����, 2: ��� ����, 3: ���� ����
	// @param pos ������ ��ġ
	virtual void CreateChest(int type, Vector2 pos);

	// @brief ���� ������ �̵��ϱ��� Object���� ����
	virtual void CleanupBeforeNewMap();
};

