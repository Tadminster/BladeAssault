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

	// ������ �߰�
	void	AddItem(class Item* item);

	// ���Ϳ� �ִ� ��� �������� ����
	void	ActivateAllItem();
};
