#include "Framework.h"

PathManager::PathManager()
{
	aStar = new AStar(200, 200);
}

PathManager::~PathManager()
{
	delete aStar;
}

void PathManager::Update()
{
	aStar->Update();
}

void PathManager::Render()
{
	aStar->Render();
}
