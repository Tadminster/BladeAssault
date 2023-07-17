#pragma once
class Scene3_jazzBar : public Scene
{
private:
	ObTileMap* tileMap[3];
	ObImage* lightCeiling;
	ObImage* lightRoom;

	bool			isLightDown;
	bool			isLightOn;
	float			LightOffTime;

	Vector2			startPostion;
	Vector2			floorPostion;

public:
	Scene3_jazzBar();
	~Scene3_jazzBar();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;

	virtual bool OnFloor();
	virtual bool OnWall();
};