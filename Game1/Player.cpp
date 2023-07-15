#include "stdafx.h"
#include "Player.h"

Player::Player()
{
  
    collider = new ObRect();
    idle = new ObImage(L"kill_onehand_idle.png");
    run = new ObImage(L"kill_onehand_run.png");
    
    //hasAxis = true;
}

Player::~Player()
{
    delete idle;
    delete run;

}

void Player::Init(Vector2 spawn)
{
    collider->SetWorldPos(Vector2(spawn.x, spawn.y));
    collider->pivot = OFFSET_B;

    idle->SetParentRT(*collider);
    idle->maxFrame.x = 6;
    idle->maxFrame.y = 1;
    idle->scale.x = idle->imageSize.x / idle->maxFrame.x * 3;
    idle->scale.y = idle->imageSize.y / idle->maxFrame.y * 3;
    idle->pivot = OFFSET_B;
    idle->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

    run->SetParentRT(*collider);
    run->maxFrame.x = 8;
    run->maxFrame.y = 1;
    run->scale.x = run->imageSize.x / run->maxFrame.x * 3;
    run->scale.y = run->imageSize.y / run->maxFrame.y * 3;
    run->pivot = OFFSET_B;
    run->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

    state = PlayerState::IDLE;


    speed = 200.0f;
}

void Player::Control()
{
    dir = Vector2();
    //계속 누를때
    //if (INPUT->KeyPress('W'))
    //{
        //dir.y = 1.0f;
    //}
    //else if (INPUT->KeyPress('S'))
    //{
        //dir.y = -1.0f;
    //}
    if (INPUT->KeyPress('A'))
    {
        dir.x = -1.0f;
        idle->reverseLR = true;
        run->reverseLR = true;
    }
    else if (INPUT->KeyPress('D'))
    {
        dir.x = 1.0f;
        idle->reverseLR = false;
        run->reverseLR = false;
    }
    dir.Normalize();

    collider->MoveWorldPos(dir * DELTA * speed);
}

void Player::Update()
{
    lastPos = collider->GetWorldPos();
    //collider->Update();

    Control();

    if (state == PlayerState::IDLE)
    {
        LookTarget(INPUT->GetWorldMousePos());


        //idle ->walk
        if (INPUT->KeyPress('W') or INPUT->KeyPress('A')
            or INPUT->KeyPress('S') or INPUT->KeyPress('D'))
        {
            state = PlayerState::RUN;
        }
    }
    else if (state == PlayerState::RUN)
    {
        if (not(INPUT->KeyPress('W') or INPUT->KeyPress('A')
            or INPUT->KeyPress('S') or INPUT->KeyPress('D')))
        {
            state = PlayerState::IDLE;
            run->frame.x = 0;
        }
    }

    collider->Update();
    idle->Update();
    run->Update();
}

void Player::Render()
{
    if (GM->DEBUG_MODE) collider->Render();
    if (state == PlayerState::IDLE)
        idle->Render();
    else if (state == PlayerState::RUN)
        run->Render();
}

void Player::LookTarget(Vector2 target)
{

    //int index =
    //    round((Utility::DirToRadian(target - GetWorldPos()) + PI) / (45.0f * ToRadian));
    //if (index == 8)index = 0;

    //walk->frame.y = Frame[index];
    //roll->frame.y = Frame[index];
}

Vector2 Player::GetFoot()
{
    //29 38
/*Utility::RECT r(GetWorldPos()+ Vector2(0, 10), Vector2(15, 10));
Utility::IntersectRectRect()*/

//                              중앙에서나갈위치    발중앙위치 보정
    return collider->GetWorldPos() + dir * Vector2(15, 10) + Vector2(0, 10);
}

void Player::GoBack()
{
    collider->SetWorldPos(lastPos);
    Update();
}