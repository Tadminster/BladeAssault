#pragma once
class ObjectManager
{
private:
	vector<class Chest*> chests;

public:
	~ObjectManager() {};

	void	Init();
	void	Release();
	void	Update();
	void	LateUpdate();
	void	Render();

	void AddChest(Chest* chest);
	void ClearChests();
};

