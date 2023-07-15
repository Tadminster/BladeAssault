#pragma once
class Scene2_inGame : public Scene
{
private:
	ObTileMap*		tileMap[3];
	ObImage*		lightCeiling;
	ObImage*		lightRoom;

	bool			isLightDown;
	bool			isLightOn;
	float			LightOffTime;

	Vector2			startPostion;

public:
	Scene2_inGame();
	~Scene2_inGame();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};