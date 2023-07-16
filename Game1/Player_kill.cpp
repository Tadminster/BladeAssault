#include "stdafx.h"
#include "Player.h"
#include "Player_Kill.h"

Player_kill::Player_kill()
{
    idle = new ObImage(L"kill_onehand_idle.png");
    run = new ObImage(L"kill_onehand_run.png");
    jump = new ObImage(L"kill_onehand_jump.png");

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

    jump->SetParentRT(*collider);
    jump->SetLocalPosY(20);
    jump->maxFrame.x = 2;
    jump->maxFrame.y = 2;
    jump->scale.x = jump->imageSize.x / jump->maxFrame.x * 3;
    jump->scale.y = jump->imageSize.y / jump->maxFrame.y * 3;
    jump->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

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