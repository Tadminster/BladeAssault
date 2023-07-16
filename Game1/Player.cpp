#include "stdafx.h"
#include "Player.h"

Player::Player()
{
    collider = new ObRect();
    idle = nullptr;
    run = nullptr;
    jump = nullptr;
}

Player::~Player()
{
    delete collider;
    delete idle;
    delete run;
    delete jump;
}

void Player::Init()
{
    state = PlayerState::IDLE;

    speed = 300.0f;
    jumpSpeed = 700;
    jumpTime = 0.0f;

    gravity = 0.0f;
    onFloor = false;

}

void Player::Update()
{
    lastPos = collider->GetWorldPos();
    collider->Update();

    // 컨트롤
    Control();

    // 스킨 방향 설정
    if (dir == LEFT)
    {
        idle->reverseLR = true;
        run->reverseLR = true;
        jump->reverseLR = true;
    }
    else if (dir == RIGHT)
    {
        idle->reverseLR = false;
        run->reverseLR = false;
        jump->reverseLR = false;
    }

    // 상태 업데이트
    if (state == PlayerState::IDLE)
    {
        // idle > walk
        if (INPUT->KeyPress('A') || INPUT->KeyPress('D'))
        {
            state = PlayerState::RUN;
        }

        // idle > jump
        if (INPUT->KeyDown('W'))
        {
            state = PlayerState::JUMP;
        }
    }
    else if (state == PlayerState::RUN)
    {
        // run -> idle
        if (!(INPUT->KeyPress('A') || INPUT->KeyPress('D')))
        {
            state = PlayerState::IDLE;
            run->frame.x = 0;
        }

        // run -> jump
        if (INPUT->KeyDown('W'))
        {
            state = PlayerState::JUMP;
        }
    }
    else if (state == PlayerState::JUMP)
    {
        // 상승할 때, 하강할 때 프레임
        if (gravity < 0)  jump->frame.y = 0;
        else
        {
            jump->frame.y = 1;

            if (onFloor)
            {
                state = PlayerState::IDLE;
            }
        }

        // 바닥에 닿으면

    }

    // 중력
    if (!onFloor) gravity += 600.0f * DELTA;
    collider->MoveWorldPos(DOWN * gravity * DELTA);

    collider->Update();
    idle->Update();
    run->Update();
    jump->Update();
}

void Player::Render()
{
    if (GM->DEBUG_MODE)
        collider->Render();

    if (state == PlayerState::IDLE)
        idle->Render();
    else if (state == PlayerState::RUN)
        run->Render();
    else if (state == PlayerState::JUMP)
        jump->Render();
}



void Player::Control()
{
    dir = Vector2();

    // 점프
    if (INPUT->KeyDown('W'))
    {
        collider->SetWorldPosY(collider->GetWorldPos().y + 5);
        gravity = -600;
    }

    // 좌우이동
    if (INPUT->KeyPress('A')) dir = LEFT;
    else if (INPUT->KeyPress('D')) dir = RIGHT;

    collider->MoveWorldPos(dir * speed * DELTA);
}

void Player::OnFloorAction()
{
    onFloor = true;
    gravity = 0;
    //GoBack();
    //collider->Update();

}

Vector2 Player::GetFoot()
{
    //29 38
    //Utility::RECT r(GetWorldPos()+ Vector2(0, 10), Vector2(15, 10));
    //Utility::IntersectRectRect()

    //                              중앙에서나갈위치    발중앙위치 보정
    return collider->GetWorldPos() + (dir + DOWN) * Vector2(collider->scale.x * 0.5f, collider->scale.y * 0.5f);
}

Vector2 Player::GetHead()
{
    //29 38
    //Utility::RECT r(GetWorldPos()+ Vector2(0, 10), Vector2(15, 10));
    //Utility::IntersectRectRect()

    //                              중앙에서나갈위치    발중앙위치 보정
    return collider->GetWorldPos() + (dir + UP) * Vector2(collider->scale.x * 0.5f, collider->scale.y * 0.5f);
}

void Player::GoBack()
{
    collider->SetWorldPos(lastPos);
    collider->Update();
}