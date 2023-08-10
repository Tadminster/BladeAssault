#pragma once
class ratmotan_dashAtk : public Projectile
{
private:
	//class ObCircle* explosionCol;

public:
	ratmotan_dashAtk(
		Vector2 spawnPos,
		Vector2 dir,
		float speed,
		float range,
		float damage,
		int penetration,
		float explosionRange);

	void Update() override;
	void Render() override;
	void AfterEffect() override;
};

