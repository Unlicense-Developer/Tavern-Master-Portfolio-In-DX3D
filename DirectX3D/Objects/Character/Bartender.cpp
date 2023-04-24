#include "Framework.h"

Bartender::Bartender()
	:ModelAnimator("Bartender")
{
	tankardTransform = new Transform();

	tankard = new Model("Tankard_Foam");
	tankard->SetTag("Tankard_Bartender");
	tankard->SetParent(tankardTransform);
	tankard->Load();

	ReadClip("Walk");
	ReadClip("Standing_Idle");
	ReadClip("Carry");

	Pos() = IDLE_POS;
}

Bartender::~Bartender()
{
	delete tankardTransform;
	delete tankard;
}

void Bartender::Update()
{
	MakeBeer();
	CheckMakeTime();
	DeliverToCounter();
	
	Move();
	Rotate();
	SetAnimation();

	tankardTransform->SetWorld(GetTransformByNode(38));

	ModelAnimator::Update();
	tankard->UpdateWorld();
}

void Bartender::Render()
{
	ModelAnimator::Render();

	if (curState == CARRY)
	{
		tankard->Render();
	}
}

void Bartender::GUIRender()
{
	Model::GUIRender();
	tankard->GUIRender();
}

void Bartender::Move()
{
	if (path.empty()) return;

	Vector3 dest = path.back();

	Vector3 direction = dest - Pos();
	direction.y = 0.0f;

	if (direction.Length() < 0.01f)
		path.pop_back();

	velocity = direction.GetNormalized();

	Pos() += velocity * moveSpeed * DELTA;
}

void Bartender::Rotate()
{
	if (path.empty())
	{
		Rot().y = 0.0f;
		return;
	}

	Vector3 forward = Forward();
	Vector3 cross = Cross(forward, velocity);

	if (cross.y < 0)
		Rot().y += rotSpeed * DELTA;
	else if (cross.y > 0)
		Rot().y -= rotSpeed * DELTA;
}

void Bartender::DeliverToCounter()
{
	if (isCarry && path.empty())
	{
		isCarry = false;
		TavernManager::Get()->ServeCounterBeer();
	}
}

void Bartender::CheckMakeTime() // 맥주 제조 시간 체크
{
	if (TavernManager::Get()->GetOrderSize() && path.empty()) // 주문 있을때 && 행선지 없을때
	{
		time += DELTA;

		if (time >= MAKING_TIME)
		{
			destPos = IDLE_POS;
			SetDestination();
			time = 0.0f;
			isCarry = true;
		}
	}
}

void Bartender::MakeBeer()
{
	if (isCarry) return;

	if (!TavernManager::Get()->GetOrderSize()) return;

	destPos = BEER_POS;

	SetDestination();
}

void Bartender::SetAnimation()
{
	if (isCarry)
		SetState(CARRY);
	else if (!path.empty())
		SetState(WALK);
	else
		SetState(IDLE);
}

void Bartender::SetState(State state)
{
	if (curState == state) return;

	curState = state;
	PlayClip(state);
}

void Bartender::SetDestination()
{
	int start = PathManager::Get()->GetAStar()->FindCloseNode(GlobalPos());
	int end = PathManager::Get()->GetAStar()->FindCloseNode(destPos);

	PathManager::Get()->GetAStar()->GetPath(start, end, path);
}
