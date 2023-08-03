#pragma once
class ItemManager
{
private:
	map<int, Item*> itemData;
	vector<class Item*>	dropItems;
	
	int gradeCriteria[4];
	int itemSize[4];

public:
	~ItemManager() {};

	void	Init();
	void	Release();
	void	Update();
	void	LateUpdate();
	void	Render();

	void	CreateItem(int itemGrade[3], Vector2 spawnPos);
	// ������ �߰�
	void	AddItem(class Item* item);

	// ���Ϳ� �ִ� ��� �������� ����
	void	ActivateAllItem();
};
