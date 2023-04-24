#include "Framework.h"

TavernManager::TavernManager()
{
	lanternLight = Environment::Get()->AddLight(lanternLightIndex);
	lanternLight->type = 1;
	lanternLight->range = 10.0f;
	lanternLight->color = { 1.0f, 0.4f, 0.0f, 1.0f };
	lanternLight->pos = lanternLight_Pos;

	bartender = new Bartender();
	waitress = new Waitress();

	beerBarrel = new Model("Barrel");
	beerBarrel->SetTag("Beer_Barrel");
	beerBarrel->Load();

	waterBarrel = new Model("Barrel");
	waterBarrel->SetTag("Water_Barrel");
	waterBarrel->Load();

	for (int i = 0; i < MAX_COUNTERBEER; i++)
	{
		counterTankards.push_back(new Model("Tankard_Foam"));
		counterTankards.back()->SetTag("Tankard_Counter" + to_string(i + 1));
		counterTankards.back()->Load();
	}
}

TavernManager::~TavernManager()
{
	delete bartender;
	delete waitress;
	delete beerBarrel;
	delete waterBarrel;

	for(Model* tankard : counterTankards)
		delete tankard;
}

void TavernManager::Update()
{
	bartender->Update();
	waitress->Update();

	beerBarrel->UpdateWorld();
	waterBarrel->UpdateWorld();

	for (Model* tankard : counterTankards)
		tankard->UpdateWorld();
}

void TavernManager::Render()
{
	bartender->Render();
	waitress->Render();

	beerBarrel->Render();
	waterBarrel->Render();

	FOR(counterBeerNum)
	{
		counterTankards[i]->Render();
	}
}

void TavernManager::PostRender()
{
}

void TavernManager::GUIRender()
{
	beerBarrel->GUIRender();
	waterBarrel->GUIRender();

	for (Model* tankard : counterTankards)
		tankard->GUIRender();
}

void TavernManager::AddChairData(Structure* chair)
{
	ChairData chairData;

	if (chair->GetType() == CHAIR1)
	{
		chairData.chairPos = chair->GlobalPos();
		chairData.sitAngle = chair->Rot().y;
		chairDatas.push_back(chairData);
	}
	else if(chair->GetType() == CHAIR2)
	{
		chairData.isAvailable = true; // 좌석이 비었는지

		if (abs((int)(chair->Rot().y / XM_PIDIV2)) % 2 == 0) // 가로 방향
		{
			chairData.chairPos = chair->GlobalPos() + Vector3(+0.5, 0, 0); // 좌석 위치
			chairData.sitAngle = chair->Rot().y; // 앉는 방향
			chairDatas.push_back(chairData);

			chairData.chairPos = chair->GlobalPos() + Vector3(-0.5, 0, 0);
			chairDatas.push_back(chairData);
		}
		else if (abs((int)(chair->Rot().y / XM_PIDIV2)) % 2 == 1) // 세로 방향
		{
			chairData.chairPos = chair->GlobalPos() + Vector3(0, 0, +0.5);
			chairData.sitAngle = chair->Rot().y;
			chairDatas.push_back(chairData);

			chairData.chairPos = chair->GlobalPos() + Vector3(0, 0, -0.5);
			chairDatas.push_back(chairData);
		}
	}
	else
		return;
}

Vector3 TavernManager::GetFrontOrderPos()
{
	return chairDatas[orderPriority.front()].chairPos;
}

Vector3 TavernManager::GetRandomChairPos(int& chairIndex)
{
	if (chairDatas.empty()) return Vector3(); // 의자 없음

	Vector3 chairPos = {0, 0, 0};

	FOR (chairDatas.size())
	{
		if (!chairDatas[i].isAvailable) continue; //이미 찬 자리

		chairDatas[i].isAvailable = false;

		chairIndex = i;

		chairPos = chairDatas[i].chairPos;

		break;
	}

	return chairPos;
}

float TavernManager::GetChairAngle(int chairIndex)
{
	return chairDatas[chairIndex].sitAngle;
}

void TavernManager::ClearChairSeat(int chairIndex)
{
	chairDatas[chairIndex].isAvailable = true;
	chairDatas[chairIndex].isDelivered = false;
}

bool TavernManager::GetIsDelivered(int chairIndex)
{
	if (chairDatas.empty())
		return false;

	return chairDatas[chairIndex].isDelivered;
}

void TavernManager::MakeBeverage(int chairIndex)
{
	orderPriority.push(chairIndex);
}

void TavernManager::StartDeliver(int& deliverIndex)
{
	deliverIndex = orderPriority.front();
	orderPriority.pop();
	counterBeerNum--;
}

void TavernManager::ServeCounterBeer()
{
	counterBeerNum++;
}

void TavernManager::PayBeer(int deliverIndex)
{
	chairDatas[deliverIndex].isDelivered = true;
	gold += BEER_PRICE;
	fame += Random(1, 6);
}
