#include "Framework.h"

StructureManager::StructureManager()
{
	LoadBaseStructureData();

	//πŸ≈π ≈∏¿œ 
	{
		floors.reserve(BASEFLOOR_WIDTH * BASEFLOOR_HEIGHT);

		for (int z = 0; z < BASEFLOOR_HEIGHT; z++)
		{
			for (int x = 0; x < BASEFLOOR_WIDTH; x++)
			{
				floors.push_back(new Plane());
				floors.back()->Pos().x = 40.0f + 4.0f * x;
				floors.back()->Pos().z = 2.0f - 4.0f * z;
				floors.back()->Rot().y = -XM_PIDIV2;
				floors.back()->UpdateWorld();
			}
		}
	}
}

StructureManager::~StructureManager()
{
	for (Structure* mapModel : mapStructures)
		delete mapModel;

	for (Plane* floor : floors)
		delete floor;
}

void StructureManager::LoadBaseStructureData()
{
	fstream loadFile("TextData/BaseStructureData.csv");

	string temp;

	char text[256];

	bool isFirstLine = true;

	while (true)
	{
		loadFile >> temp;

		if (isFirstLine)
		{
			isFirstLine = false;
			continue;
		}

		vector<string> datas = SplitString(temp, ",");

		Structure* structure = new Structure(datas[0]);
		structure->Pos() = { stof(datas[1]), 0, stof(datas[2]) };

		if (stoi(datas[3]) == 90)
			structure->Rot().y = XM_PIDIV2;
		else if (stoi(datas[3]) == 180)
			structure->Rot().y = XM_PIDIV2 * 2.0f;

		structure->UpdateWorld();
		structure->GetCollider()->UpdateWorld();

		mapStructures.push_back(structure);

		if (loadFile.eof())
			break;
	}
}

void StructureManager::Update()
{
	for (Structure* mapModel : mapStructures)
	{
		if (mapModel->GetType() == CANDLE)
			((Candle*)mapModel)->Update();
		else
			mapModel->Update();
	}

	for (Plane* floor : floors)
		floor->Update();

}

void StructureManager::Render()
{
	for (Structure* mapModel : mapStructures)
	{
		if (mapModel->GetType() == CANDLE)
			((Candle*)mapModel)->Render();
		else
			mapModel->Render();
	}

	for (Plane* floor : floors)
	{
		floor->Render();
	}
}

void StructureManager::GUIRender()
{
}

void StructureManager::AddStructure(Structure* structure)
{
	mapStructures.push_back(structure);
}

void StructureManager::AddFloor(Plane* plane)
{
	floors.push_back(plane);
}
