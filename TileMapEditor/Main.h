#pragma once

class Main : public Scene
{
private:

	ObTileMap*	tileMap[3];
	Int2		tileSize[3];
	ObRect*		LineX, *LineY;

	int			brushImgIdx;
	Int2		brushFrame;
	int			brushState;
	Color		brushColor;
	int			layer;


public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
