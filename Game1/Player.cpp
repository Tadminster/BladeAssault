#include "stdafx.h"
#include "Player.h"

Player::Player()
{
  
    collider = new ObRect();
    idle = new ObImage(L"kill_onehand_idle.png");
    run = new ObImage(L"kill_onehand_run.png");
    
    //hasAxis = true;


    //walk_shadow = new ObImage(L"player_walk.png");
    //walk_shadow->maxFrame.x = 6;
    //walk_shadow->maxFrame.y = 8;
    //walk_shadow->scale.x = walk->imageSize.x / 6.0f * 3.0f;
    //walk_shadow->scale.y = walk->imageSize.y / 8.0f * 3.0f;
    //walk_shadow->pivot = OFFSET_B;
    //walk_shadow->color = Color(0, 0, 0,0.5);


    //roll = new ObImage(L"player_roll.png");
    //roll->maxFrame.x = 6;
    //roll->maxFrame.y = 8;
    //roll->scale.x = roll->imageSize.x / 6.0f * 3.0f;
    //roll->scale.y = roll->imageSize.y / 8.0f * 3.0f;
    //roll->pivot = OFFSET_B;

    //roll_shadow = new ObImage(L"player_roll.png");
    //roll_shadow->maxFrame.x = 6;
    //roll_shadow->maxFrame.y = 8;
    //roll_shadow->scale.x = roll->imageSize.x / 6.0f * 3.0f;
    //roll_shadow->scale.y = roll->imageSize.y / 8.0f * 3.0f;
    //roll_shadow->pivot = OFFSET_B;
    //roll_shadow->color = Color(0, 0, 0, 0.5);

    //this->pivot = OFFSET_B;

    //scale.x = walk->scale.x * 0.6f;
    //scale.y = walk->scale.y * 0.8f;

    //walk->SetParentRT(*this);
    //roll->SetParentRT(*this);
    //walk_shadow->SetParentRT(*this);
    //roll_shadow->SetParentRT(*this);
    //isFilled = false;


    //Frame[0] = 2;
    //Frame[1] = 5;
    //Frame[2] = 3;
    //Frame[3] = 4;
    //Frame[4] = 0;
    //Frame[5] = 7;
    //Frame[6] = 1;
    //Frame[7] = 6;
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
    idle->scale.x = idle->imageSize.x / idle->maxFrame.x * 2;
    idle->scale.y = idle->imageSize.y / idle->maxFrame.y * 2;
    idle->pivot = OFFSET_B;
    idle->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

    run->SetParentRT(*collider);
    run->maxFrame.x = 8;
    run->maxFrame.y = 1;
    run->scale.x = run->imageSize.x / run->maxFrame.x * 2;
    run->scale.y = run->imageSize.y / run->maxFrame.y * 2;
    run->pivot = OFFSET_B;
    run->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

    state = PlayerState::IDLE;


    speed = 200.0f;
    //roll_shadow->isVisible = roll->isVisible = false;
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
    }
    else if (INPUT->KeyPress('D'))
    {
        dir.x = 1.0f;
    }
    dir.Normalize();

    collider->MoveWorldPos(dir * DELTA * speed);
}

void Player::Update()
{
    //lastPos = GetWorldPos();
    //ObRect::Update();
    Control();

    if (state == PlayerState::IDLE)
    {
        LookTarget(INPUT->GetWorldMousePos());


        //idle ->walk
        if (INPUT->KeyPress('W') or INPUT->KeyPress('A')
            or INPUT->KeyPress('S') or INPUT->KeyPress('D'))
        {
            state = PlayerState::RUN;
            //walk->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
        }
    }
    else if (state == PlayerState::RUN)
    {
        //LookTarget(INPUT->GetWorldMousePos());
  
        //walk->idle
        if (not(INPUT->KeyPress('W') or INPUT->KeyPress('A')
            or INPUT->KeyPress('S') or INPUT->KeyPress('D')))
        {
            state = PlayerState::IDLE;
            //run->ChangeAnim(ANIMSTATE::STOP, 0.1f);
            run->frame.x = 0;
        }
    //    //walk->roll
    //    if (INPUT->KeyDown(VK_SPACE))
    //    {
    //        state = PlayerState::ROLL;
    //        roll->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
    //        roll_shadow->isVisible = roll->isVisible = true;
    //        walk_shadow-> isVisible= walk->isVisible = false;
    //        rollTime = 0.0f;
    //    }
    }
    //else if (state == PlayerState::ROLL)
    //{
    //    rollTime += DELTA;

    //    //0 ~ 1 * 180
    //    speed = (250.0f * rollTime / 0.6f * PI + 100.0f);

    //    MoveWorldPos(dir * DELTA * speed);
    //    LookTarget(GetWorldPos() + dir);
    //    //roll->idle
    //    if (roll->isAniStop())
    //    {
    //        speed = 200.0f;
    //        state = PlayerState::IDLE;
    //        walk->ChangeAnim(ANIMSTATE::STOP, 0.1f);
    //        roll_shadow->isVisible = roll->isVisible = false;
    //        walk_shadow->isVisible = walk->isVisible = true;
    //    }
    //}
    //walk->Update();
    //roll->Update();
    //roll_shadow->Update();
    //walk_shadow->Update();

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


    
    /*
    roll_shadow->frame = roll->frame;
    walk_shadow->frame = walk->frame;
    roll_shadow->Render();
    walk_shadow->Render();
    walk->Render();
    roll->Render();*/
  
  
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