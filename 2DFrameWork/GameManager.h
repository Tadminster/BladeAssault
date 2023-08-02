#pragma once
class GameManager : public Singleton<GameManager>
{
public:
    class HUD*                  hud;
    class Player*               player;
    class MonsterManager*       monster;
    class DamageDisplayManager* damageDP;
    class EffectManager*        fx;
    class ItemManager*          item;

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

