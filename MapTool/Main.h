#pragma once

class Main : public Scene
{
private:

	ObTileMap*	map;
	Int2		tileSize;
	ObRect*		LineX, *LineY;

	int			brushImgIdx;
	Int2		brushFrame;


public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
