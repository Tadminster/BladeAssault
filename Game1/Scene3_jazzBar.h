#pragma once
class Scene3_jazzBar : public Scene_proto
{
private:
	ObRect*			nextMap[2];
	ObRect*			stairLeft;
	ObRect*			stairRight;

	class npcBigmam*	npc_bigmam;
	class npcPianoman*	npc_pianoman;
	class npcSaxman*	npc_saxman;
	class npcDjang*		npc_djang;
	class npcMax*		npc_max;
	class npcJack*		npc_jack;
	class npcDarcy*		npc_darcy;
	class npcJenny*		npc_jenny;
	class npcZett*		npc_zett;

public:
	Scene3_jazzBar();
	~Scene3_jazzBar();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void SummonMonster() override;
};