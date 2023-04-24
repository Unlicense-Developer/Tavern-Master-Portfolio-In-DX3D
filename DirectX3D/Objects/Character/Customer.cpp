#include "Framework.h"

Customer::Customer(Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
    : transform(transform), instancing(instancing), index(index)
{
    //root = new Transform();

    motion = instancing->GetMotion(index);
    totalEvent.resize(instancing->GetClipSize());
    eventIters.resize(instancing->GetClipSize());

    SetEvent(SIT, bind(&Customer::PlayEndEvent, this), 0.9f);
    SetEvent(ORDER, bind(&Customer::PlayEndEvent, this));
    SetEvent(DRINK, bind(&Customer::PlayEndEvent, this));
    SetEvent(STAND, bind(&Customer::PlayEndEvent, this), 0.9f);

    FOR(totalEvent.size())
    {
        eventIters[i] = totalEvent[i].begin();
    }

    rightHand = new Transform();

    tankard = new Model("Tankard_Foam");
    tankard->SetTag("Tankard_Customer");
    tankard->SetParent(rightHand);
    tankard->Load();

    payGold = new Quad(L"Textures/UI/PayGold.png");
    payGold->SetActive(false);
}

Customer::~Customer()
{
    delete tankard;
    delete rightHand;
    delete payGold;
}

void Customer::Update()
{
    if (!transform->Active()) return;

    ExcuteEvent();

    Move();
    Rotate();
    Remove();
    Sit();
    Order();
    Drink();
    Stand();

    rightHand->SetWorld(instancing->GetTransformByNode(index, 38));

    tankard->UpdateWorld();
    UpdatePayGold();
}

void Customer::Render()
{
    if (curState == DRINK)
        tankard->Render();
}

void Customer::PostRender()
{
    if (CAM->ContainPoint(transform->GlobalPos(), -5.0f) && payGold->Active() && isOrdered)
    {
        PrintPayGold();
        payGold->Render();
    }
}

void Customer::GUIRender()
{
    if (curState == DRINK)
        tankard->GUIRender();
}

void Customer::Spawn()
{
    if (way == Way::UP)
    {
        transform->Pos() = DOWN_START;
        destPos = UP_START;
    }
    else if (way == Way::DOWN)
    {
        transform->Pos() = UP_START;
        destPos = DOWN_START;
    }
    else if (way == Way::TAVERN)
    {
        int random = Random(0, 2);

        if(random == 0)
            transform->Pos() = DOWN_START;
        else if (random == 1)
            transform->Pos() = UP_START;

        destPos = TavernManager::Get()->GetRandomChairPos(chairIndex);

        if (destPos == Vector3())
        {
            if (random == 0)
            {
                way = UP;
                destPos = UP_START;
            }
            else if (random == 1)
            {
                way = DOWN;
                destPos = DOWN_START;
            }
        }
    }

    transform->SetActive(true);
    transform->UpdateWorld();

    SetDestination();
}

void Customer::SetDestination() // 목적지 설정 후, 지나갈 길을 path에 입력
{
    int start = PathManager::Get()->GetAStar()->FindCloseNode(transform->GlobalPos());
    int end = PathManager::Get()->GetAStar()->FindCloseNode(destPos);

    PathManager::Get()->GetAStar()->GetPath(start, end, path);
}

void Customer::UpdatePayGold()
{
    if (!payGold->Active() && payGold_YValue == 0.0f)
    {
        if (TavernManager::Get()->GetIsDelivered(chairIndex))
            payGold->SetActive(true);
        else
            return;
    }

    payGold_YValue += DELTA;

    if (payGold_YValue > 1.0f)
    {
        payGold->SetActive(false);
        return;
    }

    payGoldPos = transform->Pos() + Vector3(0, payGold_YValue, 0);

    payGold->Pos() = CAM->WorldToScreen(payGoldPos);
    payGold->UpdateWorld();
}

void Customer::SetEvent(int clip, Event event, float timeRatio)
{
    if (totalEvent[clip].count(timeRatio) > 0)
        return;

    totalEvent[clip][timeRatio] = event;
}

void Customer::ExcuteEvent()
{
    int index = curState;

    if (totalEvent[index].empty()) return;
    if (eventIters[index] == totalEvent[index].end()) return;

    float ratio = motion->runningTime / motion->duration;

    if (eventIters[index]->first > ratio) return;

    eventIters[index]->second();
    eventIters[index]++;
}

void Customer::PlayEndEvent()
{
    switch (curState)
    {
    case Customer::SIT:
    case Customer::ORDER:
    case Customer::DRINK:
        SetState(SITTING_IDLE);
        break;
    case Customer::STAND:
        SetState(WALK);
        int randomPos = Random(0, 2);

        if (randomPos == 0)
        {
            destPos = UP_START;
            way = UP;
        }
        else if (randomPos == 1)
        {
            destPos = DOWN_START;
            way = DOWN;
        }
   
        SetDestination();
        break;
    }
}

void Customer::SetState(State state)
{
    if (curState == state) return;

    curState = state;
    instancing->PlayClip(index, state);
    eventIters[state] = totalEvent[state].begin();
}

void Customer::Move()
{
    if (path.empty()) return;

    Vector3 dest = path.back();

    Vector3 direction = dest - transform->Pos();
    direction.y = 0.0f;

    if (direction.Length() < 0.1f)
        path.pop_back();

    velocity = direction.GetNormalized();

    transform->Pos() += velocity * moveSpeed * DELTA;
}

void Customer::Rotate()
{
    Vector3 forward = transform->Forward();
    Vector3 cross = Cross(forward, velocity);

    if (cross.y < 0)
        transform->Rot().y += rotSpeed * DELTA;
    else if (cross.y > 0)
        transform->Rot().y -= rotSpeed * DELTA;
}

void Customer::Sit()
{
    if (way == TAVERN && path.empty() && !isSit && !isOrdered)
    {
        SetState(SIT);
        velocity = 0.0f;
        isSit = true;
        transform->Rot().y = TavernManager::Get()->GetChairAngle(chairIndex);
    }

}

void Customer::Order()
{
    if (isSit && !isOrdered)
    {
        waitTime += DELTA;

        if (waitTime > WAIT_TIME)
        {
            SetState(ORDER);
            TavernManager::Get()->MakeBeverage(chairIndex);
            isOrdered = true;
            waitTime = 0.0f;
        }

    }
}

void Customer::Drink()
{
    if (isOrdered && !isDrink && TavernManager::Get()->GetIsDelivered(chairIndex))
    {
        waitTime += DELTA;

        if (waitTime > WAIT_TIME)
        {
            SetState(DRINK);
            isDrink = true;
            waitTime = 0.0f;
        }

    }
}

void Customer::Stand()
{
    if (isSit && isDrink && curState == SITTING_IDLE)
    {
        SetState(STAND);
        isSit = false;
        TavernManager::Get()->ClearChairSeat(chairIndex);
    }
}

void Customer::Remove()
{
    if (!transform->Active()) return;
    if (way == TAVERN) return;

    if (path.empty())
    {
        transform->SetActive(false);
        payGold_YValue = 0.0f;
    }

}

void Customer::PrintPayGold()
{
    Font::Get()->SetColor("White");

    Font::Get()->RenderText("+6", { payGold->GlobalPos().x - 30.0f, payGold->GlobalPos().y });
}
