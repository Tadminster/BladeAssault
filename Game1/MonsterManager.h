#pragma once

class MonsterManager
{
private:
	map<string, Monster*> monsterList;
	vector<class Monster*> monsters;
	vector<class Projectile*> projectiles;

public:
	~MonsterManager() {};

	void	Init();
	void	Release();
	void	Update();
	void	LateUpdate();
	void	Render();


	vector<class Monster*>&		GetEnemy()			{ return monsters; }
	vector<class Projectile*>&	GetProjectiles()	{ return projectiles; }
	int							getEnemyCount()		{ return monsters.size(); }

	// @brief	몬스터 소환
	// @param monsterName 소환할 몬스터 이름
	// "redHairRat", "orangeHairRat", "greenHairRat", "ratmotan", "shockwaveGenerator"
	// @param pos 소환할 위치
	void	SpawnMonster(string&& monsterName, Vector2 pos, Vector2 dir = LEFT);
	void	ClearMonster();

	void	ShowMonsterStat();
};

