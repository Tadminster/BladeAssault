#pragma once
class Scene3_jazzBar : public Scene
{
private:
	ObTileMap*		tileMap[3];
	
	ObRect*			nextMap[2];
	ObRect*			stairLeft;
	ObRect*			stairRight;

	Vector2			startPostion;

	//temp
	class redHairRat*		redRat;

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
	virtual bool OnWallside();
};