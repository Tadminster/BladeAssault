#pragma once
class kill_barehand_skill : public Projectile
{
private:
	//class ObCircle* explosionCol;

public:
	kill_barehand_skill(
		float scale,
		Vector2 spawnPos,
		Vector2 dir,
		float speed,
		float range,
		float damage,
		int penetration,
		float explosionRange,
		int critical = 0);

	~kill_barehand_skill();
	void Update() override;
	void Render() override;
	void AfterEffect() override;
};

