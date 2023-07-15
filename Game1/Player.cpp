#include "stdafx.h"
#include "Player.h"

Player::Player()
{
  
    collider = new ObRect();
    idle = new ObImage(L"kill_onehand_idle.png");
    run = new ObImage(L"kill_onehand_run.png");
    jump = new ObImage(L"kill_onehand_jump.png");
    
    //hasAxis = true;
}

Player::~Player()
{
    delete idle;
    delete run;
    delete jump;

}

void Player::Init()
{
    collider->scale.x = 60;
    collider->scale.y = 100;
    collider->isFilled = false;

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

    state = PlayerState::IDLE;

    // 능력치
    speed       = 300.0f;
    jumpSpeed   = 700;
    jumpTime    = 0.0f;

    onFloor     = false;
}


void Player::Update()
{
    ImGui::Text("collider_y : %f\n", collider->GetWorldPos().y);
    ImGui::Text("jumpTime : %f\n", jumpTime);
    ImGui::Text("state : %d\n", state);

    lastPos = collider->GetWorldPos();
    collider->Update();

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

    // 중력
    if (!onFloor) 
        collider->MoveWorldPos(DOWN * DELTA * 250.f);

    // 상태 업데이트
    if (state == PlayerState::IDLE)
    {
        //idle > walk
        if (INPUT->KeyPress('A') || INPUT->KeyPress('D'))
        {
            state = PlayerState::RUN;
        }

        //idle > jump
        if (INPUT->KeyDown('W'))
        {
            state = PlayerState::JUMP;
        }
    }
    else if (state == PlayerState::RUN)
    {


        // 이동
        collider->MoveWorldPos(dir * speed * DELTA);

        // 상태전환
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
        collider->MoveWorldPos((UP + dir) * speed * DELTA);
    }

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

    }
    
    // 좌우이동
    if (INPUT->KeyPress('A')) dir = LEFT;
    else if (INPUT->KeyPress('D')) dir = RIGHT;
}

Vector2 Player::GetFoot()
{
    //29 38
    //Utility::RECT r(GetWorldPos()+ Vector2(0, 10), Vector2(15, 10));
    //Utility::IntersectRectRect()

    //                              중앙에서나갈위치    발중앙위치 보정
    return collider->GetWorldPos() + (dir+DOWN) * Vector2(collider->scale.x * 0.5f, collider->scale.y * 0.5f);
}

void Player::GoBack()
{
    collider->SetWorldPos(lastPos);
    collider->Update();
}