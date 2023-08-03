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
	// 아이템 추가
	void	AddItem(class Item* item);

	// 벡터에 있는 모든 아이템을 삭제
	void	ActivateAllItem();
};
