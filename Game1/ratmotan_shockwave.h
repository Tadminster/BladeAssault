#pragma once
class ratmotan_shockwave : public Projectile
{
private:
	float gravity;

public:
	ratmotan_shockwave(
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

