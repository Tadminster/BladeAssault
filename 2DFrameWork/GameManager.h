#pragma once
class GameManager :public Singleton<GameManager>
{
private:
    bool	DEBUG_MODE = false;

public:
    ~GameManager();

    void    Release();
    void    Update();
    void    LateUpdate();
    void    Render();
    void    ResizeScreen();
};

