#include "Framework.h"

CustomerManager::CustomerManager()
{
	blacksmithInstancing = new ModelAnimatorInstancing("Blacksmith");
	blacksmithInstancing->ReadClip("Walk");
	blacksmithInstancing->ReadClip("StandToSit");
	blacksmithInstancing->ReadClip("Order");
	blacksmithInstancing->ReadClip("Drink");
	blacksmithInstancing->ReadClip("Sitting_Idle");
	blacksmithInstancing->ReadClip("SitToStand");

	fortunetellerInstancing = new ModelAnimatorInstancing("Fortuneteller");
	fortunetellerInstancing->ReadClip("Walk");
	fortunetellerInstancing->ReadClip("StandToSit");
	fortunetellerInstancing->ReadClip("Order");
	fortunetellerInstancing->ReadClip("Drink");
	fortunetellerInstancing->ReadClip("Sitting_Idle");
	fortunetellerInstancing->ReadClip("SitToStand");

	peasant_MaleInstancing = new ModelAnimatorInstancing("Peasant_Male");
	peasant_MaleInstancing->ReadClip("Walk");
	peasant_MaleInstancing->ReadClip("StandToSit");
	peasant_MaleInstancing->ReadClip("Order");
	peasant_MaleInstancing->ReadClip("Drink");
	peasant_MaleInstancing->ReadClip("Sitting_Idle");
	peasant_MaleInstancing->ReadClip("SitToStand");

	peasant_FemaleInstancing = new ModelAnimatorInstancing("Peasant_Female");
	peasant_FemaleInstancing->ReadClip("Walk");
	peasant_FemaleInstancing->ReadClip("StandToSit");
	peasant_FemaleInstancing->ReadClip("Order");
	peasant_FemaleInstancing->ReadClip("Drink");
	peasant_FemaleInstancing->ReadClip("Sitting_Idle");
	peasant_FemaleInstancing->ReadClip("SitToStand");

	riderInstancing = new ModelAnimatorInstancing("Rider");
	riderInstancing->ReadClip("Walk");
	riderInstancing->ReadClip("StandToSit");
	riderInstancing->ReadClip("Order");
	riderInstancing->ReadClip("Drink");
	riderInstancing->ReadClip("Sitting_Idle");
	riderInstancing->ReadClip("SitToStand");

	wizardInstancing = new ModelAnimatorInstancing("Wizard");
	wizardInstancing->ReadClip("Walk");
	wizardInstancing->ReadClip("StandToSit");
	wizardInstancing->ReadClip("Order");
	wizardInstancing->ReadClip("Drink");
	wizardInstancing->ReadClip("Sitting_Idle");
	wizardInstancing->ReadClip("SitToStand");

	customers.reserve(SIZE * 6);
	FOR(SIZE)
	{
		Transform* transform = blacksmithInstancing->Add();
		transform->SetActive(false);
		Customer* customer = new Customer(transform, blacksmithInstancing, i);
		customers.push_back(customer);
	}

	FOR(SIZE)
	{
		Transform* transform = fortunetellerInstancing->Add();
		transform->SetActive(false);
		Customer* customer = new Customer(transform, fortunetellerInstancing, i);
		customers.push_back(customer);
	}

	FOR(SIZE)
	{
		Transform* transform = peasant_MaleInstancing->Add();
		transform->SetActive(false);
		Customer* customer = new Customer(transform, peasant_MaleInstancing, i);
		customers.push_back(customer);
	}

	FOR(SIZE)
	{
		Transform* transform = peasant_FemaleInstancing->Add();
		transform->SetActive(false);
		Customer* customer = new Customer(transform, peasant_FemaleInstancing, i);
		customers.push_back(customer);
	}

	FOR(SIZE)
	{
		Transform* transform = riderInstancing->Add();
		transform->SetActive(false);
		Customer* customer = new Customer(transform, riderInstancing, i);
		customers.push_back(customer);
	}

	FOR(SIZE)
	{
		Transform* transform = wizardInstancing->Add();
		transform->SetActive(false);
		Customer* customer = new Customer(transform, wizardInstancing, i);
		customers.push_back(customer);
	}
}

CustomerManager::~CustomerManager()
{
	delete blacksmithInstancing;
	delete fortunetellerInstancing;
	delete peasant_MaleInstancing;
	delete peasant_FemaleInstancing;
	delete riderInstancing;
	delete wizardInstancing;

	for (Customer* customer : customers)
		delete customer;
}

void CustomerManager::Update()
{
	time += DELTA;

	if (time > SPAWN_TIME)
	{
		time -= SPAWN_TIME;
		Spawn();
	}


	blacksmithInstancing->Update();
	fortunetellerInstancing->Update();
	peasant_MaleInstancing->Update();
	peasant_FemaleInstancing->Update();
	riderInstancing->Update();
	wizardInstancing->Update();

	for (Customer* customer : customers)
		customer->Update();
}

void CustomerManager::Render()
{
	blacksmithInstancing->Render();
	fortunetellerInstancing->Render();
	peasant_MaleInstancing->Render();
	peasant_FemaleInstancing->Render();
	riderInstancing->Render();
	wizardInstancing->Render();

	for (Customer* customer : customers)
		customer->Render();
}

void CustomerManager::PostRender()
{
	for (Customer* customer : customers)
		customer->PostRender();
}

void CustomerManager::GUIRender()
{
	for (Customer* customer : customers)
		customer->GUIRender();
}

void CustomerManager::Spawn()
{
	int random = Random(0, customers.size());

	if (!customers[random]->GetTransform()->Active()) // 등장하지 않은 손님 검색
	{
		int randomWay = Random(0, 4);

		switch (randomWay)
		{
		case 0:
			customers[random]->SetWay(Way::UP); // 위쪽 방향
			break;
		case 1:
			customers[random]->SetWay(Way::DOWN); // 아래쪽 방향
			break;
		case 2:
		case 3:
			customers[random]->SetWay(Way::TAVERN); // 주점에 올 손님
			break;
		}

		customers[random]->Spawn();
	}
	else // 이미 나온 손님이면 다시 랜덤 손님 검색
		Spawn();
}
