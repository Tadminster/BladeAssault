#pragma once
class commonChest : public Chest
{
private:

public:
	commonChest();
	//~commonChest() override;

	void Init() override;
	//void Update() override;
	//void Render() override;
	void CreateItem() override;
};

