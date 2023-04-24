#include "Framework.h"
#include "TavernScene.h"

TavernScene::TavernScene()
{
	terrain = new Terrain();
	skybox = new Skybox(L"Textures/Landscape/Sky.dds");

	water = new Water(L"Textures/Landscape/Wave.dds", 200, 200);
	water->Load();

	trees = new Tree();
	grass = new Grass();
	rock1 = new Rock("Rock1");

	bridge = new Model("Bridge");
	bridge->Load();

	stonefence = new Stonefence();

	StructureDataManager::Get();
	UIManager::Get()->SetTerrain(terrain);
	PathManager::Get()->SetPath(terrain);
	StructureManager::Get();
	CustomerManager::Get();
	TavernManager::Get();

	CreateSounds();

	CAM->Load();
}

TavernScene::~TavernScene()
{
	delete terrain;
	delete water;
	delete skybox;
	delete trees;
	delete grass;
	delete rock1;

	delete stonefence;
	delete bridge;
	
	PathManager::Delete();
	CustomerManager::Delete();
	UIManager::Delete();
	StructureManager::Delete();
	TavernManager::Delete();
	StructureDataManager::Delete();
}

void TavernScene::Update()
{
	LoopBgm();

	StructureManager::Get()->Update();
	UIManager::Get()->Update();
	CustomerManager::Get()->Update();
	TavernManager::Get()->Update();

	PathManager::Get()->Update();
	skybox->Update();
	terrain->UpdateWorld();
	water->Update();
	trees->Update();
	grass->Update();
	rock1->Update();
	stonefence->Update();
	bridge->UpdateWorld();
}

void TavernScene::PreRender()
{
	water->SetRefraction();
	
	skybox->Render();
	bridge->Render();
	terrain->Render();

	water->SetReflection();

	skybox->Render();
	bridge->Render();
	terrain->Render();
}

void TavernScene::Render()
{
	skybox->Render();
	terrain->Render();

	StructureManager::Get()->Render();
	UIManager::Get()->Render();

	water->Render();
	trees->Render();
	grass->Render();
	rock1->Render();
	stonefence->Render();
	bridge->Render();

	PathManager::Get()->Render();
	TavernManager::Get()->Render();
	CustomerManager::Get()->Render();
}

void TavernScene::PostRender()
{
	UIManager::Get()->PostRender();
	CustomerManager::Get()->PostRender();
}

void TavernScene::GUIRender()
{
	//UIManager::Get()->GUIRender();
	//TavernManager::Get()->GUIRender();
	//CustomerManager::Get()->GUIRender();
	//bridge->GUIRender();
	//stonefence->GUIRender();
	//trees->GUIRender();
	//water->GUIRender();
	//grass->GUIRender();
	//rock1->GUIRender();
	//skybox->GUIRender();
	//astar->GUIRender();
	//customer->GUIRender();
}

void TavernScene::CreateSounds()
{
	Audio::Get()->Add("Create_Floor", "Sounds/Create_Floor.wav");
	Audio::Get()->Add("Create_Structure", "Sounds/Create_Structure.wav");
	Audio::Get()->Add("Create_Wall", "Sounds/Create_Wall.wav");
	Audio::Get()->Add("Delete_Structure", "Sounds/Delete_Structure.wav");
	Audio::Get()->Add("UI Click", "Sounds/UI Click.wav");
}

void TavernScene::LoopBgm()
{
	if (!Audio::Get()->IsPlaySound("Bgm " + to_string(curBgmIndex)))
	{
		curBgmIndex = Random(1, 6);
		Audio::Get()->Play("Bgm " + to_string(curBgmIndex), 0.6f);
	}
}


