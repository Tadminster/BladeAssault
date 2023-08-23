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

	// @brief	���� ��ȯ
	// @param monsterName ��ȯ�� ���� �̸�
	// "redHairRat", "orangeHairRat", "greenHairRat", "ratmotan", "shockwaveGenerator"
	// @param pos ��ȯ�� ��ġ
	void	SpawnMonster(string&& monsterName, Vector2 pos, Vector2 dir = LEFT);
	void	ClearMonster();

	void	ShowMonsterStat();
};

