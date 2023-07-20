#pragma once

class MonsterManager
{
private:
	vector<class Monster*> enemy;
	vector<class Projectile*> projectiles;

public:
	~MonsterManager() {};

	void	Init();
	void	Release();
	void	Update();
	void	LateUpdate();
	void	Render();


	vector<class Monster*>&		GetEnemy()			{ return enemy; }
	vector<class Projectile*>&	GetProjectiles()	{ return projectiles; }
	int							getEnemyCount()		{ return enemy.size(); }

	void	AddMonster(Monster* monster);
};

