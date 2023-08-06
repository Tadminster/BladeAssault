#pragma once

class MonsterManager
{
private:
	map<string, Monster*> monsterList;
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

	void	SpawnMonster(class Monster* monster, Vector2 pos);
	void	ClearMonster() { enemy.clear(); }

	void	ShowMonsterStat();
};

