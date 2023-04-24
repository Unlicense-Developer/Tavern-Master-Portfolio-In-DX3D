#include "Framework.h"

Waitress::Waitress()
	:ModelAnimator("Waitress")
{
	plateTransform = new Transform();
	plate = new Model("Plate");
	plate->SetParent(plateTransform);
	plate->Load();

	tankard = new Model("Tankard_Foam");
	tankard->SetTag("Tankard_Waitress");
	tankard->SetParent(plate);
	tankard->Load();

	ReadClip("Walk");
	ReadClip("Standing_Idle");
	ReadClip("Carry");

	Pos() = IDLE_POS;
}

Waitress::~Waitress()
{
	delete plateTransform;
	delete plate;
	delete tankard;
}

void Waitress::Update()
{
	CheckBeer();
	CompleteDeliver();

	Move();
	Rotate();
	SetAnimation();

	plateTransform->SetWorld(GetTransformByNode(7));

	ModelAnimator::Update();

	plate->UpdateWorld();
	tankard->UpdateWorld();
}

void Waitress::Render()
{
	ModelAnimator::Render();

	if (curState == CARRY)
	{
		plate->Render();
		tankard->Render();
	}
}

void Waitress::GUIRender()
{
	Model::GUIRender();
	plate->GUIRender();
	tankard->GUIRender();
}

void Waitress::Move()
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

void Waitress::Rotate()
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

void Waitress::Carry()
{
}

void Waitress::CheckBeer()
{
	if (isDelivering || GlobalPos().z < 1.0f) return;

	if (TavernManager::Get()->GetCounterBeerNum())
	{
		destPos = TavernManager::Get()->GetFrontOrderPos();
		SetDestination();
		TavernManager::Get()->StartDeliver(deliverIndex);
		isDelivering = true;
	}
}

void Waitress::CompleteDeliver()
{
	if (isDelivering && path.empty())
	{
		destPos = IDLE_POS;
		SetDestination();
		isDelivering = false;
		TavernManager::Get()->PayBeer(deliverIndex);
	}
}

void Waitress::SetAnimation()
{
	if (isDelivering)
		SetState(CARRY);
	else if ( path.size() > 0 )
		SetState(WALK);
	else
		SetState(IDLE);
}

void Waitress::SetState(State state)
{
	if (curState == state) return;

	curState = state;
	PlayClip(state);
}

void Waitress::SetDestination()
{
	int start = PathManager::Get()->GetAStar()->FindCloseNode(GlobalPos());
	int end = PathManager::Get()->GetAStar()->FindCloseNode(destPos);

	PathManager::Get()->GetAStar()->GetPath(start, end, path);
}
