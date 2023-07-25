#pragma once
class GameManager : public Singleton<GameManager>
{
public:
    class Player*           player;
    class MonsterManager*   monster;
    class HUD*              hud;

    bool	DEBUG_MODE = false;

public:
    ~GameManager();

    void    Init();
    void    Release();
    void    Update();
    void    LateUpdate();
    void    Render();
    void    ResizeScreen();
};

