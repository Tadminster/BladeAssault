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

    // ��Ʈ��
    Control();

    // ��Ų ���� ����
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

    // ���� ������Ʈ
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
        // ����� ��, �ϰ��� �� ������
        if (gravity < 0)  jump->frame.y = 0;
        else
        {
            jump->frame.y = 1;

            if (onFloor)
            {
                state = PlayerState::IDLE;
            }
        }

        // �ٴڿ� ������

    }

    // �߷�
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

    // ����
    if (INPUT->KeyDown('W'))
    {
        collider->SetWorldPosY(collider->GetWorldPos().y + 5);
        gravity = -600;
    }

    // �¿��̵�
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

    //                              �߾ӿ���������ġ    ���߾���ġ ����
    return collider->GetWorldPos() + (dir + DOWN) * Vector2(collider->scale.x * 0.5f, collider->scale.y * 0.5f);
}

Vector2 Player::GetHead()
{
    //29 38
    //Utility::RECT r(GetWorldPos()+ Vector2(0, 10), Vector2(15, 10));
    //Utility::IntersectRectRect()

    //                              �߾ӿ���������ġ    ���߾���ġ ����
    return collider->GetWorldPos() + (dir + UP) * Vector2(collider->scale.x * 0.5f, collider->scale.y * 0.5f);
}

void Player::GoBack()
{
    collider->SetWorldPos(lastPos);
    collider->Update();
}