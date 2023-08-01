#pragma once
class commonChest : public Chest
{
private:

public:
	commonChest();
	~commonChest();

	void Init() override;
	//void Update() override;
	//void Render() override;
	void Open() override;
	void Spawn() override;
};

