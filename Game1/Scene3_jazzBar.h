#pragma once
class Scene3_jazzBar : public Scene
{
private:
	ObTileMap*		tileMap[3];
	ObImage*		lightCeiling;
	ObImage*		lightRoom;

	ObRect*			nextMap[2];
	ObRect*			stairLeft;
	ObRect*			stairRight;

	bool			isLightDown;
	bool			isLightOn;
	float			LightOffTime;

	Vector2			startPostion;

	//temp
	class redHairRat*		redRat;

public:
	Scene3_jazzBar();
	~Scene3_jazzBar();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;

	virtual bool OnFloor();
	virtual bool OnWall();
	virtual bool OnWallside();
};