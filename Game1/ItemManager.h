#pragma once
class ItemManager
{
private:
	vector<class Item*>	dropItems;

public:
	~ItemManager() {};

	void	Init();
	void	Release();
	void	Update();
	void	LateUpdate();
	void	Render();

	// 아이템 추가
	void	AddItem(class Item* item);

	// 벡터에 있는 모든 아이템을 삭제
	void	ActivateAllItem();
};
