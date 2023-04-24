#include "Framework.h"
#include "Stonefence.h"

Stonefence::Stonefence()
{
	leftFence = new Model("Stonefence_Left");
	leftFence->Load();

	rightFence = new Model("Stonefence_Right");
	rightFence->Load();

	leftFire = new Sprite(L"Textures/Effect/Fire1.png", 1, 1, 5, 5, true);
	rightFire = new Sprite(L"Textures/Effect/Fire1.png", 1, 1, 5, 5, true);
}

Stonefence::~Stonefence()
{
	delete leftFence;
	delete rightFence;

	delete leftFire;
	delete rightFire;
}

void Stonefence::Update()
{
	leftFence->UpdateWorld();
	rightFence->UpdateWorld();

	if (!leftFire->IsActive())
		leftFire->Play(leftFence->GlobalPos() + OFFSET_LEFTFIRE);

	if (!rightFire->IsActive())
		rightFire->Play(rightFence->GlobalPos() + OFFSET_RIGHTFIRE);

	leftFire->Update();
	rightFire->Update();
}

void Stonefence::Render()
{
	leftFence->Render();
	rightFence->Render();

	leftFire->Render();
	rightFire->Render();
}

void Stonefence::GUIRender()
{
	leftFence->GUIRender();
	rightFence->GUIRender();
}
