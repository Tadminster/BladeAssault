#include "stdafx.h"
#include "Monster.h"
#include "redHairRat.h"

redHairRat::redHairRat(Vector2 spawnPos)
{
	idle = new ObImage(L"redHairRat_idle.png");
	run = new ObImage(L"redHairRat_run.png");
	jump = new ObImage(L"redHairRat_jump.png");
	attack = new ObImage(L"redHairRat_attack.png");

    collider->isFilled = false;
    collider->scale.x = 80;
    collider->scale.y = 110;
    collider->SetWorldPos(spawnPos);

    idle->SetParentRT(*collider);
    idle->SetLocalPosY(45);
    idle->maxFrame.x = 9;
    idle->maxFrame.y = 1;
    idle->scale.x = idle->imageSize.x / idle->maxFrame.x * 3;
    idle->scale.y = idle->imageSize.y / idle->maxFrame.y * 3;
    idle->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

    run->SetParentRT(*collider);
    run->SetLocalPosY(45);
    run->maxFrame.x = 7;
    run->maxFrame.y = 1;
    run->scale.x = run->imageSize.x / run->maxFrame.x * 3;
    run->scale.y = run->imageSize.y / run->maxFrame.y * 3;
    run->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

    jump->SetParentRT(*collider);
    jump->SetLocalPosY(45);
    jump->maxFrame.x = 2;
    jump->maxFrame.y = 2;
    jump->scale.x = jump->imageSize.x / jump->maxFrame.x * 3;
    jump->scale.y = jump->imageSize.y / jump->maxFrame.y * 3;
    jump->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

    attack->SetParentRT(*collider);
    attack->SetLocalPosY(45);
    attack->maxFrame.x = 9;
    attack->maxFrame.y = 1;
    attack->scale.x = attack->imageSize.x / attack->maxFrame.x * 3;
    attack->scale.y = attack->imageSize.y / attack->maxFrame.y * 3;
    attack->ChangeAnim(ANIMSTATE::ONCE, 0.1f, true);

    state = MonsterState::IDLE;
    dir = LEFT;

    hp = 100;
    damage = 10;
    speed = 100;
    attackSpeed = 0.3f;
}

redHairRat::~redHairRat()
{
	Monster::~Monster();
}

void redHairRat::Init(Vector2 spawnPos)
{
	collider->isFilled = false;
	collider->scale.x = 60;
	collider->scale.y = 100;
    collider->SetWorldPos(spawnPos);

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

    attack->SetParentRT(*collider);
    attack->SetLocalPosY(20);
    attack->maxFrame.x = 4;
    attack->maxFrame.y = 1;
    attack->scale.x = attack->imageSize.x / attack->maxFrame.x * 3;
    attack->scale.y = attack->imageSize.y / attack->maxFrame.y * 3;
    attack->ChangeAnim(ANIMSTATE::ONCE, 0.3f, true);

    state = MonsterState::IDLE;
    dir = LEFT;

    hp = 100;
    damage = 10;
    speed = 100;
    attackSpeed = 1.0f;

}

void redHairRat::Update()
{
	Monster::Update();
}

void redHairRat::Render()
{
	Monster::Render();
}

void redHairRat::Attack()
{
    static float lastShotTime = 0;
    static float timeSinceLastTime = 0;

    float currentTime = TIMER->GetWorldTime();
    float elapsedTime = currentTime - lastShotTime;

    if (elapsedTime >= timeSinceLastTime)
    {
        Monster::Attack();
        cout << "redHairRat Attack" << endl;

        // 발사 위치 계산
        Vector2 spawnPos = collider->GetWorldPos();

        // 탄생성
        //kill_barehand_atk* proj = new kill_barehand_atk
        //(
        //	spawnPos,										// 생성위치
        //	lastDir,										// 각도
        //	700,											// 발사체 속도
        //	500,											// 사거리
        //	10,												// 공격력
        //	1,												// 관통력
        //	1												// 폭발범위
        //);

        //벡터에 탄 push
        //projectiles.emplace_back(proj);

        // 공속계산
        lastShotTime = currentTime;
        timeSinceLastTime = 1.0f / attackSpeed;
    }
}
