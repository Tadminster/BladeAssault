#pragma once
class Scene4_armory : public Scene_proto
{
private:
	ObRect* nextMap;
	ObRect* previousMap;
	
	ObRect* stair;

	class npcHank*		npc_hank;
	class npcDoctor*	npc_doctor;

	Vector2			startPostion;
	Vector2			returnPosition;

public:
	Scene4_armory();
	~Scene4_armory();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};