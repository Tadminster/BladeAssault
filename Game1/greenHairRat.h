#pragma once
class greenHairRat : public Monster
{
private:

public:
	greenHairRat();
	~greenHairRat();
	void Update() override;
	void Render() override;
	void Attack() override;
};

