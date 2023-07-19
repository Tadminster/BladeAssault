#include "stdafx.h"
#include "Player.h"
#include "Player_Kill.h"

Player_kill::Player_kill()
{
    idle = new ObImage(L"kill_barehand_idle.png");
    run = new ObImage(L"kill_barehand_run.png");
    dash = new ObImage(L"kill_barehand_dash.png");
    jump = new ObImage(L"kill_barehand_jump.png");
    crouch = new ObImage(L"kill_barehand_crouch.png");
    //hasAxis = true;
}

Player_kill::~Player_kill()
{
    Player::~Player();
}

void Player_kill::Init()
{
    collider->isFilled = false;
    collider->scale.x = 60;
    collider->scale.y = 100;

    idle->SetParentRT(*collider);
    idle->SetLocalPosY(20);
    idle->maxFrame.x = 6;
    idle->maxFrame.y = 1;
    idle->scale.x = idle->imageSize.x / idle->maxFrame.x * 3;
    idle->scale.y = idle->imageSize.y / idle->maxFrame.y * 3;
    idle->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

    run->SetParentRT(*collider);
    run->SetLocalPosY(20);
    run->maxFrame.x = 8;
    run->maxFrame.y = 1;
    run->scale.x = run->imageSize.x / run->maxFrame.x * 3;
    run->scale.y = run->imageSize.y / run->maxFrame.y * 3;
    run->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

    dash->SetParentRT(*collider);
    dash->SetLocalPosY(20);
    dash->maxFrame.x = 5;
    dash->maxFrame.y = 1;
    dash->scale.x = dash->imageSize.x / dash->maxFrame.x * 3;
    dash->scale.y = dash->imageSize.y / dash->maxFrame.y * 3;
    dash->ChangeAnim(ANIMSTATE::ONCE, 0.1f, true);

    jump->SetParentRT(*collider);
    jump->SetLocalPosY(20);
    jump->maxFrame.x = 2;
    jump->maxFrame.y = 2;
    jump->scale.x = jump->imageSize.x / jump->maxFrame.x * 3;
    jump->scale.y = jump->imageSize.y / jump->maxFrame.y * 3;
    jump->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

    crouch->SetParentRT(*collider);
    crouch->SetLocalPosY(20);
    crouch->maxFrame.x = 6;
    crouch->maxFrame.y = 1;
    crouch->scale.x = crouch->imageSize.x / crouch->maxFrame.x * 3;
    crouch->scale.y = crouch->imageSize.y / crouch->maxFrame.y * 3;
    crouch->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

    // ´É·ÂÄ¡
    Player::Init();
}


void Player_kill::Update()
{
    Player::Update();
}

void Player_kill::Render()
{
    Player::Render();
}